#pragma once
#include <lame/lame.h>
#include <mpg123.h>
#include <vector>
#include <string>
#include <fstream>

class StereoAudio {
public:
	std::vector<short> left;
	std::vector<short> right;
	StereoAudio(std::vector<short> left, std::vector<short> right);
};

class AudioProvider {
private:
	mpg123_handle* handle;
	int err;
public:
	AudioProvider();
	bool openFile(std::string filename);
	StereoAudio getFrame();
};
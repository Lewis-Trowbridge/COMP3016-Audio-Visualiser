#pragma once
#include <mpg123.h>
#include <vector>
#include <string>
#include <fstream>

class AudioProvider {
private:
	mpg123_handle* handle;
	int err;
public:
	AudioProvider();
	bool openFile(std::string filename);
	std::vector<float> getFrame();
};
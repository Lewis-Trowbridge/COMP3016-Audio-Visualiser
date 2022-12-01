#pragma once
#include <lame/lame.h>
#include <vector>
#include <string>
#include <fstream>

class AudioProvider {
private:
	std::vector<float> floats;
public:
	bool openFile(std::string filename);
};
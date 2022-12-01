#pragma once
#include <lame/lame.h>
#include <vector>
#include <string>
#include <fstream>

class AudioProvider {
private:
	std::ifstream* currentStream;
	lame_global_flags* lameFlags;
	hip_global_flags* hipFlags;
public:
	AudioProvider();
	bool openFile(std::string filename);
};
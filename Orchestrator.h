#pragma once
#include "AudioProvider.h"
#include "FrequencyProvider.h"
#include "models/ModelDraw.h"
class Orchestrator {
public:
	Drawer drawer;

	Orchestrator();
	void openAudioFile(std::string filename);
	void createCubesInCircle(size_t cubes);
	void playAudioFrame();
private:
	FrequencyProvider frequencyProvider;
	AudioProvider audioProvider;
};

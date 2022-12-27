#pragma once
#include "AudioProvider.h"
#include "FrequencyProvider.h"
#include "models/ModelDraw.h"
class Orchestrator {
public:
	Drawer drawer;
	double audioSecondsLength;

	Orchestrator(size_t cubes);
	void openAudioFile(std::string filename);
	void createCubesInCircle();
	void playAudioFrame();
private:
	size_t cubes;
	FrequencyProvider frequencyProvider;
	AudioProvider audioProvider;
};

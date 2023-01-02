#pragma once
#include "AudioProvider.h"
#include "FrequencyProvider.h"
#include "models/ModelDraw.h"

enum CameraMode {
	LOCKED,
	MANUAL,
	AUTOMATIC
};

class Orchestrator {
public:
	Drawer drawer;
	double audioSecondsLength;
	CameraMode cameraMode;

	Orchestrator(size_t cubes);
	void openAudioFile(std::string filename);
	void createCubesInCircle();
	void playAudioFrame();
	void moveCameraRight();
	void moveCameraLeft();
	void cycleCameraMode();
private:
	size_t cubes;
	FrequencyProvider frequencyProvider;
	AudioProvider audioProvider;
};

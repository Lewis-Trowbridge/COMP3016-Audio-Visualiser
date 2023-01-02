#pragma once
#include "AudioProvider.h"
#include "FrequencyProvider.h"
#include "models/ModelDraw.h"
#include "window/ImGUIWindow.h"
#include "CameraMode.h"

class Orchestrator {
public:
	Drawer drawer;
	double audioSecondsLength;
	CameraMode cameraMode;

	Orchestrator(size_t cubes);
	void openAudioFile(std::string filename);
	void createCubesInCircle();
	void playAudioFrame();
	void drawControls();
	void moveCameraRight();
	void moveCameraLeft();
	void cycleCameraMode();
private:
	size_t cubes;
	FrequencyProvider frequencyProvider;
	AudioProvider audioProvider;
	VisualiserImGUIWindow visualiserWindow;
	bool playing;
	double elapsedTime;
};

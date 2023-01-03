#pragma once
#include "AudioProvider.h"
#include "FrequencyProvider.h"
#include "models/ModelDraw.h"
#include "window/ImGUIWindow.h"
#include "CameraMode.h"
#include <tinyfiledialogs.h>

class Orchestrator {
public:
	Drawer drawer;
	double audioSecondsLength;
	CameraMode cameraMode;

	Orchestrator(size_t cubes);
	void openAudioFile();
	void createCubesInCircle();
	void playAudioFrame();
	void drawControls();
	void moveCameraRight();
	void moveCameraLeft();
	void cycleCameraMode();
private:
	size_t cubes;
	std::string filename;
	FrequencyProvider frequencyProvider;
	AudioProvider audioProvider;
	VisualiserImGUIWindow visualiserWindow;
	bool playing;
	double elapsedTime;

	void openFileDialog();
};

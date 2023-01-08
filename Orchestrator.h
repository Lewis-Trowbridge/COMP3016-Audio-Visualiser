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
	// Opens the audio file at the registered filename
	void openAudioFile();
	// Draws a set of cubes in a circle
	void createCubesInCircle();
	// Plays a single audio frame
	void playAudioFrame();
	// Draws the ImGUI controls
	void drawControls();
	// Moves the camera right.
	void moveCameraRight();
	// Moves the camera left.
	void moveCameraLeft();
	// Cycles the registered camera mode enum.
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

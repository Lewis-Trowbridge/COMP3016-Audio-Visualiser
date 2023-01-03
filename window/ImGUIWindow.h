#pragma once
#include <imgui.h>
#include "../CameraMode.h"
#include <string>
#include <sstream>
#include <iomanip>

class VisualiserImGUIWindow {
public:
	bool show;
	bool shouldOpenFileDialog;

	VisualiserImGUIWindow();
	void setup(CameraMode* cameraMode, bool* playing, double* elaspedTime);
	void draw();

private:
	CameraMode* cameraMode;
	bool* playing;
	double* elapsedTime;
};
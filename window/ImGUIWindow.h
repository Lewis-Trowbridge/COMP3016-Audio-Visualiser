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
	void setup(std::string* filename, CameraMode* cameraMode, bool* playing, double* elaspedTime);
	void draw();

private:
	std::string* filename;
	CameraMode* cameraMode;
	bool* playing;
	double* elapsedTime;
};
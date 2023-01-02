#pragma once
#include <imgui.h>
#include "../CameraMode.h"
#include <string>

class VisualiserImGUIWindow {
public:
	bool show;

	VisualiserImGUIWindow();
	void setup(CameraMode* cameraMode, bool* playing);
	void draw();

private:
	CameraMode* cameraMode;
	bool* playing;
};
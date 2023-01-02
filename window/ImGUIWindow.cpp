#include "ImGUIWindow.h"

VisualiserImGUIWindow::VisualiserImGUIWindow() {
	show = true;
	cameraMode = nullptr;
}

void VisualiserImGUIWindow::setup(CameraMode* cameraMode) {
	this->cameraMode = cameraMode;
}

void VisualiserImGUIWindow::draw() {
	if (show) {
		ImGui::Begin("Visualiser controls");
		std::string stringCameraValue;
		switch (*cameraMode) {
		case LOCKED:
			ImGui::Text("Camera mode: Locked");
			break;
		case AUTOMATIC:
			ImGui::Text("Camera mode: Automatic");
			break;
		case MANUAL:
			ImGui::Text("Camera mode: Manual");
			break;
		}


		ImGui::End();
	}
}
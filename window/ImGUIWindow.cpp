#include "ImGUIWindow.h"

VisualiserImGUIWindow::VisualiserImGUIWindow() {
	show = true;
	cameraMode = nullptr;
}

void VisualiserImGUIWindow::setup(CameraMode* cameraMode, bool* playing, double* elapsedTime) {
	this->cameraMode = cameraMode;
	this->playing = playing;
	this->elapsedTime = elapsedTime;
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

		std::string buttonTitle;
		if (*playing) {
			buttonTitle = "Stop";
		}
		else {
			buttonTitle = "Play";
		}
		
		if (ImGui::Button(buttonTitle.c_str())) {
			*playing = !*playing;
		};

		ImGui::SameLine();

		std::stringstream elapsedStringStream = std::stringstream();
		elapsedStringStream << std::fixed << std::setprecision(2) << *elapsedTime;
		ImGui::Text(elapsedStringStream.str().c_str());


		ImGui::End();
	}
}
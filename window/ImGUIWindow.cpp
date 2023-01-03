#include "ImGUIWindow.h"

VisualiserImGUIWindow::VisualiserImGUIWindow() {
	show = true;
	cameraMode = nullptr;
	playing = nullptr;
	elapsedTime = nullptr;
	shouldOpenFileDialog = true;
}

void VisualiserImGUIWindow::setup(std::string* filename, CameraMode* cameraMode, bool* playing, double* elapsedTime) {
	this->filename = filename;
	this->cameraMode = cameraMode;
	this->playing = playing;
	this->elapsedTime = elapsedTime;
}

void VisualiserImGUIWindow::draw() {
	if (show) {
		ImGui::Begin("Visualiser controls");

		if (*filename != "") {
			// TODO: Only compatible with Windows filesystems, extend to unix-based filesystems
			ImGui::Text((filename->substr(filename->find_last_of("\\\\")).c_str()));
		}

		ImGui::Text("Camera mode:");

		std::string stringCameraValue;
		switch (*cameraMode) {
		case LOCKED:
			stringCameraValue = "Locked";
			break;
		case AUTOMATIC:
			stringCameraValue = "Automatic";
			break;
		case MANUAL:
			stringCameraValue = "Manual";
			break;
		}

		ImGui::SameLine();

		ImGui::Text(stringCameraValue.c_str());

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

		if (ImGui::Button("Open file")) {
			shouldOpenFileDialog = true;
		};


		ImGui::End();
	}
}
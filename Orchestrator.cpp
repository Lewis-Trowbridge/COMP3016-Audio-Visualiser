#include "Orchestrator.h"

const GLint radius = 10;

Orchestrator::Orchestrator(size_t cubes) {
	this->cubes = cubes;
	this->filename = "";
	this->audioSecondsLength = 0.0;
	this->elapsedTime = 0.0;
	visualiserWindow.setup(&cameraMode, &playing, &elapsedTime);


	drawer.view = glm::translate(drawer.view, glm::vec3(0.0f, -3.0f, -15.0f));
	drawer.view = glm::rotate(drawer.view, glm::radians(25.0f), glm::vec3(1.0f, 0.0f, 0.0f));
}

void Orchestrator::openFileDialog() {
	std::vector<char*> filters = { "*.mp3" };
	filename = tinyfd_openFileDialog("Open MP3 file", NULL,
		1, filters.data(), "mp3 files", false);
	visualiserWindow.shouldOpenFileDialog = false;
	openAudioFile();
}

void Orchestrator::openAudioFile() {
	audioProvider.openFile(filename);
	audioSecondsLength = audioProvider.getLengthOfFrameInSeconds();
	elapsedTime = 0.0;
}

void Orchestrator::createCubesInCircle() {
	GLfloat angleIncrement = 360.0f / cubes;
	for (GLint i = 0; i < cubes; i++) {
		Mesh* cube = drawer.create();
		cube->initFromFile("media/models/cube.obj");
		// TODO: See if we can move these calculations to the vertex shader?
		GLfloat angle = angleIncrement * (i + 1);
		cube->scale(1.0f, 5.0f, 1.0f, false);
		cube->rotate(angle, 0.0f, 1.0f, 0.0f);
		cube->translate(10.0f, 0.0f, 0.0f);
		cube->saveMatrix(); 
	}
	drawer.setup();
	playing = true;
}

void Orchestrator::playAudioFrame() {
	if (cameraMode == AUTOMATIC) {
		moveCameraRight();
	}
	if (playing) {
		std::vector<float> frame = audioProvider.getFrame();
		if (frame.size() != 0) {
			std::vector<float> buckets = frequencyProvider.getFrequencies(&frame, cubes);
			for (int i = 0; i < cubes; i++) {
				drawer.verticallyScaleMesh(i, buckets[i]);
			}
			elapsedTime += audioSecondsLength;
		}

		// TODO: Add playing frame out of speakers

		
	}
}

void Orchestrator::drawControls() {
	visualiserWindow.draw();
	if (visualiserWindow.shouldOpenFileDialog) {
		openFileDialog();
	}
}

void Orchestrator::moveCameraRight() {
	drawer.view = glm::rotate(drawer.view, glm::radians(5.0f), glm::vec3(0.0f, -1.0f, 0.0f));
}

void Orchestrator::moveCameraLeft() {
	drawer.view = glm::rotate(drawer.view, glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Orchestrator::cycleCameraMode() {
	switch (cameraMode) {
	case LOCKED:
		cameraMode = AUTOMATIC;
		break;
	case AUTOMATIC:
		cameraMode = MANUAL;
		break;
	case MANUAL:
		cameraMode = LOCKED;
	}
}
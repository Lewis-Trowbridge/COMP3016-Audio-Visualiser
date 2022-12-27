#include "Orchestrator.h"

const GLint radius = 10;

Orchestrator::Orchestrator(size_t cubes) {
	this->cubes = cubes;
	this->audioSecondsLength;
	drawer = Drawer();
	audioProvider = AudioProvider();
	frequencyProvider = FrequencyProvider();
}

void Orchestrator::openAudioFile(std::string filename) {
	audioProvider.openFile(filename);
	audioSecondsLength = audioProvider.getLengthOfFrameInSeconds();
}

void Orchestrator::createCubesInCircle() {
	GLfloat angleIncrement = 360.0f / cubes;
	for (GLint i = 0; i < cubes; i++) {
		Mesh* cube = drawer.create();
		cube->initFromFile("media/models/cube.obj");
		// TODO: See if we can move these calculations to the vertex shader?
		GLfloat angle = angleIncrement * (i + 1);
		cube->rotate(angle, 0.0f, 1.0f, 0.0f);
		cube->translate(10.0f, 0.0f, 0.0f);
		cube->saveMatrix();
	}
	drawer.setup();
}

void Orchestrator::playAudioFrame() {
	std::vector<float> frame = audioProvider.getFrame();
	if (frame.size() != 0) {
		std::vector<float> buckets = frequencyProvider.getFrequencies(&frame, cubes);
		for (int i = 0; i < cubes; i++) {
			drawer.verticallyScaleMesh(i, buckets[i]);
		}
	}
	
	// TODO: Add playing frame out of speakers
}
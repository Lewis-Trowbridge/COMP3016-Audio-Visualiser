#include "Orchestrator.h"

const int radius = 10;

Orchestrator::Orchestrator() {
	drawer = Drawer();
	audioProvider = AudioProvider();
	frequencyProvider = FrequencyProvider();
}

void Orchestrator::openAudioFile(std::string filename) {
	audioProvider.openFile(filename);
}

void Orchestrator::createCubesInCircle(size_t cubes) {
	float angleIncrement = 360.0f / cubes;
	for (int i = 0; i < cubes; i++) {
		Mesh* cube = drawer.create();
		cube->initFromFile("media/models/cube.obj");
		// TODO: See if we can move these calculations to the vertex shader?
		float angle = angleIncrement * (i + 1);
		float x = radius * cos(angle);
		float z = radius * sin(angle);
		cube->translate(x, 0.0f, z);
	}
	drawer.setup();
}
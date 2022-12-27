#include "Orchestrator.h"

const GLint radius = 10;

Orchestrator::Orchestrator() {
	drawer = Drawer();
	audioProvider = AudioProvider();
	frequencyProvider = FrequencyProvider();
}

void Orchestrator::openAudioFile(std::string filename) {
	audioProvider.openFile(filename);
}

void Orchestrator::createCubesInCircle(size_t cubes) {
	GLfloat angleIncrement = 360.0f / cubes;
	for (GLint i = 0; i < cubes; i++) {
		Mesh* cube = drawer.create();
		cube->initFromFile("media/models/cube.obj");
		// TODO: See if we can move these calculations to the vertex shader?
		GLfloat angle = angleIncrement * (i + 1);
		cube->rotate(angle, 0.0f, 1.0f, 0.0f);
		cube->translate(10.0f, 0.0f, 0.0f);
		
	}
	drawer.setup();
}
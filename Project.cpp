#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include<vector>
#include <chrono>
#include <thread>

#include "Project.h"

GLuint texture1;

Orchestrator orchestrator = Orchestrator(16);
//----------------------------------------------------------------------------
//
// init
//
#define BUFFER_OFFSET(a) ((void*)(a))


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		orchestrator.moveCameraRight();
	}
	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		orchestrator.moveCameraLeft();
	}
}

void
init(void)
{
	orchestrator.createCubesInCircle();
	orchestrator.openAudioFile("media/audio/tone.mp3");
}



//----------------------------------------------------------------------------
//
// display
//

void
display(void)
{
	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	glClearBufferfv(GL_COLOR, 0, black);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//// Ensure faces are correctly culled
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	// Ensure that item depth appears correctly
	glEnable(GL_DEPTH_TEST);
	orchestrator.playAudioFrame();
	orchestrator.drawer.draw();
}

int
main(int argc, char** argv)
{
	doctest::Context ctx;
	ctx.applyCommandLine(argc, argv);
	ctx.setOption("abort-after", 10);  // default - stop after 5 failed asserts
	ctx.setOption("no-breaks", true); // override - don't break in the debugger
	int res = ctx.run();              // run test cases unless with --no-run
	if (ctx.shouldExit())              // query flags (and --exit) rely on this
		return res;                   // propagate the result of the tests
	// your actual program execution goes here - only if we haven't exited

	glfwInit();

	GLFWwindow* window = glfwCreateWindow(800, 600, "Visualiser", NULL, NULL);

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, &keyCallback);
	glewInit();

	init();

	while (!glfwWindowShouldClose(window))
	{
		// uncomment to draw only wireframe 
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
		std::this_thread::sleep_for(std::chrono::duration<double>(orchestrator.audioSecondsLength));
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	return res; // + your_program_res
}

#define GLUT_DISABLE_ATEXIT_HACK
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
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		orchestrator.cycleCameraMode();
	}
	if (orchestrator.cameraMode == MANUAL) {
		if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
			orchestrator.moveCameraRight();
		}
		if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
			orchestrator.moveCameraLeft();
		}
	}
}

void
init(void)
{
	orchestrator.createCubesInCircle();
}



//----------------------------------------------------------------------------
//
// display
//

void
display(void)
{
	static const std::vector<float> black = { 0.0f, 0.0f, 0.0f, 0.0f };

	glClearBufferfv(GL_COLOR, 0, black.data());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//// Ensure faces are correctly culled
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	// Ensure that item depth appears correctly
	glEnable(GL_DEPTH_TEST);
	orchestrator.playAudioFrame();
	orchestrator.drawer.draw();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	orchestrator.drawControls();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	// Despite the init name, we use OpenGL 4 by using the latest compatible version string:
	// https://github.com/ocornut/imgui/blob/e57871bb95faec757e51214bc0e1ae29b13258ab/backends/imgui_impl_opengl3.cpp#L86
	ImGui_ImplOpenGL3_Init("#version 430 core");

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

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);

	glfwTerminate();

	return res; // + your_program_res
}

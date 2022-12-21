//////////////////////////////////////////////////////////////////////////////
//
//  Triangles.cpp
//
//////////////////////////////////////////////////////////////////////////////

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include "LoadShaders.h"
#include <glm/glm.hpp> //includes GLM
#include "glm/ext/vector_float3.hpp"
#include "glm/fwd.hpp"
#include <glm/ext/matrix_transform.hpp> // GLM: translate, rotate
#include <glm/ext/matrix_clip_space.hpp> // GLM: perspective and ortho 
#include <glm/gtc/type_ptr.hpp> // GLM: access to the value_ptr
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

#include <iostream>
#include<vector>

#include "Project.h"

GLuint texture1;

Drawer drawer = Drawer();

//----------------------------------------------------------------------------
//
// init
//
#define BUFFER_OFFSET(a) ((void*)(a))


void
init(void)
{
	Mesh* mesh = drawer.create();
	mesh->initFromFile("media/models/cube.obj");
	mesh->translate(-4.0f, 0.0f, 0.0f);
	Mesh* mesh2 = drawer.create();
	mesh2->initFromFile("media/models/cube.obj");
	mesh2->translate(4.0f, 0.0f, 0.0f);
	drawer.setup();
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
	glClear(GL_COLOR_BUFFER_BIT);
	//// Ensure faces are correctly culled
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	drawer.draw(); 
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

	GLFWwindow* window = glfwCreateWindow(800, 600, "Textured Cube", NULL, NULL);

	glfwMakeContextCurrent(window);
	glewInit();

	init();

	while (!glfwWindowShouldClose(window))
	{
		// uncomment to draw only wireframe 
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	return res; // + your_program_res
}

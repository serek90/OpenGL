#include <stdlib.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void printOpenGLversion(void);

int main(int argc, char* argv[])
{

	if (!glfwInit()) exit(EXIT_FAILURE);

	const int height = 720;
	const int width = 1080;

	GLFWwindow* window;
	window = glfwCreateWindow(width, height, "glfw", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	std::cout << "Window is created" << std::endl;

	/* main loop */
	while (!glfwWindowShouldClose(window))
	{
		glViewport(1100, 1100, width, height);
		glClearColor(1, 1, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		// here will be some drawing

		glfwSwapBuffers(window);  //swap buffers
		glfwPollEvents();         //listen for window events
	}

	// Destroy window and terminate glfw
	glfwDestroyWindow(window);
	glfwTerminate();
	std::cout << "Window was destroyed" << std::endl;

	return 0;
}

void printOpenGLversion(void)
{
	const GLubyte* p = glGetString(GL_VERSION);
	std::cout << "OpenGL version: " << p << std::endl;
}
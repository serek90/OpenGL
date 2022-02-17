/*
* This is a very simple program to draw a red triangle
*
* Fell free to use and modify it
*
* created 16.01.2022 by: jseroczy (serek90)
*
*/

#include <stdlib.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int width = 1080;
int height = 720;

void drawSquare()
{
	/* the order metters!!! */
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(-0.5, -0.5, 0);

	glColor3f(1, 0, 0);
	glVertex3f(0.5, -0.5, 0);

	glColor3f(1, 0, 0);
	glVertex3f(0.5, 0.5, 0);

	glColor3f(1, 0, 0);
	glVertex3f(-0.5, 0.5, 0);

	glEnd();
}

int main(int argc, char* argv[])
{
	std::cout << "Start drawing square" << std::endl;

	if (!glfwInit()) exit(EXIT_FAILURE);

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
		glfwGetFramebufferSize(window, &width, &height);  // the window can resize
		glViewport(0, 0, width, height);
		glClearColor(.2, .2, .2, 1); //set background Color to dark grey
		glClear(GL_COLOR_BUFFER_BIT);

		drawSquare ();

		glfwSwapBuffers(window);  //swap buffers
		glfwPollEvents();         //listen for window events
	}

	// Destroy window and terminate glfw
	glfwDestroyWindow(window);
	glfwTerminate();
	std::cout << "Window was destroyed" << std::endl;

	return 0;
}

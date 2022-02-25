/*
* =======================================================
*
*    Filename: glfw_window.cpp
*
*    author: jseroczy
*
* =======================================================
*/

#include "glfw_window.h"


void Window::create(int w = 1080, int h = 720)
{

	window = glfwCreateWindow(width, height, "glfw", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	glfwMakeContextCurrent(window);
	std::cout << "Window is created" << std::endl;
}

void Window::destroy()
{
	glfwDestroyWindow(window);
}

Window::~Window()
{
	destroy();
	std::cout << "Window was destoryed" << std::endl;
}

bool ShouldClose()
{
	return (bool)glfwWindowShouldClose(window);
}

void swapBuffers()
{
	glfwSwapBuffers(window);
}
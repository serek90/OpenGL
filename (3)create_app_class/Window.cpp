#include "Window.h"

void Window::create(int w = 1080, int h = 720)
{
	std::cout << " Start creation" << std::endl;
	window = glfwCreateWindow(600,600, "glfw", NULL, NULL);

	if (!window)
	{
		std::cout << "Failed";
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

Window::Window()
{
	std::cout << "Hello window" << std::endl;
}

bool Window::shouldClose()
{
	return (bool)glfwWindowShouldClose(window);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(window);
}

void Window::setViewport()
{

}
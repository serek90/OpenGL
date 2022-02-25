#pragma once

#include <stdlib.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
private:
	int _width, _height;
	GLFWwindow* window;

public:
	int width() const { return _width; }
	int height() const { return _height; }

	virtual ~Window();
	Window();
	void create(int, int);
	void destroy();
	bool shouldClose();
	void swapBuffers();
	void setViewport();
};


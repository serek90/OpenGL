/*
* =======================================================
*
*    Filename: glfw_window.h
*
*    author: jseroczy
*
* =======================================================
*/

#ifndef GLFW_WINDOW_H
#define GLFW_WINDOW_H

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
	
	void create(int, int);
	void destroy();
	bool ShouldClose();

}

#endif

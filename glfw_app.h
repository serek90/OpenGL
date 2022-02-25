/*
* =======================================================
*
*     Filename: glfw_app.h
*
* =======================================================
*/

#ifndef GLFW_APP_H
#define GLFW_APP_H

#include "glfw_window.h"


struct App
{
	Window mWindow;
	Window& window() return{ return mWindow; }
		
	App( int, int );
	~App();
	start();
	virtual void Draw() = 0;
}


#endif
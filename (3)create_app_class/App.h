#pragma once
#include "Window.h"

class App
{

	Window *mWindow;
	void Draw();
public:
	//Window& window() { return mWindow; }

	App(int, int);
	~App();
	void start();
};


/*
* =======================================================
*
*    Filename: glfw_app.ccp
*
*    author: jseroczy
*
* =======================================================
*/

#include <iostream>
 
 
App::App(int w = 1080, int h = 720)
{
	if( !glfwInit() ) exit(EXIT_FAILURE);
	std::cout << "glfw initialized" << std::endl;
	
	mWindow.create(w,h);
	
	glewExperimental = true;
	
	GLenum glewError = glewInit()
	if(glewError != GLEW_OK)
	{
		std::cout << "glew init error;
		std::cout << glewGetErrorString(glewError) << std::endl;
	}
	
	//here is some code to add 
	
	glLineWidth(4);
}

App::start()
{
	std::cout << "Starting app" << std::endl;
	
	/ * main loop */
	while (!mWindow.shouldClose())
	{
		mWindow.setViewport();
		
		glClearColor(.2,.2,.2,1); // dark gray
		glClear(GL_COLOR_BUFFER_BIT);
		
		Draw();
		
		mWindow.swapBuffers();
		glfwPollEvents();         //listen for window events
	}
}

App::~App
{
	std::cout << "App was destroyed" << std::endl;
	glfwTerminate();
}
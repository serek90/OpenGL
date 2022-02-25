#include "App.h"

App::App(int w = 1080, int h = 720)
{
	if (!glfwInit()) exit(EXIT_FAILURE);
	std::cout << "glfw initialized" << std::endl;

	mWindow = new Window();
	mWindow->create(w, h);

	//glewExperimental = true;

	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		std::cout << "glew init error" << std::endl;
		std::cout << glewGetErrorString(glewError) << std::endl;
	}


	glLineWidth(4);
}

void App::start()
{
	std::cout << "Starting app" << std::endl;

	/* main loop */
		while (!mWindow->shouldClose())
		{
			mWindow->setViewport();

			glClearColor(.2, .2, .2, 1); // dark gray
			glClear(GL_COLOR_BUFFER_BIT);

			Draw();

			mWindow->swapBuffers();
			glfwPollEvents();         //listen for window events
		}
}

App::~App()
{
	delete mWindow;
	std::cout << "App was destroyed" << std::endl;
	glfwTerminate();
}

void App::Draw()
{
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex3f(-1, 0, 0);
	glColor3f(1, 0, 0);
	glVertex3f(0, 1, 0);
	glColor3f(1, 0, 0);
	glVertex3f(1, 0, 0);
	glEnd();
}

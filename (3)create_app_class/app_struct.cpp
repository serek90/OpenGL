/*
* =======================================================
*
*     Filename: app_struct.cpp
*
* =======================================================
*/


#include "glfw_app.h"


class FirstApp : App
{
	FirstApp : App() {};
	
	virtual void Draw()
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
}

int main(int argc, char* argv[])
{
	App app = new App;
	
	app.start();
	
	return 0;
}
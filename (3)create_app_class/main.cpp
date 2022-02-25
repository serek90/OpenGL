
#include "App.h"

int width = 1080;
int height = 720;



int main(int argc, char* argv[])
{
	App *app = new App(1080, 720);

	app->start();

	delete app;

	return 0;
}

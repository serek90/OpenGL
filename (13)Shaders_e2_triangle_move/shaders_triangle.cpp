/*
* My solution to exercise from page:
* https://learnopengl.com
*
*  Shaders exercise 2:
*  Specify a horizontal offset via a uniform and move the triangle 
*  to the right side of the screen in the vertex shader using this offset value
*
* @author: jseroczy (serek90)
*/

/* standard libs */
#include <stdlib.h>
#include <iostream>


/* OpenGL libs */
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

/* window sizes */
int width = 1080;
int height = 720;

float vertices[] = {
	 /* positions  */       /* colors  */
	-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // bottom right 
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // bottom left
	 0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f  // top
};

void prepareShader(void);
unsigned int VAO;
unsigned int VBO;

int main(int argc, char* argv[])
{
	std::cout << "Start drawing triangle" << std::endl;
	glewExperimental = GL_TRUE;
	if (!glfwInit()) exit(EXIT_FAILURE);

	GLFWwindow* window;
	window = glfwCreateWindow(width, height, "glfw", NULL, NULL);
	if (!window)
	{
		std::cout << "glfwCreateWindow";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	std::cout << "Window is created" << std::endl;

	GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult)
	{
		printf("ERROR: %s", glewGetErrorString(GlewInitResult));
		exit(EXIT_FAILURE);
	}

	Shader myShader("shader.vs", "shader.fs");
	prepareShader();
	
	float offset = 0.0f;
	int mark = 0;
	/* main loop */
	while (!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &width, &height);  // the window can resize
		glViewport(0, 0, width, height);
		glClearColor(.2, .2, .2, 1); //set background Color to dark grey
		glClear(GL_COLOR_BUFFER_BIT);

		int vertexOffsetLocation = glGetUniformLocation(myShader.getID(), "Offset");
		printf("%d\n", vertexOffsetLocation);
		myShader.use();

		if (!mark && offset <= 0.5f)offset += 0.002f;
		else if (mark && offset >= -0.5f) offset -= 0.002f;
		else mark = !mark;

		glUniform4f(vertexOffsetLocation, offset, 0.0f, 0.0f, 1.0f);
		
	
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);  //swap buffers
		glfwPollEvents();         //listen for window events
	}

	// Destroy window and terminate glfw
	glfwDestroyWindow(window);
	glfwTerminate();
	std::cout << "Window was destroyed" << std::endl;
	
	return 0;
}

//JSJS TODO: Change name
void prepareShader(void)
{

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	// 1. bind Vertex Array Object
	glBindVertexArray(VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. then set our vertex attributes pointers
	/* position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	/* color attribute */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

}
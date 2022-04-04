/*
* My solution to exercise from page:
* https://learnopengl.com
*
* Draw triangle using shaders and make different color in every corner
*
* copy glm from : https://glm.g-truc.net/0.9.8/index.html
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

/* open GL mathematics */
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

/* window sizes */
int width = 1000;
int height = 1000;

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
	
	//glm::vec4 vec(5.0f, 2.0f, 0.0f, 1.0f);
	//glm::mat4 trans = glm::mat4(1.0f);
	//trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f)); // 
	//vec = trans * vec;

	//std::cout <<  "x = " << vec.x << " y = " << vec.y << " z = " << vec.z << std::endl;
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
	
	/* main loop */
	while (!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &width, &height);  // the window can resize
		glViewport(0, 0, width, height);
		glClearColor(.2, .2, .2, 1); //set background Color to dark grey
		glClear(GL_COLOR_BUFFER_BIT);
		
		//glm::mat4 trans = glm::mat4(1.0f);
		//trans = glm::rotate(trans, glm::radians(0.0f), glm::vec3(0.0, 0.0, 1.0));
		//trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		unsigned int transformLoc = glGetUniformLocation(myShader.getID(), "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		myShader.use();
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
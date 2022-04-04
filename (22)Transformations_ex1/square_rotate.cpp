/*
* My solution to exercise from page:
* https://learnopengl.com
*
* exercise 1 from Transformations:
* Using the last transformation on the container, 
* try switching the order around by first rotating and then translating. 
* See what happens and try to reason why this happens: solution.
*
* stb lib from: https://github.com/nothings/stb
* GLM libs from: https://glm.g-truc.net/0.9.8/index.html
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
/* stb_lib.h */
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
/* GLM libs */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* window sizes */
int width = 1100;
int height = 800;

float vertices[] = {
	// positions          // colors           // texture coords
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};
unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};

void prepareShader(void);
void prepereTexture(void);
unsigned int VAO;
unsigned int VBO;
unsigned int EBO;
unsigned int texture;

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
	prepereTexture();
	prepareShader();

	
	/* main loop */
	while (!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &width, &height);  // the window can resize
		glViewport(0, 0, width, height);
		glClearColor(.2, .2, .2, 1); //set background Color to dark grey
		glClear(GL_COLOR_BUFFER_BIT);

		glm::mat4 trans = glm::mat4(1.0f);

		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, -1.0f));
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		unsigned int transformLoc = glGetUniformLocation(myShader.getID(), "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		myShader.use();

		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &EBO);
	// 1. bind Vertex Array Object
	glBindVertexArray(VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 3. then set our vertex attributes pointers
	/* position attribute */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	/* color attribute */
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	/* texture coridinations */
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

}

void prepereTexture(void)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/* Load image */
	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
}
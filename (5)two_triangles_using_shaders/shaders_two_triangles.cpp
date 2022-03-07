/*
* My solution to exercise from page: 
* https://learnopengl.com
*
* Exercise 1:
* Try to draw 2 triangles next to each other using glDrawArrays by adding more vertices to your data
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

/* window sizes */
int width = 1080;
int height = 720;

float vertices[] = {
	-0.25f, -0.25f, 0.0f,
	 0.25f, -0.25f, 0.0f,
	 0.0f,  0.25f, 0.0f,

	 0.75f, -0.25f, 0.0f,
	 0.5,  0.25f, 0.0f
};

unsigned int indices[] = {  // note that we start from 0!
	0, 1, 2,   // first triangle
	1, 3, 4    // second triangle
};

/* shaders */
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4  FragColor;"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.1f, 0.2f, 1.0f);"
"}\0";

void prepareShader(void);
unsigned int VAO;
unsigned int VBO;
unsigned int EBO;
unsigned int shaderProgram;

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

	prepareShader();
	
	/* main loop */
	while (!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &width, &height);  // the window can resize
		glViewport(0, 0, width, height);
		glClearColor(.2, .2, .2, 1); //set background Color to dark grey
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
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

void prepareShader(void)
{
	/* check variables */
	int  success;
	char infoLog[512];

	/* vertex shader */
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/* fragment shader */
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	/* shader program */
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) 
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	}

	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// 1. bind Vertex Array Object
	glBindVertexArray(VAO);
	// 2. copy our vertices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. copy our index array in a element buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 4. then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}
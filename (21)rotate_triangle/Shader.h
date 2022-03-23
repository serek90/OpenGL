#ifndef SHADER_H
#define SHADER_H

/* openGL headers */
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
	unsigned int ID;

public:
	unsigned int getID() const { return ID;  }
	Shader(const char* vertexPath, const char* fragmentPath);
	void use() const;

};

#endif // !SHADER_H

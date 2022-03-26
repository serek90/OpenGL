#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 ourColor; //output a color to the fragment shader
uniform vec4 Offset;

void main()
{
	gl_Position = vec4(aPos.x + Offset.x, aPos.y + Offset.y, aPos.z, 1.0);
	ourColor = aColor;
}
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

//outputs the color for the fragment shader
out vec3 color;

//inputs the matrix needed for the camera object
uniform mat4 camMatrix;

void main()
{
	gl_Position = camMatrix * vec4(aPos, 1.0);
	color = aColor;
}



#version 460 core
in vec4 colorFromVS;

out vec4 FragColor;

in vec3 color;

void main()
{
	FragColor = vec4(color, 1.0f);
}
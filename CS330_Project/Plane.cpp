#include "Plane.h"

//constructors
Plane::Plane(){};

Plane::Plane(GLfloat x, GLfloat y, GLfloat z, GLfloat length, GLfloat width)
{
	vertices[0] = (x - (width/2));		//vertex 0
	vertices[1] = y;
	vertices[2] = (z - (length / 2));

	vertices[6] = (x + (width / 2));	//vertex 1
	vertices[7] = y;
	vertices[8] = (z - (length / 2));

	vertices[12] = (x + (width / 2));	//vertex 2
	vertices[13] = y;
	vertices[14] = (z + (length / 2));

	vertices[18] = (x - (width / 2));	//vertex 3
	vertices[19] = y;
	vertices[20] = (z + (length / 2));
}

//change the color of the cube
void Plane::ChangeColor(GLfloat r, GLfloat g, GLfloat b)
{
	for (int i = 3; i < 24; i += 6)
	{
		vertices[i] = r;
		vertices[i + 1] = g;
		vertices[i + 2] = b;
	}
}
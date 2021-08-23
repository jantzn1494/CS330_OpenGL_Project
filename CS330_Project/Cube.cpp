#include "Cube.h"

//constructors
Cube::Cube() {};

Cube::Cube(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, GLfloat length)
{
	vertices[0] = x;			//vertex 0
	vertices[1] = y;
	vertices[2] = z;

	vertices[6] = (x + width);	//vertex 1
	vertices[7] = y;
	vertices[8] = z;

	vertices[12] = (x + width);	//vertex 2
	vertices[13] = y;
	vertices[14] = (z + length);

	vertices[18] = x;			//vertex 3
	vertices[19] = y;
	vertices[20] = (z + length);

	vertices[24] = x;			//vertex 4
	vertices[25] = (y - height);
	vertices[26] = (z + length);

	vertices[30] = (x + width);	//vertex 5
	vertices[31] = (y - height);
	vertices[32] = (z + length);

	vertices[36] = (x + width);	//vertex 6
	vertices[37] = (y - height);
	vertices[38] = z;

	vertices[42] = x;			//vertex 7
	vertices[43] = (y - height);
	vertices[44] = z;
}

//change the color of the cube
void Cube::ChangeColor(GLfloat r, GLfloat g, GLfloat b)
{
	for (int i = 3; i < 48; i+=6)
	{
		vertices[i] = r;
		vertices[i + 1] = g;
		vertices[i + 2] = b;
	}
}
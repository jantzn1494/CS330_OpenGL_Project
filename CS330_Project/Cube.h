#ifndef CUBE_CLASS_H
#define CUBE_CLASS_H

#include "shaderClass.h"

class Cube
{
	public:
		//default cube
		GLfloat vertices[48] =
		{
			// COORDINATES				/ COLORS				//
			-0.5f,  0.5f, -0.5f,		0.25f, 0.25f, 0.25f,	// index 0
			 0.5f,  0.5f, -0.5f,		0.25f, 0.25f, 0.25f,	// index 1
			 0.5f,  0.5f,  0.5f,		0.25f, 0.25f, 0.25f,	// index 2
			-0.5f,  0.5f,  0.5f,		0.25f, 0.25f, 0.25f,	// index 3
			-0.5f, -0.5f,  0.5f,		0.25f, 0.25f, 0.25f,	// index 4
			 0.5f, -0.5f,  0.5f,		0.25f, 0.25f, 0.25f,	// index 5
			 0.5f, -0.5f, -0.5f,		0.25f, 0.25f, 0.25f,	// index 6
			-0.5f, -0.5f, -0.5f,		0.25f, 0.25f, 0.25f		// index 7

		};

		// Indices for cube are always the same
		GLuint indices[36] =
		{
			0, 1, 6,
			0, 7, 6,
			0, 2, 1,
			0, 3, 2,
			0, 3, 4,
			0, 4, 7,
			5, 3, 4,
			5, 3, 2,
			5, 7, 4,
			5, 7, 6,
			5, 1, 6,
			5, 1, 2
		};

		//constructors
		Cube();
		Cube(GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height, GLfloat length);

		void ChangeColor(GLfloat r, GLfloat g, GLfloat b);
};

#endif

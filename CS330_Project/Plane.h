#pragma once
#ifndef PLANE_CLASS_H
#define PLANE_CLASS_H

#include "shaderClass.h"

class Plane
{
public:
	//default cube
	GLfloat vertices[24] =
	{
		// COORDINATES				/ COLORS				//
		-1.0f,  0.0f, -1.0f,		0.25f, 0.25f, 0.25f,	// index 0
		-1.0f,	0.0f,  1.0f,		0.25f, 0.25f, 0.25f,	// index 1
		 1.0f,  0.0f,  1.0f,		0.25f, 0.25f, 0.25f,	// index 2
		 1.0f,  0.0f, -1.0f,		0.25f, 0.25f, 0.25f,	// index 3
	};

	// Indices for cube are always the same
	GLuint indices[6] =
	{
		0, 1, 2,
		0, 2, 3
	};

	//constructors
	Plane();
	Plane(GLfloat x, GLfloat y, GLfloat z, GLfloat length, GLfloat width);

	void ChangeColor(GLfloat r, GLfloat g, GLfloat b);
};

#endif
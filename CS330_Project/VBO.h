#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include "shaderClass.h"

class VBO
{
public:
	GLuint ID;
	VBO(GLfloat* verts, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};

#endif
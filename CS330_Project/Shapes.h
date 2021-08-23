#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <vector>

//math header inclusions for GL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#pragma once
using namespace std;

class Circle
{
private:
	vector <GLfloat> verts;		//vector holds vertices to draw circle
	vector <GLushort> indices;	//vector holds indices to draw circle
	float x = 0;	//all circles start at origin
	float y = 0;
	float z = 0;
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.5f; //blue by default
	float a = 1.0f;
	float radius;
	int steps;

public:
	Circle(float radius, int steps)
	{
		this->radius = radius;
		this->steps = steps;
		CreateCircle(); //function fills verts and indices vectors with given info
	}

	vector <GLfloat> GetVertices()
	{
		return verts;
	}

	vector <GLushort> GetIndices()
	{
		return indices;
	}

	/*
	*	CreateCircle() fills verts and indices vectors with correct information. 
	*/
	void CreateCircle()
	{
		float angle = 3.1415926 * 2.0f / steps;
		float prevX = x;
		float prevY = y - radius;
		float newX;
		float newY;

		for (int i = 0; i <= steps; i++)
		{
			newX = radius * sin(angle * i);
			newY = -radius * cos(angle * i);

			//First vertex of triangle is always (x, y, z)
			verts.push_back(x);
			verts.push_back(y);
			verts.push_back(z);
			pushColor();
			indices.push_back(0);
			//Second vertex is the 3rd of the previous triangle
			verts.push_back(prevX);
			verts.push_back(prevY);
			verts.push_back(z);
			pushColor();
			indices.push_back(i + 1);
			//Third vertex is the new coordinates calculated
			verts.push_back(newX);
			verts.push_back(newY);
			verts.push_back(z);
			pushColor();
			indices.push_back(i + 2);
			//Change 3rd vertex to 2nd for next loop cycle
			prevX = newX;
			prevY = newY;
		}
		return;
	}

	void ChangeColor(float r, float g, float b, float a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;

		for (int i = 3; i < verts.size(); i + 3)
		{
			//change rgba values in verts
			verts.at(i++) = r;
			verts.at(i++) = g;
			verts.at(i++) = b;
			verts.at(i++) = a;
		}
		return;
	}

private:
	//pushColor() helper function adds rgba values to verts in CreateCircle function
	void pushColor()
	{
		verts.push_back(r);
		verts.push_back(g);
		verts.push_back(b);
		verts.push_back(a);
	}
}; //end circle class


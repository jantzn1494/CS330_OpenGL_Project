#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "shaderClass.h"

class Camera
{
	public:
		//stores main vectors of camera
		glm::vec3 cameraPosition;
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight = glm::vec3(1.0f, 0.0f, 0.0f);

		//timing
		float deltaTime = 0.0f; //time between current frame and last frame
		float lastFrame = 0.0f;

		// Prevents the camera from jumping around when first clicking left click
		bool firstClick = true;

		//stores width and height of window
		int width;
		int height;

		//mouse state
		float lastX;
		float lastY;

		//adjusts speed of camera and sensitivity while looking around
		float cameraSpeed = 2.5f;
		float yaw = -90.0f;	//yaw is initialized to -90.0 because 0.0 results in a vector pointing to the right
		float pitch = 0.0f;

		//constructor
		Camera(int width, int height, glm::vec3 position);

		//updates and exports camera matrix to vertex shader
		void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
		
		//handles inputs via keyboard
		void Inputs(GLFWwindow* window);

		//handles input via mouse cursor
		void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);

		//handles input via mouse scroller
		void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif

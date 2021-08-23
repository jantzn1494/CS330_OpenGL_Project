#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	lastX = width / 2.0;
	lastY = height / 2.0;
	cameraPosition = position;
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
	//initialize matrices
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	//makes camera look at correct position
	view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
	//adds perspective
	projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

	//export matrix to vertex shader program
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::Inputs(GLFWwindow* window)
{
	//escape to close
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	float cameraOffset = cameraSpeed * deltaTime;

	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)	//press W to move forward
	{
		cameraPosition += cameraOffset * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)	//press A to move left
	{
		cameraPosition += cameraOffset * -glm::normalize(glm::cross(cameraFront, cameraUp));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)	//press S to move back
	{
		cameraPosition -= cameraOffset * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)	//press D to move right
	{
		cameraPosition += cameraOffset * glm::normalize(glm::cross(cameraFront, cameraUp));
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)	//press Q to move up
	{
		cameraPosition -= cameraUp * cameraOffset;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)	//press E to move down
	{
		cameraPosition += cameraUp * cameraOffset;
	}
}

//handles input via mouse cursor
void Camera::MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	//if first mouse call, get position
	if (firstClick)
	{
		lastX = xpos;
		lastY = ypos;
		firstClick= false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f; //change this to change camera rotation speed
	xoffset = xoffset * sensitivity;
	yoffset = yoffset * sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	//make sure that when pitch runs out of bounds that the screen is not flipped
	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	//temporary vector to transform using new values
	glm::vec3 tempFront;
	tempFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	tempFront.y = sin(glm::radians(pitch));
	tempFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	//set camera front to normalized temp vector
	cameraFront = glm::normalize(tempFront);
}

//handles input via mouse scroller
void Camera::MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (cameraSpeed >= 1.0f && cameraSpeed <= 25.0f) //scroll up for more speed, down for less
	{
		cameraSpeed += yoffset;
	}
	if (cameraSpeed <= 1.0f) //Minimum speed
	{
		cameraSpeed = 1.0f;
	}
	if (cameraSpeed >= 25.0f) //Maximum speed
	{
		cameraSpeed = 25.0f;
	}
}
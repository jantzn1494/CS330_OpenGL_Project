#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <vector>


//math header inclusions for GL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Unnamed namespace
namespace
{
	//define settings
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//Stores the GL data relative to a given mesh
	struct GLMesh
	{
		GLuint vao;		//Vertex array object
		GLuint vbos[2]; //vertex buffer objects
		GLuint nIndeces;//number of indices of mesh
	};

	//GLFW window
	GLFWwindow* window = nullptr;
	//Triangle Mesh Data
	GLMesh gMesh;
	//shader program
	GLuint gProgramID;
}

//------------------------------------------------------------------------------------------------------------------------------------
class Circle
{
private:
	GLMesh circleMesh;

	std::vector <GLfloat> verts;		//vector holds vertices to draw circle
	std::vector <GLushort> indices;	//vector holds indices to draw circle
	float x = 0;	//all circles start at origin
	float y = 0;
	float z = 0;
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f; //blue by default
	float a = 0.5f;
	float radius;
	int steps;

public:
	Circle(float radius, int steps)
	{
		this->radius = radius;
		this->steps = steps;
		CreateCircle(); //function fills verts and indices vectors with given info
	}

	std::vector <GLfloat> GetVertices()
	{
		return verts;
	}

	std::vector <GLushort> GetIndices()
	{
		return indices;
	}

	/*
	*	CreateCircle() fills verts and indices vectors with correct information.
	*/
	void CreateCircle()
	{
		float angle = 3.1415926 * 2.0f / float(steps);
		float prevX = x;
		float prevY = y - radius;
		float newX;
		float newY;

		for (int i = 0; i <= steps; i++)
		{
			newX = radius * cos(i * angle);
			newY = radius * sin(i * angle);

			//First vertex of triangle is always (x, y, z)
			verts.push_back(x);
			verts.push_back(y);
			verts.push_back(z);
			pushColor(i);
			indices.push_back(0);
			//Second vertex is the 3rd of the previous triangle
			verts.push_back(prevX);
			verts.push_back(prevY);
			verts.push_back(z);
			pushColor(i);
			indices.push_back(i + 1);
			//Third vertex is the new coordinates calculated
			verts.push_back(newX);
			verts.push_back(newY);
			verts.push_back(z);
			pushColor(i);
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

		for (int i = 3; i < verts.size(); i++)
		{
			//change rgba values in verts
			if (i % 3 == 0)
			{
				verts.at(i++) = r;
				verts.at(i++) = g;
				verts.at(i++) = b;
				verts.at(i++) = a;
			}
		}
		return;
	}

private:
	//pushColor() helper function adds rgba values to verts in CreateCircle function
	//it also separates triangles into different colors
	void pushColor(int num)
	{
		int special = (num / 3) % 3;
		if (special == 0)
		{
			verts.push_back(r);
			verts.push_back(g);
			verts.push_back(1.0f);
			verts.push_back(a);
		}
		else if (special == 1)
		{
			verts.push_back(1.0f);
			verts.push_back(g);
			verts.push_back(b);
			verts.push_back(a);
		}
		else
		{
			verts.push_back(r);
			verts.push_back(1.0f);
			verts.push_back(b);
			verts.push_back(a);
		}
	}
}; //-----------------------------------------end circle class-------------------------------------------------------


//user defined functions
bool UInitialize(GLFWwindow** window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void UCreateMesh(GLMesh& mesh);
void UDestroyMesh(GLMesh& mesh);
void URender();
bool UCreateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource, GLuint& programID);
void UDestroyShaderProgram(GLuint programID);
void UDrawObject(GLMesh& mesh, std::vector <GLfloat> vertices, std::vector <GLushort> indicesVec);

//----------------------------------------Vertex Shader Program Source Code-----------------------------------------------
const char* vertexShaderSource =
"#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec4 colorFromVBO;\n"

"out vec4 colorFromVS;\n"

"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"

"void main()\n"
"{\n"
"	gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
"	colorFromVS = colorFromVBO;\n"
"}\n\0";

//Fragment Shader Program Source Code
const char* fragmentShaderSource =
"#version 460 core\n"
"in vec4 colorFromVS;\n"

"out vec4 FragColor;\n"

"void main()\n"
"{\n"
"	FragColor = vec4(colorFromVS);\n"
"}\n\0";

int main(void)
{
	//initialize GLFW/GLEW and create window
	if (!UInitialize(&window))
	{
		return -1;
	}

	//Create circle object
	Circle circle = Circle(0.5, 20);

	//Create mesh

	UCreateMesh(gMesh);

	UDrawObject(gMesh, circle.GetVertices(), circle.GetIndices()); //creates VBO

	//create shader program
	if (!UCreateShaderProgram(vertexShaderSource, fragmentShaderSource, gProgramID))
	{
		return -1;
	}

	//sets background color to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//render loop
	while (!glfwWindowShouldClose(window))
	{
		//get input
		processInput(window);

		//render frame
		URender();

		//check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//release mesh
	UDestroyMesh(gMesh);

	//release shader
	UDestroyShaderProgram(gProgramID);

	//terminate, delete allocated resources
	glfwTerminate();

	return 0;
}//end main

//function to initialize GLFW/GLEW properties and create a window
bool UInitialize(GLFWwindow** window)
{
	//initialize and configure OpenGL
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create window object
	//display error message if window creation fails
	*window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MODULE 3 ASSIGNMENT", NULL, NULL);
	if (*window == NULL)
	{
		std::cout << "Failed to create window." << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(*window);

	//set window size using callback function for resize option
	glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);

	//GLEW initialization
	glewExperimental = GL_TRUE;
	GLenum GlewInitResult = glewInit();

	if (GLEW_OK != GlewInitResult)
	{
		std::cout << glewGetErrorString(GlewInitResult) << std::endl;
		return false;
	}

	return true;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

//whenever the window size is changed this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

/*
*	CreateCylinder()
*/

//Function to render
void URender()
{
	//enable z depth
	glEnable(GL_DEPTH_TEST);

	//clear the background and z buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	//Scaling done here
	//Default is 1
	glm::mat4 scale = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));
	//Rotation done here
	//Default is 0 degrees
	glm::mat4 rotation = glm::rotate(0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	//Translation done here
	//Default is origin
	glm::mat4 translation = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
	//Model matrix : remember transformations are done right to left with matrices
	//Use commented code for matrix operations
	//glm::mat4 model = translation * rotation * scale;

	//Model matrix : identity matrix (model will be at origin)
	glm::mat4 model = glm::mat4(1.0f);

	//Transforms the camera: move the camera back (z axis)
	//Default is -1
	glm::mat4 view = glm::lookAt(
		glm::vec3(0, 0, 2), //EYE::Camera is at this location in World Space
		glm::vec3(0, 0, 0),	 //CENTER::Camera looks at this location
		glm::vec3(0, 1, 0)   //UP::Head is up, (0, -1, 0) to look upside down
	);

	//Creates an orthographic projection
	//glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.f);

	//Projection matrix : 45 degree Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

	//set the shader to be used
	glUseProgram(gProgramID);

	//Retrieves and passes transform matrices to shader program
	GLint modelLoc = glGetUniformLocation(gProgramID, "model");
	GLint viewLoc = glGetUniformLocation(gProgramID, "view");
	GLint projLoc = glGetUniformLocation(gProgramID, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	//Activate the VBOs contained within the mesh's VAO
	glBindVertexArray(gMesh.vao);

	//Draws the triangle
	glDrawElements(GL_TRIANGLES, gMesh.nIndeces, GL_UNSIGNED_SHORT, NULL);

	//Deactivate the VAO
	glBindVertexArray(0);
}

//UDrawObject takes in a vector of vertices and a vector of indices
//to draw the object.
void UDrawObject(GLMesh& mesh, std::vector <GLfloat> vertices, std::vector <GLushort> indicesVec)
{
	//Specifies Normalized Device Coordinates (x,y,z) and color (r,g,b,a) for triangle vertices

	glGenVertexArrays(1, &mesh.vao); //can generate multiple VAOs or buffers at the same time
	glBindVertexArray(mesh.vao);

	//Create buffers, one for vertex data, another for indices
	glGenBuffers(2, mesh.vbos);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]); //activates buffer
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW); //send data to GPU

	mesh.nIndeces = sizeof(indicesVec) / sizeof(indicesVec[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesVec.size() * sizeof(GLushort), &indicesVec[0], GL_STATIC_DRAW);

	//create vertex attrib pointer for screen coordinates
	const GLuint floatsPerVertex = 3; //Number of coordinates for vertex
	const GLuint floatsPerColor = 4; // r,g,b,a

	//Strides between vertex coordinates is 7 floats (3 coordinates + 4 floats for color definition)
	GLint stride = sizeof(float) * (floatsPerVertex + floatsPerColor);

	//Creates the Vertex attrib pointer
	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, floatsPerColor, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
	glEnableVertexAttribArray(1);
}

//Implements the UCreateMesh function
void UCreateMesh(GLMesh& mesh)
{
	//Specifies Normalized Device Coordinates (x,y,z) and color (r,g,b,a) for triangle vertices
	GLfloat verts[] =
	{
		//Vertices				//color
		 0.0f, 0.5f, 0.0,		1.0f, 1.0f, 1.0f, 1.0f,	//white
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 1.0f, 1.0f,	//fuchsia
		 0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 0.0f, 1.0f, //yellow
		 0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f, 1.0f, //blue
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 1.0f, 1.0f	//cyan
	};

	//Index data
	GLushort indices[] =
	{
		0, 1, 2,	//Front triangle
		0, 2, 3,	//Right Triangle
		0, 3, 4,	//Back Triangle
		0, 4, 1,	//Left Triangle
		1, 2, 3,	//Bottom Left Triangle
		1, 3, 4		//Bottom Right Triangle
	};

	glGenVertexArrays(1, &mesh.vao); //can generate multiple VAOs or buffers at the same time
	glBindVertexArray(mesh.vao);

	//Create buffers, one for vertex data, another for indices
	glGenBuffers(2, mesh.vbos);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[0]); //activates buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW); //send data to GPU

	mesh.nIndeces = sizeof(indices) / sizeof(indices[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//create vertex attrib pointer for screen coordinates
	const GLuint floatsPerVertex = 3; //Number of coordinates for vertex
	const GLuint floatsPerColor = 4; // r,g,b,a

	//Strides between vertex coordinates is 7 floats (3 coordinates + 4 floats for color definition)
	GLint stride = sizeof(float) * (floatsPerVertex + floatsPerColor);

	//Creates the Vertex attrib pointer
	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, floatsPerColor, GL_FLOAT, GL_FALSE, stride, (char*)(sizeof(float) * floatsPerVertex));
	glEnableVertexAttribArray(1);
}

void UDestroyMesh(GLMesh& mesh)
{
	glDeleteVertexArrays(1, &mesh.vao);
	glDeleteBuffers(2, mesh.vbos);
}

//Implements the UCreateShaders function
bool UCreateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource, GLuint& programID)
{
	//build and compile shader program
	//vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//check for compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}

	//fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//check for compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}

	//link shaders
	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);
	//check for linking errors
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return false;
	}

	//Use Shader Program
	glUseProgram(programID);

	return true;
}

void UDestroyShaderProgram(GLuint programID)
{
	glDeleteProgram(programID);
}
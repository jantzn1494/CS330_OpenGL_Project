//header files for organization
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"
#include"Cube.h"
#include"Plane.h"

//Unnamed namespace
namespace
{
	const unsigned int width = 800;
	const unsigned int height = 800;

	//GLFW window
	GLFWwindow* window = nullptr;

	//camera object initialization
	Camera camera(width, height, glm::vec3(0.0f, 5.0f, 20.0f));

	GLfloat lightVertices[] =
	{ //     COORDINATES     //
		-0.1f, -0.1f,  0.1f,
		-0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f, -0.1f,
		 0.1f, -0.1f,  0.1f,
		-0.1f,  0.1f,  0.1f,
		-0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f, -0.1f,
		 0.1f,  0.1f,  0.1f
	};

	GLuint lightIndices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};
}

//user defined functions
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void cursor_callback(GLFWwindow* window, double xpos, double ypos);

int main()
{
	//initialize objects
	Plane plane1 = Plane(0.0f, -0.01f, 0.0f, 50.0f, 50.0f);	//desk
	plane1.ChangeColor(0.6f, 0.75f, 0.85f);

	Cube book1 = Cube(0.0f, 1.2f, 0.0f, 0.1f, 1.2f, 8.25f);	//binder
	book1.ChangeColor(0.5f, 0.8f, 0.5f);

	Cube book2 = Cube(0.1f, 1.2f, 0.0f, 5.5f, 0.1f, 8.25f);	//cover
	book2.ChangeColor(0.79f, 0.8f, 0.79f);

	Cube book3 = Cube(0.1f, 1.1f, 0.12f, 5.4f, 1.0f, 8.02f);//pages
	book3.ChangeColor(0.8f, 0.8f, 0.6f);

	Cube book4 = Cube(0.1f, 0.1f, 0.0f, 5.5f, 0.1f, 8.25f);	//back
	book4.ChangeColor(0.79f, 0.8f, 0.79f);

	Cube wallet1 = Cube(1.5f, 0.75f, -4.75f, 3.5f, 0.375f, 4.5f);	//top
	wallet1.ChangeColor(0.2f, 0.2f, 0.2f);

	Cube wallet2 = Cube(1.5f, 0.375f, -4.75f, 3.5f, 0.375f, 4.5f);	//bottom
	wallet2.ChangeColor(0.17f, 0.17f, 0.18f);

	Cube console = Cube(-2.75f, 5.0f, -3.125f, 0.6f, 4.0f, 7.0f);	//screen
	console.ChangeColor(0.1f, 0.1f, 0.1f);

	Cube dock1 = Cube(-2.0f, 4.0f, -3.0f, 0.25f, 4.0f, 6.75f);		//front
	dock1.ChangeColor(0.18f, 0.18f, 0.18f);

	Cube dock2 = Cube(-3.0f, 1.0f, -3.0f, 1.0f, 1.0f, 6.75f);		//bottom
	dock2.ChangeColor(0.18f, 0.18f, 0.18f);

	Cube dock3 = Cube(-4.0f, 4.0f, -3.0f, 1.0f, 4.0f, 6.75f);		//back
	dock3.ChangeColor(0.18f, 0.18f, 0.18f);

	Cube controller1 = Cube(-2.75f, 5.0f, 3.875f, 0.6f, 4.0f, 1.5f);//left

	Cube controller2 = Cube(-2.75f, 5.0f, -4.625f, 0.6f, 4.0f, 1.5f);//right

																//left
	Cube button1 = Cube(-2.15f, 2.9f, 4.865f, 0.1f, 0.25f, 0.25f);		//left
	button1.ChangeColor(0.1f, 0.1f, 0.1f);

	Cube button2 = Cube(-2.15f, 3.25f, 4.515f, 0.1f, 0.25f, 0.25f);		//up
	button2.ChangeColor(0.1f, 0.1f, 0.1f);

	Cube button3 = Cube(-2.15f, 2.9f, 4.165f, 0.1f, 0.25f, 0.25f);		//right
	button3.ChangeColor(0.1f, 0.1f, 0.1f);

	Cube button4 = Cube(-2.15f, 2.55f, 4.515f, 0.1f, 0.25f, 0.25f);		//down
	button4.ChangeColor(0.1f, 0.1f, 0.1f);

																//right
	Cube button5 = Cube(-2.15f, 4.25f, -3.635f, 0.1f, 0.25f, 0.25f);	//left
	button5.ChangeColor(0.1f, 0.1f, 0.1f);

	Cube button6 = Cube(-2.15f, 4.6f, -3.985f, 0.1f, 0.25f, 0.25f);		//up
	button6.ChangeColor(0.1f, 0.1f, 0.1f);

	Cube button7 = Cube(-2.15f, 4.25f, -4.335f, 0.1f, 0.25f, 0.25f);	//right
	button7.ChangeColor(0.1f, 0.1f, 0.1f);

	Cube button8 = Cube(-2.15f, 3.9f, -3.985f, 0.1f, 0.25f, 0.25f);		//down
	button8.ChangeColor(0.1f, 0.1f, 0.1f);

	/*
	Cylinder pencil = Cylinder();
	pencil.ChangeColor(0.1f, 0.1f, 0.1f);

	Cylinder eraser = Cylinder();
	eraser.ChangeColor(0.1f, 0.1f, 0.1f);
	*/

	Cube pencil = Cube(2.8f, 1.55f, -2.0f, 0.25f, 0.25f, 7.0f);
	pencil.ChangeColor(0.9f, 0.9f, 0.1f);

	Cube eraser = Cube(2.8f, 1.55f, 5.0f, 0.25f, 0.25f, 0.25f);
	eraser.ChangeColor(0.9f, 0.5f, 0.5f);

	Cube joy1 = Cube(-2.15f, 4.5f, 4.35f, 0.1f, 0.5f, 0.5f);
	joy1.ChangeColor(0.1f, 0.1f, 0.1f);

	Cube joy2 = Cube(-2.15f, 3.1f, -4.15f, 0.1f, 0.5f, 0.5f);
	joy2.ChangeColor(0.1f, 0.1f, 0.1f);

	//initialize glfw window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//create window object and check if window is created successfully
	window = glfwCreateWindow(width, height, "CS330 Project", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window..." << std::endl;
		glfwTerminate();
		return -1; //end program, error
	}

	//use newly created window object
	glfwMakeContextCurrent(window);

	//GLEW initialization
	glewExperimental = GL_TRUE;
	GLenum GlewInitResult = glewInit();

	if (GLEW_OK != GlewInitResult)
	{
		std::cout << glewGetErrorString(GlewInitResult) << std::endl;
		return -1;
	}

	//Create shader object using text files default.frag and default.vert
	Shader shaderProgram("default.vert", "default.frag");

	//Generate VAO and bind them --------------------------------------------------------------
	VAO VAO1;
	VAO1.Bind();
	//Generate VBO and link it to vertices
	VBO VBO1(book1.vertices, sizeof(book1.vertices));
	//Generate EBO and link it to indices
	EBO EBO1(book1.indices, sizeof(book1.indices));
	//Link and bind objects
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//repeat process with all objects
	VAO VAO2;
	VAO2.Bind();
	VBO VBO2(book2.vertices, sizeof(book2.vertices));
	EBO EBO2(book2.indices, sizeof(book2.indices));
	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();

	VAO VAO3;
	VAO3.Bind();
	VBO VBO3(book3.vertices, sizeof(book3.vertices));
	EBO EBO3(book3.indices, sizeof(book3.indices));
	VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO3.Unbind();
	VBO3.Unbind();
	EBO3.Unbind();

	VAO VAO4;
	VAO4.Bind();
	VBO VBO4(book4.vertices, sizeof(book4.vertices));
	EBO EBO4(book4.indices, sizeof(book4.indices));
	VAO4.LinkAttrib(VBO4, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO4.LinkAttrib(VBO4, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO4.Unbind();
	VBO4.Unbind();
	EBO4.Unbind();

	VAO VAO5;
	VAO5.Bind();
	VBO VBO5(plane1.vertices, sizeof(plane1.vertices));
	EBO EBO5(plane1.indices, sizeof(plane1.indices));
	VAO5.LinkAttrib(VBO5, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO5.LinkAttrib(VBO5, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO5.Unbind();
	VBO5.Unbind();
	EBO5.Unbind();

	VAO VAO6;
	VAO6.Bind();
	//Generate VBO and link it to vertices
	VBO VBO6(wallet1.vertices, sizeof(wallet1.vertices));
	//Generate EBO and link it to indices
	EBO EBO6(wallet1.indices, sizeof(wallet1.indices));
	//Link and bind objects
	VAO6.LinkAttrib(VBO6, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO6.LinkAttrib(VBO6, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO6.Unbind();
	VBO6.Unbind();
	EBO6.Unbind();

	VAO VAO7;
	VAO7.Bind();
	//Generate VBO and link it to vertices
	VBO VBO7(wallet2.vertices, sizeof(wallet2.vertices));
	//Generate EBO and link it to indices
	EBO EBO7(wallet2.indices, sizeof(wallet2.indices));
	//Link and bind objects
	VAO7.LinkAttrib(VBO7, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO7.LinkAttrib(VBO7, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO7.Unbind();
	VBO7.Unbind();
	EBO7.Unbind();

	VAO VAO8;
	VAO8.Bind();
	//Generate VBO and link it to vertices
	VBO VBO8(console.vertices, sizeof(console.vertices));
	//Generate EBO and link it to indices
	EBO EBO8(console.indices, sizeof(console.indices));
	//Link and bind objects
	VAO8.LinkAttrib(VBO8, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO8.LinkAttrib(VBO8, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO8.Unbind();
	VBO8.Unbind();
	EBO8.Unbind();

	VAO VAO9;
	VAO9.Bind();
	//Generate VBO and link it to vertices
	VBO VBO9(dock1.vertices, sizeof(dock1.vertices));
	//Generate EBO and link it to indices
	EBO EBO9(dock1.indices, sizeof(dock1.indices));
	//Link and bind objects
	VAO9.LinkAttrib(VBO9, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO9.LinkAttrib(VBO9, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO9.Unbind();
	VBO9.Unbind();
	EBO9.Unbind();

	VAO VAO10;
	VAO10.Bind();
	//Generate VBO and link it to vertices
	VBO VBO10(dock2.vertices, sizeof(dock2.vertices));
	//Generate EBO and link it to indices
	EBO EBO10(dock2.indices, sizeof(dock2.indices));
	//Link and bind objects
	VAO10.LinkAttrib(VBO10, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO10.LinkAttrib(VBO10, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO10.Unbind();
	VBO10.Unbind();
	EBO10.Unbind();

	VAO VAO11;
	VAO11.Bind();
	//Generate VBO and link it to vertices
	VBO VBO11(dock3.vertices, sizeof(dock3.vertices));
	//Generate EBO and link it to indices
	EBO EBO11(dock3.indices, sizeof(dock3.indices));
	//Link and bind objects
	VAO11.LinkAttrib(VBO11, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO11.LinkAttrib(VBO11, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO11.Unbind();
	VBO11.Unbind();
	EBO11.Unbind();

	VAO VAO12;
	VAO12.Bind();
	//Generate VBO and link it to vertices
	VBO VBO12(controller1.vertices, sizeof(controller1.vertices));
	//Generate EBO and link it to indices
	EBO EBO12(controller1.indices, sizeof(controller1.indices));
	//Link and bind objects
	VAO12.LinkAttrib(VBO12, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO12.LinkAttrib(VBO12, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO12.Unbind();
	VBO12.Unbind();
	EBO12.Unbind();

	VAO VAO13;
	VAO13.Bind();
	//Generate VBO and link it to vertices
	VBO VBO13(controller2.vertices, sizeof(controller2.vertices));
	//Generate EBO and link it to indices
	EBO EBO13(controller2.indices, sizeof(controller2.indices));
	//Link and bind objects
	VAO13.LinkAttrib(VBO13, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO13.LinkAttrib(VBO13, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO13.Unbind();
	VBO13.Unbind();
	EBO13.Unbind();

	VAO VAO14;
	VAO14.Bind();
	//Generate VBO and link it to vertices
	VBO VBO14(button1.vertices, sizeof(button1.vertices));
	//Generate EBO and link it to indices
	EBO EBO14(button1.indices, sizeof(button1.indices));
	//Link and bind objects
	VAO14.LinkAttrib(VBO14, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO14.LinkAttrib(VBO14, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO14.Unbind();
	VBO14.Unbind();
	EBO14.Unbind();

	VAO VAO15;
	VAO15.Bind();
	//Generate VBO and link it to vertices
	VBO VBO15(button2.vertices, sizeof(button2.vertices));
	//Generate EBO and link it to indices
	EBO EBO15(button2.indices, sizeof(button2.indices));
	//Link and bind objects
	VAO15.LinkAttrib(VBO15, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO15.LinkAttrib(VBO15, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO15.Unbind();
	VBO15.Unbind();
	EBO15.Unbind();

	VAO VAO16;
	VAO16.Bind();
	//Generate VBO and link it to vertices
	VBO VBO16(button3.vertices, sizeof(button3.vertices));
	//Generate EBO and link it to indices
	EBO EBO16(button3.indices, sizeof(button3.indices));
	//Link and bind objects
	VAO16.LinkAttrib(VBO16, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO16.LinkAttrib(VBO16, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO16.Unbind();
	VBO16.Unbind();
	EBO16.Unbind();

	VAO VAO17;
	VAO17.Bind();
	//Generate VBO and link it to vertices
	VBO VBO17(button4.vertices, sizeof(button4.vertices));
	//Generate EBO and link it to indices
	EBO EBO17(button4.indices, sizeof(button4.indices));
	//Link and bind objects
	VAO17.LinkAttrib(VBO17, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO17.LinkAttrib(VBO17, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO17.Unbind();
	VBO17.Unbind();
	EBO17.Unbind();

	VAO VAO18;
	VAO18.Bind();
	//Generate VBO and link it to vertices
	VBO VBO18(button5.vertices, sizeof(button5.vertices));
	//Generate EBO and link it to indices
	EBO EBO18(button5.indices, sizeof(button5.indices));
	//Link and bind objects
	VAO18.LinkAttrib(VBO18, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO18.LinkAttrib(VBO18, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO18.Unbind();
	VBO18.Unbind();
	EBO18.Unbind();

	VAO VAO19;
	VAO19.Bind();
	//Generate VBO and link it to vertices
	VBO VBO19(button6.vertices, sizeof(button6.vertices));
	//Generate EBO and link it to indices
	EBO EBO19(button6.indices, sizeof(button6.indices));
	//Link and bind objects
	VAO19.LinkAttrib(VBO19, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO19.LinkAttrib(VBO19, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO19.Unbind();
	VBO19.Unbind();
	EBO19.Unbind();

	VAO VAO20;
	VAO20.Bind();
	//Generate VBO and link it to vertices
	VBO VBO20(button7.vertices, sizeof(button7.vertices));
	//Generate EBO and link it to indices
	EBO EBO20(button7.indices, sizeof(button7.indices));
	//Link and bind objects
	VAO20.LinkAttrib(VBO20, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO20.LinkAttrib(VBO20, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO20.Unbind();
	VBO20.Unbind();
	EBO20.Unbind();

	VAO VAO21;
	VAO21.Bind();
	//Generate VBO and link it to vertices
	VBO VBO21(button8.vertices, sizeof(button8.vertices));
	//Generate EBO and link it to indices
	EBO EBO21(button8.indices, sizeof(button8.indices));
	//Link and bind objects
	VAO21.LinkAttrib(VBO21, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO21.LinkAttrib(VBO21, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO21.Unbind();
	VBO21.Unbind();
	EBO21.Unbind();

	VAO VAO22;
	VAO22.Bind();
	//Generate VBO and link it to vertices
	VBO VBO22(pencil.vertices, sizeof(pencil.vertices));
	//Generate EBO and link it to indices
	EBO EBO22(pencil.indices, sizeof(pencil.indices));
	//Link and bind objects
	VAO22.LinkAttrib(VBO22, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO22.LinkAttrib(VBO22, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO22.Unbind();
	VBO22.Unbind();
	EBO22.Unbind();

	VAO VAO23;
	VAO23.Bind();
	//Generate VBO and link it to vertices
	VBO VBO23(eraser.vertices, sizeof(button8.vertices));
	//Generate EBO and link it to indices
	EBO EBO23(eraser.indices, sizeof(button8.indices));
	//Link and bind objects
	VAO23.LinkAttrib(VBO23, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO23.LinkAttrib(VBO23, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO23.Unbind();
	VBO23.Unbind();
	EBO23.Unbind();

	VAO VAO24;
	VAO24.Bind();
	//Generate VBO and link it to vertices
	VBO VBO24(joy1.vertices, sizeof(joy1.vertices));
	//Generate EBO and link it to indices
	EBO EBO24(joy1.indices, sizeof(joy1.indices));
	//Link and bind objects
	VAO24.LinkAttrib(VBO24, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO24.LinkAttrib(VBO24, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO24.Unbind();
	VBO24.Unbind();
	EBO24.Unbind();

	VAO VAO25;
	VAO25.Bind();
	//Generate VBO and link it to vertices
	VBO VBO25(joy2.vertices, sizeof(joy2.vertices));
	//Generate EBO and link it to indices
	EBO EBO25(joy2.indices, sizeof(joy2.indices));
	//Link and bind objects
	VAO25.LinkAttrib(VBO25, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO25.LinkAttrib(VBO25, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO25.Unbind();
	VBO25.Unbind();
	EBO25.Unbind();

	//Enable depth buffer
	glEnable(GL_DEPTH_TEST);

	//use inputs to set camera position
	glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//while window is not closed, process commands in while loop
	while (!glfwWindowShouldClose(window))
	{

		// setup timing
		float currentFrame = glfwGetTime();
		camera.deltaTime = currentFrame - camera.lastFrame;
		camera.lastFrame = currentFrame;

		//define color of background
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		//clear back buffer, depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Tell OpenGL which Shader Program to use
		shaderProgram.Activate();

		//handles camera inputs
		camera.Inputs(window);

		//updates and exports the camera matrix to vertex shader
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");


		//Bind VAO
		VAO1.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(book1.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);

		VAO2.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(book2.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);

		VAO3.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(book3.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);

		VAO4.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(book4.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);

		VAO5.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(plane1.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);

		VAO6.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(wallet1.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);

		VAO7.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(wallet2.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);

		VAO8.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(console.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);

		VAO9.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(dock1.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);

		VAO10.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(dock2.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);

		VAO11.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(dock3.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);

		VAO12.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(controller1.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);

		VAO13.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(controller2.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);

		VAO14.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(button1.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);

		VAO15.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(button2.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);

		VAO16.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(button3.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);

		VAO17.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(button4.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);

		VAO18.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(button5.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);

		VAO19.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(button6.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);

		VAO20.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(button7.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);

		VAO21.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(button8.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);

		VAO22.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(pencil.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);

		VAO23.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(eraser.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);

		VAO24.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(joy1.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);

		VAO25.Bind();
		//Draw object within array
		glDrawElements(GL_TRIANGLES, (sizeof(joy2.indices) / sizeof(GLfloat)), GL_UNSIGNED_INT, NULL);


		//Swap dual buffer
		glfwSwapBuffers(window);
		//window responds to GLFW events
		glfwPollEvents();
	}

	//Delete all created objects
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	VAO2.Delete();
	VBO2.Delete();
	EBO2.Delete();
	VAO3.Delete();
	VBO3.Delete();
	EBO3.Delete();
	VAO4.Delete();
	VBO4.Delete();
	EBO4.Delete();
	shaderProgram.Delete();

	glfwTerminate();

	return 0;
}//-------------end main-------------

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//handles input via mouse scroller
	camera.MouseScrollCallback(window, xoffset, yoffset);
}

void cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
	//handles input via mouse cursor
	camera.MousePositionCallback(window, xpos, ypos);
}
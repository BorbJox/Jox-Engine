/*//Standard library includes:
#include <iostream>
#include <thread>

//OpenGL includes:
#define GLFW_INCLUDE_GLU
#define GLFW_DLL
#include "glew/glew.h"
//#include "glew/wglew.h"
#include "glfw/glfw3.h"
GLFWwindow* window;
#include "glm/glm.hpp"
using namespace glm;

// Shader sources
const GLchar* vertexSource =
"#version 150 core\n"
"in vec2 position;"
"in vec3 color;"
"out vec3 Color;"
"void main() {"
"   Color = color;"
"   gl_Position = vec4(position, 0.0, 1.0);"
"}";
const GLchar* fragmentSource =
"#version 150 core\n"
"in vec3 Color;"
"out vec4 outColor;"
"void main() {"
"   outColor = vec4(Color, 1.0);"
"}";

//OpenGL Stuff
GLuint vao;
GLuint vbo;
GLuint ebo;
GLuint vertexShader;
GLuint fragmentShader;
GLuint shaderProgram;

void pause()
{
	std::cout << std::endl << "Press Enter to continue...";
	getchar();
}


int initialiseWindow() {
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		pause();
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 8);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//Window creation
	window = glfwCreateWindow(800, 600, "Jox's Playground", nullptr, nullptr); // Windowed, can do Fullscreen here
	//GLFWwindow* window = glfwCreateWindow(1920, 1080, "OpenGL", glfwGetPrimaryMonitor(), nullptr); // Fullscreen

	if (window == NULL){
		fprintf(stderr, "Failed to open GLFW window. Your GPU is probably not compatible with this version of OpenGL.\n");
		pause();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//GLEW Init
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		pause();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	return 0;
}

void initialiseOpenGLBuffers() {
	// Create Vertex Array Object
	//GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create a Vertex Buffer Object and copy the vertex data to it
	//GLuint vbo;
	glGenBuffers(1, &vbo);

	GLfloat vertices[] = {
		-0.25f, 0.25f, 1.0f, 0.0f, 0.0f, // Top-left
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // Top-right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Create an element array
	//GLuint ebo;
	glGenBuffers(1, &ebo);

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	// Create and compile the vertex shader
	//GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Create and compile the fragment shader
	//GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// Link the vertex and fragment shader into a shader program
	//GLuint shaderProgram = glCreateProgram();
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
}

void exitProgram() {
	//Close OpenGL stuff and terminate GLFW
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vbo);

	glDeleteVertexArrays(1, &vao);


	glfwTerminate();
}


int main()
{
	//Starting the Window
	if (initialiseWindow() == -1)
		return -1;
	
	//Initialise OpenGL arrays and vbos and stuff
	initialiseOpenGLBuffers();

	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw a rectangle from the 2 triangles using 6 indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
	}

	//Closing the Window
	exitProgram();
	return 0;
}*/
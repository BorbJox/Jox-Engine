#pragma once
#include <iostream>

#define GLFW_INCLUDE_GLU
#define GLFW_DLL
#include "glew\glew.h"
#include "glfw\glfw3.h"
#include "glm\glm.hpp"



/*
Initialises glew and glfw, sets background colour, window size and input mode.
*/
class Window {
public:
	//Create a window of given size in pixels
	Window(int width, int height);
	~Window();
	GLFWwindow* getWindow() { return theWindow;	}
	bool isMousePressed();
	//Returns the cursor position in pixels
	glm::vec2 getCursorPos();
	bool isKeyPressed(GLint key);
	bool isKeyReleased(GLint key);
	void centerCursor();
private:
	//Pointer to the OpenGL window
	GLFWwindow* theWindow;
	void pause();
	int windowWidth;
	int windowHeight;
};


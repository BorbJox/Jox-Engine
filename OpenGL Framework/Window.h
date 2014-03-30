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
	Window();
	~Window();
	GLFWwindow* getWindow() { return theWindow;	}
	bool isMousePressed();
	glm::vec2 getCursorPos();
	bool isKeyPressed(GLint key);
	bool isKeyReleased(GLint key);
	void centerCursor();
private:
	GLFWwindow* theWindow;
	void pause();
};


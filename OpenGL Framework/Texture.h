#pragma once
#include "glew\glew.h"
#include "glfw\glfw3.h"
#include "glm\glm.hpp"
#include "soil\SOIL.h"
#include <string>

/*
Holds the OpenGL texture ID and the path name. Can bind the texture for immediate use.
*/
class Texture {
public:
	Texture(std::string filename);
	~Texture();
	void bindTexture();
private:
	std::string filename;
	GLuint textureID;
};


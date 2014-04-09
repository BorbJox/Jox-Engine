#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "glew\glew.h"

struct shaderParameters {
	bool handles3D;
	bool handlesColour;
	bool handlesTextures;
	bool handlesLighting;
	bool handlesNormals;
};

class Shader {
public:
	/* Shader pipeline provides a program to link and use.
	To use:
	1.Construct, with paths to glsl source code of shaders
	2.Check if ShaderLoaded() correctly (Optional)
	3.If you use other programs, call LinkProgram() before using this one again
	Current shader limitations: Need position, colour and UV values, with uniform modelTranform (mat4), colourAmount (0.0 - 1.0) and textureSampler (sampler2D) values.
	*/
	Shader(shaderParameters params, std::string vertex, std::string fragment);
	~Shader();
	GLuint getShaderProgram() { return program; }
	bool ShaderLoaded() { return !loadFailed; }
	bool handlesLighting() { return params.handlesLighting; }
	bool LinkProgram();
private:
	shaderParameters params;
	bool LoadShaderFile(std::string from, std::string &into);
	GLuint GenerateShader(std::string from, GLenum type);
	GLuint program;
	GLuint vertexShader;
	GLuint fragmentShader;
	bool loadFailed;
	
};


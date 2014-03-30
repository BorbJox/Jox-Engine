#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "glew\glew.h"
using namespace std;



class Shader {
public:
	/* Shader pipeline provides program to link and use.
	To use:
	1.Construct, with paths to glsl source code of shaders
	2.Check if ShaderLoaded() correctly (Optional)
	3.If you use other programs, call LinkProgram() before using this one again
	*/
	Shader(bool handles3D, bool handlesTextures, bool handlesNormals, string vertex, string fragment, string geometry = "", string tcs = "", string tes = "");
	~Shader();
	GLuint getShaderProgram() { return program; }
	bool ShaderLoaded() { return !loadFailed; }
	bool handles3D() { return enabled3D; }
	bool handlesTextures() { return enabledTextures; }
	bool handlesNormals() { return enabledNormals; }
	bool LinkProgram();
	void deleteProgram();
private:
	bool LoadShaderFile(string from, string &into);
	GLuint GenerateShader(string from, GLenum type);
	GLuint program;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint geometryShader = 0;
	GLuint tcsShader = 0;
	GLuint tesselationShader = 0;
	bool loadFailed;
	bool enabled3D;
	bool enabledTextures;
	bool enabledNormals;
	
};


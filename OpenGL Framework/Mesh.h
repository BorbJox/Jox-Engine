#pragma once
#include <vector>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include "glew\glew.h"
#include "glfw\glfw3.h"
#include "glm\glm.hpp"

/*
Reads vertex information from a .ply file, and buffers it to the GPU
*/
class Mesh {
public:
	Mesh(std::string filename);
	~Mesh();
	GLuint getVAOID() { return vao; }
	GLuint getPositionBufferID() { return positionBuffer; }
	GLuint getNormalBufferID() { return normalBuffer; }
	GLuint getColourBufferID() { return colourBuffer; }
	GLuint getUVBufferID() { return uvBuffer; }
	GLuint getIndicesBufferID() { return indicesBuffer; }
	bool hasIncompleteData() { return incompleteData; }
	int getTriangleCount() { return triangleCount; }
private:
	bool incompleteData;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> colours;
	std::vector<int> indices;
	GLuint vao;
	GLuint positionBuffer;
	GLuint normalBuffer;
	GLuint colourBuffer;
	GLuint uvBuffer;
	GLuint indicesBuffer;
	GLuint type;
	void BufferData();
	unsigned int triangleCount;
};


#pragma once
#include <vector>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include "glm\glm.hpp"

struct triangleVertexIndices {
	unsigned int first;
	unsigned int second;
	unsigned int third;
};

class Mesh {
public:
	Mesh(std::string filename);
	~Mesh();
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> colours;
	std::vector<triangleVertexIndices> elements;
};


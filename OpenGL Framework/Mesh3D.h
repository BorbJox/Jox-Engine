#pragma once
#include "Entity.h"
#include <vector>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>


class Mesh3D : public Entity {

public:
	Mesh3D();
	Mesh3D(std::string modelPath, std::string texturePath, glm::vec3 pos);
	~Mesh3D();
	std::vector<glm::vec3> getVertexData() { return vertices; }
	std::vector<glm::vec2> getUVData() { return uvs; }
	std::vector<glm::vec3> getNormalData() { return normals; }
	void setTexture(std::string path) { texturePath = path; }
	std::string getTexturePath() { return texturePath; }
	bool failedToLoad = false;
private:
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::string texturePath;
	bool loadMesh(std::string path);
};


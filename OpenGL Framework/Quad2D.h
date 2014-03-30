#pragma once
#include <string>
#include "glm\glm.hpp"
#include "Entity.h"

class Quad2D : public Entity {
public:
	Quad2D(std::string texturePath, float width, float height, glm::vec3 pos);
	~Quad2D();
	std::vector<glm::vec3> getVertexData() { return vertices; }
	std::vector<glm::vec2> getUVData() { return uvs; }
	std::string getTexturePath() { return texturePath; }
	void setTexture(std::string path) { texturePath = path; }
	float width, height;
private:
	std::string texturePath;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> generateVertices(float width, float height);
	std::vector<glm::vec2> uvs;
};


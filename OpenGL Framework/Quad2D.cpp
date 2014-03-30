#include "Quad2D.h"

Quad2D::Quad2D(std::string texturePath, float width, float height, glm::vec3 pos) : texturePath(texturePath), Entity(pos), width(width), height(height) {
	vertices = generateVertices(width, height);
	uvs.push_back(glm::vec2(1.0f, 0.0f));
	uvs.push_back(glm::vec2(0.0f, 0.0f));
	uvs.push_back(glm::vec2(0.0f, 1.0f));
	uvs.push_back(glm::vec2(0.0f, 1.0f));
	uvs.push_back(glm::vec2(1.0f, 1.0f));
	uvs.push_back(glm::vec2(1.0f, 0.0f));
}

Quad2D::~Quad2D() {

}

std::vector<glm::vec3> Quad2D::generateVertices(float width, float height) {

	std::vector<glm::vec3> tempVertices;
	float left = width * -0.5f;
	float right = width * 0.5f;
	float up = height * 0.5f;
	float down = height * -0.5f;
	tempVertices.push_back(glm::vec3(right, up, 0.0f));
	tempVertices.push_back(glm::vec3(left, up, 0.0f));
	tempVertices.push_back(glm::vec3(left, down, 0.0f));
	tempVertices.push_back(glm::vec3(left, down, 0.0f));
	tempVertices.push_back(glm::vec3(right, down, 0.0f));
	tempVertices.push_back(glm::vec3(right, up, 0.0f));
	return tempVertices;
}
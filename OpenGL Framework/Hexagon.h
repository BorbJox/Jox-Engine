#pragma once
#include "Entity.h"
#include <vector>

class Hexagon : public Entity {
public:
	Hexagon(float radius, glm::vec3 colour, glm::vec2 position);
	~Hexagon();
	glm::vec3 getColour() { return colour; }
	//Must have a tied RenderObject
	void changeColour(glm::vec3 col);
	vector<glm::vec3> getVertexData() { return vertices; }
private:
	vector<glm::vec3> vertices;
	glm::vec3 colour;
};


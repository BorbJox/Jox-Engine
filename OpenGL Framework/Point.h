#pragma once
#include "glm\glm.hpp"
#include "Entity.h"
class Point : public Entity {
public:
	Point();
	Point(glm::vec3 position);
	Point(glm::vec3 position, glm::vec3 colour);
	~Point();
	glm::vec3 getColour() { return colour; }
	void setColour(glm::vec3 colour) { this->colour = colour; }
private:
	glm::vec3 colour;
};


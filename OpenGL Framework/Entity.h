#pragma once
#include "glm\glm.hpp"
#include "RenderObject.h"
//Generic Entity class for game calculations excluding physics
class Entity
{
public:
	Entity();
	Entity(glm::vec3 position);
	~Entity();
	glm::vec3 getPosition() { return position; }
	void setPosition(glm::vec3 pos);
	void setRenderObject(RenderObject* r) { renderObject = r; }
	RenderObject* getRenderObject() { return renderObject; }
private:
	glm::vec3 position;
	RenderObject* renderObject;
};
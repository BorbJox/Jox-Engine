#pragma once
#include "glm\glm.hpp"

//Plane class used to form world boundaries
class PhysicsPlane {
public:
	PhysicsPlane(glm::vec3 position, glm::vec3 normal);
	~PhysicsPlane();
	const glm::vec3 position;
	const glm::vec3 normal;
};


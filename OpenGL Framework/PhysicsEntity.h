#pragma once
#include "glm\glm.hpp"
#include "Entity.h"
#include <iostream>

struct EntityState {
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
};

const float DAMPING_FACTOR = 0.99f;
const float GRAVITY_ACCEL = -9.81f;
const float ELASTICITY = 0.9f;

//Generic Physics wrapper class to hold physics related information and calculate the integrated movement
class PhysicsEntity {
public:
	PhysicsEntity(Entity* e);
	~PhysicsEntity();
	glm::vec3 getPosition() { return linkedEntity->getPosition(); }
	Entity* getLinkedEntity() { return linkedEntity; }
	glm::vec3 getAcceleration() { return currentState.acceleration; }
	glm::vec3 getVelocity() { return currentState.velocity; }
	void overrideAcceleration(glm::vec3 acceleration) { currentState.acceleration = acceleration; }
	void overrideVelocity(glm::vec3 velocity) { currentState.velocity = velocity; }
	void doStep(double deltaTime);
private:
	Entity* linkedEntity;
	EntityState currentState;
	void updateEntityPosition() { linkedEntity->setPosition(currentState.position); }
};


#include "PhysicsEntity.h"


PhysicsEntity::PhysicsEntity(Entity* e) : linkedEntity(e) {
	currentState.position = e->getPosition();
	currentState.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	currentState.acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
}


PhysicsEntity::~PhysicsEntity() {
}

void PhysicsEntity::doStep(double deltaTime) {
	//Rest state
	if (currentState.velocity.length() > 0.01f) {
		//Semi-implicit Euler's
		currentState.position = linkedEntity->getPosition();
		currentState.acceleration.y += GRAVITY_ACCEL;
		currentState.velocity += currentState.acceleration * (float)deltaTime;
		currentState.velocity *= DAMPING_FACTOR;
		currentState.position += currentState.velocity * (float)deltaTime;
		updateEntityPosition();
		//Reset acceleration to keep gravity effect in bounds
		currentState.acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	}
}
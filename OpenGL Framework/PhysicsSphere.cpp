#include "PhysicsSphere.h"


PhysicsSphere::PhysicsSphere(Sphere3D* s) : PhysicsEntity(s), connectedEntity(s) {
	radius = s->getRadius();
	//make the spheres heavier while calculating their inverse mass
	inverseMass = 1 / (radius * radius * radius) * 60.0f;
}


PhysicsSphere::~PhysicsSphere() {
}

//Checks distance and compares it to radius
bool PhysicsSphere::isCollidingWith(PhysicsSphere* s) {
	float xd = getPosition().x - s->getPosition().x;
	float yd = getPosition().y - s->getPosition().y;
	float zd = getPosition().z - s->getPosition().z;
	float squaredDistance = (xd*xd) + (yd*yd) + (zd*zd);
	float squaredDiameter = getRadius() + s->getRadius() * getRadius() + s->getRadius();
	return squaredDistance < squaredDiameter;
}

//Checks dot product of distance from centre with plane's normal
bool PhysicsSphere::isCollidingWith(PhysicsPlane* p) {
	float dist = glm::dot(p->normal, getPosition() - p->position);
	return dist < radius;
}

//Pushes sphere out using projection, and modifies its velocity using impulse
void PhysicsSphere::correctOverlapWith(PhysicsSphere* s) {	
	glm::vec3 sumVelocities = getVelocity() + s->getVelocity();
	glm::vec3 tempDistance = getPosition() - s->getPosition();
	glm::vec3 pushNormal = glm::normalize(tempDistance);
	float nudgeAmount = radius + s->getRadius() - tempDistance.length() + 0.01f;
	float impulse = -(1 + ELASTICITY) * glm::dot(sumVelocities, pushNormal) / (glm::dot(pushNormal, pushNormal * (inverseMass + s->getInverseMass())));
	getLinkedEntity()->setPosition(getPosition() + pushNormal * nudgeAmount);
	overrideVelocity(getVelocity() + (impulse * inverseMass) * pushNormal);
	s->overrideVelocity(s->getVelocity() - (impulse * s->getInverseMass()) * pushNormal);
}

//Pushes sphere out of the plane and mirrors the velocity to bounce
void PhysicsSphere::correctOverlapWith(PhysicsPlane* p) {
	glm::vec3 tempDistVector = getPosition() - p->position;
	float dist = glm::dot(p->normal, tempDistVector);
	float nudgeAmount = radius - dist + 0.0001f;
	glm::vec3 newPos = getPosition() + (glm::normalize(tempDistVector) * nudgeAmount);
	getLinkedEntity()->setPosition(newPos);
	glm::vec3 newVelocity = (-2.0f * glm::dot(getVelocity(), p->normal) * p->normal) + getVelocity();
	
	overrideVelocity(ELASTICITY * newVelocity);
}
#pragma once
#include "Sphere3D.h"
#include "PhysicsEntity.h"
#include "PhysicsPlane.h"

//Sphere class which handles collisions with other spheres and planes
class PhysicsSphere : public PhysicsEntity {
public:
	PhysicsSphere(Sphere3D* s);
	~PhysicsSphere();
	bool isCollidingWith(PhysicsSphere* s);
	bool isCollidingWith(PhysicsPlane* p);
	void correctOverlapWith(PhysicsSphere* s);
	void correctOverlapWith(PhysicsPlane* p);
	float getRadius() { return radius; }
	float getInverseMass() { return inverseMass; }
	Sphere3D* getLinkedEntity() { return connectedEntity; }
private:
	Sphere3D* connectedEntity;
	float radius;
	float inverseMass;
};


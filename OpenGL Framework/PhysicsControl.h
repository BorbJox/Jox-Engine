#pragma once
#include <vector>
#include "PhysicsSphere.h"
#include "PhysicsPlane.h"
#include "Entity.h"

//Physics wrapper class to iterate over the physics objects and calculate collisions and movement
class PhysicsControl {
public:
	PhysicsControl(std::vector<PhysicsEntity*> entities);
	~PhysicsControl();
	void doPhysicsStep(double deltaTime);
	void overwriteControlledEntities(std::vector<PhysicsEntity*> entities) { this->entities = entities; }
	void clearEntities() { entities.clear(); spheres.clear(); boundingPlanes.clear(); }
	void addEntity(PhysicsEntity* e) { entities.push_back(e); }
	void addSphere(PhysicsSphere* s) { spheres.push_back(s); }
	void addPlane(PhysicsPlane* p) { boundingPlanes.push_back(p); }
	void handleSphereCollisions();
private:
	std::vector<PhysicsEntity*> entities;
	std::vector<PhysicsSphere*> spheres;
	std::vector<PhysicsPlane*> boundingPlanes;
};


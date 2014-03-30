#include "PhysicsControl.h"


PhysicsControl::PhysicsControl(std::vector<PhysicsEntity*> entities) : entities(entities) {

}


PhysicsControl::~PhysicsControl() {
	for each (PhysicsPlane* p in boundingPlanes)
		delete p;
	for each (PhysicsSphere* s in spheres)
		delete s;
	for each (PhysicsEntity* e in entities)
		delete e;
}

void PhysicsControl::doPhysicsStep(double deltaTime) {

	//Handle collisions and change velocities
	handleSphereCollisions();

	//Do a step in time according to the current accelerations and velocities (no collision detection)
	for each (PhysicsEntity* e in entities) {
		e->doStep(deltaTime);
	}
}

void PhysicsControl::handleSphereCollisions() {
	for (unsigned int i = 0; i < spheres.size(); i++) {
		for (unsigned int j = i + 1; j < spheres.size(); j++) {
			if (spheres[i]->isCollidingWith(spheres[j])) {
				
				spheres[i]->correctOverlapWith(spheres[j]);
				//change velocity and acceleration
				//set flag
			}
		}
		for each (PhysicsPlane* p in boundingPlanes) {
			if (spheres[i]->isCollidingWith(p)) {
				spheres[i]->correctOverlapWith(p);
				//if flag set, interpolate vectors (A+B)/2
				//change velocity & accel
			}
		}
	}
}
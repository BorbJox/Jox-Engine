#pragma once
#include <vector>
#include "glm\gtc\matrix_transform.hpp"
//#include "glm\gtx\transform.hpp"
#include "Entity.h"
#include "Renderer.h"
#include "RenderObject.h"
#include "Point.h"
#include "PointCloud.h"
#include "Mesh3D.h"
#include "Quad2D.h"
#include "Sphere3D.h"
#include "PhysicsSphere.h"
#include "Hexagon.h"

/*Converts in-game entities into RenderObjects and pushes them to the renderer
	Must have an addEntity(____) implemented for any type of entity you want to draw.*/
class Scene {
public:
	Scene(std::vector<Shader*> shaders, Renderer* r);
	~Scene();
	void addEntity(Entity* e);
	//Other Entity type calls to this:
	void addEntity(Point* e);
	void addEntity(PointCloud* e);
	void addEntity(Mesh3D* m);
	void addEntity(Quad2D* q);
	void addEntity(Sphere3D* m);
	void addEntity(PhysicsEntity* e); 
	void addEntity(PhysicsSphere* s);
	void addEntity(Hexagon* h);
	void moveCamera(glm::mat4 newViewMatrix);
	std::vector<RenderObject*> getObjectArray() { return renderObjects; }
	std::vector<Entity*> getEntityArray() { return entities; }
	std::vector<PhysicsEntity*> getPhysicsEntityArray() { return physicsEntities; }
private:
	std::vector<Entity*> entities;
	std::vector<Shader*> shaders;
	std::vector<RenderObject*> renderObjects;
	std::vector<PhysicsEntity*> physicsEntities;
	Renderer* rendererHandle;
	//bool newData = false;
	glm::mat4 view;
	glm::mat4 projection;
};


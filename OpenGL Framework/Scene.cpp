#include "Scene.h"

Scene::Scene(std::vector<Shader*> shaders, Renderer* r) : shaders(shaders), rendererHandle(r) {
	view = glm::lookAt(glm::vec3(4.0f, 3.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	projection = glm::perspective(75.0f, 4.0f / 3.0f, 0.1f, 100.0f);
}


Scene::~Scene() {
	for each (Entity* e in entities)
		delete e;
	for each (RenderObject* ro in renderObjects) {
		delete ro;
	}
	for each (PhysicsEntity* pe in physicsEntities) {
		delete pe;
	}
}

void Scene::addEntity(Entity* e)  {
	entities.push_back(e);
	RenderObject* temp = new RenderObject(shaders[0]);
	e->setRenderObject(temp);
	rendererHandle->addObject(temp);
}

void Scene::addEntity(Point* p) {
	entities.push_back(p);
	RenderObject* temp = new RenderObject(GL_POINTS, std::vector<glm::vec3>(1, glm::vec3(0.0f,0.0f,0.0f)), shaders[1], p->getPosition());
	p->setRenderObject(temp);
	renderObjects.push_back(temp);
	rendererHandle->addObject(temp);
}

void Scene::addEntity(PointCloud* p) {
	entities.push_back(p);
	std::vector<glm::vec3> tempPointPos;
	for each (Point* point in p->getVector()) {
		tempPointPos.push_back(point->getPosition());
	}
	RenderObject* temp = new RenderObject(GL_POINTS, tempPointPos, shaders[0], p->getPosition());
	p->setRenderObject(temp);
	renderObjects.push_back(temp);
	rendererHandle->addObject(temp);
}

void Scene::addEntity(Mesh3D* m) {
	entities.push_back(m);
	RenderObject* temp = new RenderObject(GL_TRIANGLES, m->getVertexData(), m->getUVData(), m->getNormalData(), shaders[3], m->getPosition());
	temp->assignTexture(m->getTexturePath());
	m->setRenderObject(temp);
	renderObjects.push_back(temp);
	rendererHandle->addObject(temp);
}

void Scene::addEntity(Sphere3D* m) {
	entities.push_back(m);
	RenderObject* temp = new RenderObject(GL_TRIANGLES, m->getVertexData(), m->getUVData(), m->getNormalData(), shaders[3], m->getPosition());
	temp->assignTexture(m->getTexturePath());
	m->setRenderObject(temp);
	renderObjects.push_back(temp);
	rendererHandle->addObject(temp);
}

void Scene::addEntity(Quad2D* q) {
	entities.push_back(q);
	RenderObject* temp = new RenderObject(GL_TRIANGLES, q->getVertexData(), q->getUVData(), shaders[4], q->getPosition());
	temp->assignTexture(q->getTexturePath());
	q->setRenderObject(temp);
	renderObjects.push_back(temp);
	rendererHandle->addObject(temp);
}

void Scene::addEntity(PhysicsEntity* e) {
	physicsEntities.push_back(e);
	addEntity(e->getLinkedEntity());
}

void Scene::addEntity(PhysicsSphere* e) {
	physicsEntities.push_back(e);
	addEntity(e->getLinkedEntity());
}

void Scene::addEntity(Hexagon* h) {
	entities.push_back(h);
	RenderObject* temp = new RenderObject(GL_TRIANGLE_FAN, h->getVertexData(), h->getColour(), shaders[5], h->getPosition());
	h->setRenderObject(temp);
	renderObjects.push_back(temp);
	rendererHandle->addObject(temp);
}

void Scene::moveCamera(glm::mat4 newViewMatrix) {
	view = newViewMatrix;
	rendererHandle->setCamera(projection, view);
}
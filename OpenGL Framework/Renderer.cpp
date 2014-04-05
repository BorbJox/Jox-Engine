#include "Renderer.h"


Renderer::Renderer(Window &w) {
	windowHandle = &w;
}


Renderer::~Renderer() {
	
}

void Renderer::renderScene() {
	glfwMakeContextCurrent(windowHandle->getWindow());
	for each (RenderObject* obj in objectArray)
		obj->Draw(viewMatrix, projectionMatrix);
}

int Renderer::addObject(RenderObject* object) {
	objectArray.push_back(object);
	return objectArray.size() - 1;
}

void Renderer::overwriteObject(int i, RenderObject* object) {
	delete objectArray[i];
	objectArray[i] = object;
}

void Renderer::overwriteObjectArray(vector<RenderObject*> newArray) {
	objectArray = newArray;
}

void Renderer::deleteObject(int i) {
	delete objectArray[i];
	objectArray[i] = nullptr;
}

void Renderer::clearCurrentObjects() {
	objectArray.clear();
}

void Renderer::setCamera(glm::mat4 projection, glm::mat4 view) {
	projectionMatrix = projection;
	viewMatrix = view;
}
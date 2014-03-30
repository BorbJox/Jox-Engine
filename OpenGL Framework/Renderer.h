#pragma once
#include "Window.h"
#include "Shader.h"
#include "RenderObject.h"
#include <vector>

//OpenGL renderer class
class Renderer {

public:
	Renderer(Window &w);
	~Renderer();
	//Render all current RenderObjects in the vector onto the screen.
	void renderScene();
	//Adds the pointer to the vector and returs the index of it.
	int addObject(RenderObject* object);
	//Overwrites the RenderObject at the given index.
	void overwriteObject(int i, RenderObject* object);
	//Replaces the current array of drawn objects with the provided one (does not delete any previous objects).
	void overwriteObjectArray(vector<RenderObject*> newArray);
	//Delete the RenderObject at that location (pointer become null pointer).
	void deleteObject(int i);
	//Don't forget to delete pointers if you're not going to use the objects any more!
	void clearCurrentObjects();
	Window* getWindow() { return windowHandle; }
	void setCamera(glm::mat4 projection, glm::mat4 view);
private:
	vector<RenderObject*> objectArray; 
	Window* windowHandle;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
};


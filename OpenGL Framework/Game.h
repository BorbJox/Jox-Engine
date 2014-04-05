#pragma once
#include "Scene.h"
#include "irrKlang\irrKlang.h"
#include "Window.h"
#include "PhysicsControl.h"
#include "AIControl.h"

/*
Manages Scenes
*/
class Game
{
public:
	Game(Renderer* r);
	~Game();
	//Update the game entities by stepping forward one frame
	void update();
	PhysicsControl* getPhysicsController() { return physicsController; }
private:
	Renderer* r;
	PhysicsControl* physicsController;
	AIControl* AIController;
	std::vector<Scene*> scenes = std::vector<Scene*>(4);
	int counter = 1;
	Scene* create3DTestScene();
	Scene* createMainMenu();
	Scene* createPhysicsBox();
	Scene* createHexagonGrid();
	int currentSceneID;
	irrklang::ISound* music;
	void switchScene(int sceneID);
	std::vector<Shader*> shaders;
	irrklang::ISoundEngine* soundEngine;
	glm::vec3 cameraPos = glm::vec3(7.0f, 5.0f, 5.0f);
	float cameraPitch = 3.14f;
	float cameraYaw = 0.0f;
	glm::vec3 cameraDirection = glm::vec3(glm::cos(cameraPitch) * glm::sin(cameraYaw), glm::sin(cameraPitch), glm::cos(cameraPitch) * glm::cos(cameraYaw));
	glm::vec3 cameraUp;
	glm::mat4 viewMatrix;
	void recalculateViewMatrix();
	void recalculateCameraPitchYaw();
	void recalculateCameraPosition();
};


#include "Game.h"


Game::Game(Renderer* r) : r(r) {
	shaders.push_back(new Shader(true, false, false, "shaders/generic3DVertex.glsl", "shaders/genericFragment.glsl"));
	shaders.push_back(new Shader(false, false, false, "shaders/genericVertex.glsl", "shaders/genericFragment.glsl"));
	shaders.push_back(new Shader(true, true, false, "shaders/genericTextured3DVertex.glsl", "shaders/genericTexturedFragment.glsl"));
	shaders.push_back(new Shader(true, true, true, "shaders/litTextured3DVertex.glsl", "shaders/litTextured3DFragment.glsl"));
	shaders.push_back(new Shader(false, true, false, "shaders/textured2DVertex.glsl", "shaders/genericTexturedFragment.glsl"));
	shaders.push_back(new Shader(false, false, false, "shaders/coloured2DVertex.glsl", "shaders/coloured2DFragment.glsl"));

	currentSceneID = 0;
	scenes[currentSceneID] = (createMainMenu());
	
	physicsController = new PhysicsControl(scenes[currentSceneID]->getPhysicsEntityArray());
}


Game::~Game() {
	for each (Scene* s in scenes)
		delete s;
	for each (Shader* s in shaders) {
		s->deleteProgram();
		delete s;
	}
	if (soundEngine)
		soundEngine->removeAllSoundSources();
	delete physicsController;
	delete AIController;
}

void Game::update() {
	glm::vec2 cursorPos;
	switch (currentSceneID) {
	case 0:
		cursorPos = r->getWindow()->getCursorPos();
		if (cursorPos.x >= 320 && cursorPos.x <= 480 && cursorPos.y >= 360 && cursorPos.y <= 440 && r->getWindow()->isMousePressed())
			switchScene(3);
		break;
	case 1:
		scenes[currentSceneID]->getEntityArray().back()->setPosition(glm::vec3(glm::cos((float)counter*0.02f)*6.0f, 1.0f, glm::sin((float)counter*0.02f)*6.0f));
		scenes[currentSceneID]->getEntityArray()[1]->setPosition(glm::vec3(glm::cos((float)counter*0.02f)*0.8f, glm::sin((float)counter*0.02f), 0.0f)*0.8f);
		recalculateCameraPitchYaw();
		recalculateCameraPosition();
		recalculateViewMatrix();
		scenes[1]->moveCamera(viewMatrix);
		if (music) {
			music->setPosition(irrklang::vec3df(scenes[currentSceneID]->getEntityArray().back()->getPosition().x, scenes[currentSceneID]->getEntityArray().back()->getPosition().y, scenes[currentSceneID]->getEntityArray().back()->getPosition().z));
			irrklang::vec3df position(cameraPos.x, cameraPos.y, cameraPos.z);
			irrklang::vec3df camPos(cameraPos.x, cameraPos.y, cameraPos.z);
			irrklang::vec3df camDir(cameraDirection.x, cameraDirection.y, cameraDirection.z);
			irrklang::vec3df camUp(cameraUp.x, -cameraUp.y, cameraUp.z);
			soundEngine->setListenerPosition(camPos, camDir, irrklang::vec3df(0,0,0), camUp);
		}
		counter++;
		if (counter > 1000000)
			counter = 1;
		break;
	case 2:
		recalculateCameraPitchYaw();
		recalculateCameraPosition();
		recalculateViewMatrix();
		scenes[2]->moveCamera(viewMatrix);

		counter++;
		break;
	case 3:
		//Moving the arrow
		if (r->getWindow()->isKeyPressed(GLFW_KEY_LEFT)) {
			if (counter > 1) {
				counter--;
			} else {
				counter = 111;
			}
		}
		if (r->getWindow()->isKeyPressed(GLFW_KEY_RIGHT)) {
			if (counter < 111) {
				counter++;
			} else {
				counter = 1;
			}
		}
		
		scenes[currentSceneID]->getEntityArray().back()->setPosition(AIController->getHexagons()[counter]->getAttachedHex()->getPosition());
		//Changing cost of tiles on the fly (does not change colour appearance)
		if (r->getWindow()->isKeyPressed(GLFW_KEY_ENTER)) {
			switch (AIController->getHexagons()[counter]->getCost())
			{
			case -1:
				AIController->getHexagons()[counter]->setCost(1);
				AIController->getHexagons()[counter]->setPassable(true);
				break;
			case 1:
				AIController->getHexagons()[counter]->setCost(2);
				AIController->getHexagons()[counter]->setPassable(true);
				break;
			case 2:
				AIController->getHexagons()[counter]->setCost(4);
				AIController->getHexagons()[counter]->setPassable(true);
				break;
			case 4:
				AIController->getHexagons()[counter]->setCost(-1);
				AIController->getHexagons()[counter]->setPassable(false);
				break;
			default:
				AIController->getHexagons()[counter]->setCost(1);
				AIController->getHexagons()[counter]->setPassable(true);
				break;
			}
		}
		//Calculating the path towards the arrow's position
		if (r->getWindow()->isKeyPressed(GLFW_KEY_SPACE)) {
			//Reseting path dots
			int i = scenes[currentSceneID]->getEntityArray().size() - 2;
			for (int j = 20; j > 0; --j)
				scenes[currentSceneID]->getEntityArray()[i-j]->setPosition(glm::vec3(-1.0f, -1.0f, -1.0f));
			//Drawing new dots
			std::vector<pathNode*> viableNodes = AIController->calculatePath(AIController->getHexagons()[counter]);
			for each (pathNode* n in viableNodes) {
				scenes[currentSceneID]->getEntityArray()[i]->setPosition(n->getAttachedHex()->getPosition());
				--i;
				std::cout << "X" << n->getXCoord() << " Y" << n->getYCoord() << " Cost:" << n->getCost() << std::endl;
			}
			std::cout << std::endl;
		}
		break;
	default:
		break;
	}
}

Scene* Game::createMainMenu() {
	Scene* tempScene = new Scene(shaders, r);
	Quad2D* tempQuad = new Quad2D("img/startbutton.png", 0.4f, 0.2f, glm::vec3(0.0f, 0.0f, 0.0f));
	tempScene->addEntity(tempQuad);

	return tempScene;
}

Scene* Game::createPhysicsBox() {
	Scene* tempScene = new Scene(shaders, r);
	
	//Room creation
	Mesh3D* tempMesh = new Mesh3D("meshes/room.obj", "img/roomtex.png", glm::vec3(0.0f, 0.0f, 0.0f));
	if (!tempMesh->failedToLoad) {
		tempScene->addEntity(tempMesh);
		//The physical implementation of the bounding room, 6 planes:
		//floor
		physicsController->addPlane(new PhysicsPlane(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
		//ceiling
		physicsController->addPlane(new PhysicsPlane(glm::vec3(0.0f, 8.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		//+z wall (far)
		physicsController->addPlane(new PhysicsPlane(glm::vec3(0.0f, 4.0f, 8.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
		//-z wall (near)
		physicsController->addPlane(new PhysicsPlane(glm::vec3(0.0f, 4.0f, -8.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
		//+x wall (right)
		physicsController->addPlane(new PhysicsPlane(glm::vec3(8.0f, 4.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)));
		//-x wall (left)
		physicsController->addPlane(new PhysicsPlane(glm::vec3(-8.0f, 4.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
	}
	else {
		delete tempMesh;
	}
	//Sphere creation
	glm::vec3 positions[15] = { glm::vec3(-6.0f, 2.0f, 6.0f),
		glm::vec3(-6.0f, 5.0f, 4.0f),
		glm::vec3(-6.0f, 2.0f, 1.0f),
		glm::vec3(-5.0f, 4.0f, -3.0f),
		glm::vec3(-6.0f, 2.0f, -5.0f),
		glm::vec3(0.0f, 3.0f, -5.0f),
		glm::vec3(0.0f, 2.5f, -3.0f),
		glm::vec3(-1.0f, 1.0f, 0.0f),
		glm::vec3(-1.0f, 4.0f, 3.0f),
		glm::vec3(-1.0f, 5.0f, 5.8f),
		glm::vec3(6.0f, 3.0f, -4.0f),
		glm::vec3(5.0f, 2.0f, -4.0f),
		glm::vec3(5.0f, 3.0f, -4.0f),
		glm::vec3(5.0f, 3.0f, -4.0f),
		glm::vec3(5.0f, 3.0f, -4.0f)
	};
	float sizes[15] = {
		1.1f, 0.5f, 1.2f, 1.1f, 1.7f,
		0.8f, 0.9f, 1.1f, 1.5f, 1.0f,
		1.5f, 1.0f, 1.1f, 0.8f, 0.6f
	};
	std::string textures[15] = {
		"img/blue.png", "img/brown.png", "img/green.png", "img/orange2.png", "img/pink.png", "img/purple.png", "img/red.png", "img/yellow.png",
		"img/blue.png", "img/brown.png", "img/green.png", "img/orange2.png", "img/pink.png", "img/purple.png", "img/red.png"
	};
	glm::vec3 velocities[15] = { glm::vec3(1.0f, 3.0f, -4.0f),
		glm::vec3(3.0f, 3.0f, -2.0f),
		glm::vec3(0.0f, 4.0f, -1.0f),
		glm::vec3(5.0f, -4.0f, 4.0f),
		glm::vec3(6.0f, 0.0f, 0.0f),
		glm::vec3(-2.0f, -3.0f, 1.0f),
		glm::vec3(-1.0f, 0.0f, 3.0f),
		glm::vec3(-1.0f, -2.0f, -1.0f),
		glm::vec3(-4.0f, 3.0f, -3.0f),
		glm::vec3(-5.0f, 0.0f, 0.5f),
		glm::vec3(-3.0f, 2.0f, 0.0f),
		glm::vec3(1.0f, -3.0f, 3.0f),
		glm::vec3(0.0f, 7.0f, -4.0f),
		glm::vec3(3.0f, 3.0f, -1.0f),
		glm::vec3(1.0f, -5.0f, 0.0f)
	};

	for (unsigned int i = 0; i < 15; i++) {
		Sphere3D* tempSphere = new Sphere3D(sizes[i], textures[i], positions[i]);
		if (!tempSphere->failedToLoad) {
			PhysicsSphere* physSphere = new PhysicsSphere(tempSphere);
			tempScene->addEntity(physSphere);
			physicsController->addSphere(physSphere);
			physSphere->overrideVelocity(velocities[i]);
		}
		else {
			delete tempSphere;
		}
	}

	return tempScene;
}

Scene* Game::create3DTestScene() {
		Scene* tempScene = new Scene(shaders, r);
		tempScene->addEntity(new Point(glm::vec3(0.0f, 0.0f, 0.0f)));

		Quad2D* tempQuad = new Quad2D("img/esctoexit.png", 0.4f, 0.4f, glm::vec3(0.5f, 0.5f, 0.0f));
		tempScene->addEntity(tempQuad);

		tempQuad = new Quad2D("img/wtomove.png", 0.18f, 0.2f, glm::vec3(0.8f, -0.8f, 0.0f));
		tempScene->addEntity(tempQuad);

		Mesh3D* tempMesh = new Mesh3D("meshes/room.obj", "img/roomtex.png", glm::vec3(0.0f, 0.0f, 0.0f));
		if (!tempMesh->failedToLoad) {
			tempScene->addEntity(tempMesh);
		}
		else {
			delete tempMesh;
		}
		tempMesh = new Mesh3D("meshes/housetex.obj", "img/house.png", glm::vec3(0.0f, 0.0f, -1.0f));
		if (!tempMesh->failedToLoad) {
			tempScene->addEntity(tempMesh);
		}
		else {
			delete tempMesh;
		}
		tempMesh = new Mesh3D("meshes/tower.obj", "img/orange.png", glm::vec3(-2.0f, 1.0f, 2.0f));
		if (!tempMesh->failedToLoad) {
			tempScene->addEntity(tempMesh);
		}
		else {
			delete tempMesh;
		}

		
		soundEngine = irrklang::createIrrKlangDevice();
		soundEngine->setListenerPosition(irrklang::vec3df(7.0f, 3.0f, 7.0f), irrklang::vec3df(7.0f, 3.0f, 7.0f));
		recalculateViewMatrix();
		tempScene->moveCamera(viewMatrix);
		if (!soundEngine)
			printf("Error initialising the Audio Engine!");
		music = soundEngine->play3D("audio/groovy.wav",
			irrklang::vec3df(0, 0, 0), true, false, true);
		if (music)
			music->setMinDistance(5.0f);
		return tempScene;
}

Scene* Game::createHexagonGrid() {
	Scene* tempScene = new Scene(shaders, r);
	AIController = new AIControl();
	std::vector<pathNode*> tempNodes = AIController->getHexagons();
	for each (pathNode* node in tempNodes) {
		if (node->getCost() != -2)
			tempScene->addEntity(node->getAttachedHex());
	}

	for (int i = 0; i < 50; i++) {
		Quad2D* tempQuad = new Quad2D("img/purple.png", 0.03f, 0.03f, glm::vec3(-1.0f, -1.0f, 0.0f));
		tempScene->addEntity(tempQuad);
	}

	Quad2D* tempQuad = new Quad2D("img/redarrow.png", 0.05f, 0.05f, glm::vec3(0.0f, 0.0f, 0.0f));
	tempScene->addEntity(tempQuad);
	
	return tempScene;
}

void Game::switchScene(int sceneID) {
	r->clearCurrentObjects();
	switch (sceneID) {
	case 0:
		r->overwriteObjectArray(scenes[sceneID]->getObjectArray());
		physicsController->overwriteControlledEntities(scenes[sceneID]->getPhysicsEntityArray());
		break;
	case 1:
		if (scenes[sceneID]) {
			r->overwriteObjectArray(scenes[sceneID]->getObjectArray());
			physicsController->overwriteControlledEntities(scenes[sceneID]->getPhysicsEntityArray());
		}
		else {
			scenes[1] = create3DTestScene();
			physicsController->overwriteControlledEntities(scenes[sceneID]->getPhysicsEntityArray());
		}
		break;
	case 2:
		if (scenes[sceneID]) {
			r->overwriteObjectArray(scenes[sceneID]->getObjectArray());
			physicsController->overwriteControlledEntities(scenes[sceneID]->getPhysicsEntityArray());
		}
		else {
			scenes[2] = createPhysicsBox();
			physicsController->overwriteControlledEntities(scenes[sceneID]->getPhysicsEntityArray());
		}
		break;
	case 3:
		if (scenes[sceneID]) {
			r->overwriteObjectArray(scenes[sceneID]->getObjectArray());
			physicsController->overwriteControlledEntities(scenes[sceneID]->getPhysicsEntityArray());
		}
		else {
			scenes[3] = createHexagonGrid();
			physicsController->overwriteControlledEntities(scenes[sceneID]->getPhysicsEntityArray());
		}
		break;
	default:
		break;
	}
	currentSceneID = sceneID;
}

void Game::recalculateViewMatrix() {
	cameraDirection = glm::vec3(glm::cos(cameraPitch) * glm::sin(cameraYaw), glm::sin(cameraPitch), glm::cos(cameraPitch) * glm::cos(cameraYaw));
	glm::vec3 right = glm::vec3(glm::sin(cameraYaw - 1.57f), 0.0f, cos(cameraYaw - 1.57f));
	cameraUp = glm::cross(cameraDirection, right);
	viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraDirection, cameraUp);
}

void Game::recalculateCameraPitchYaw() {
	glm::vec2 cursorPos = r->getWindow()->getCursorPos();
	r->getWindow()->centerCursor();
	cameraPitch -= 0.005f * (300.0f - cursorPos.y);
	if (cameraPitch < 1.8f)
		cameraPitch = 1.8f;
	if (cameraPitch > 4.45f)
		cameraPitch = 4.45f;
	cameraYaw += 0.005f * (400.0f - cursorPos.x);
	if (cameraYaw < -3.141f)
		cameraYaw = 3.141f;
	if (cameraYaw > 3.141f)
		cameraYaw = -3.141f;
}

void Game::recalculateCameraPosition() {
	if (r->getWindow()->isKeyPressed(GLFW_KEY_W)) {
		glm::vec3 moveDirection(glm::sin(cameraYaw) * 0.1f, 0.0f, glm::cos(cameraYaw) * 0.1f);
		cameraPos -= moveDirection;
		if (cameraPos.x < -7)
			cameraPos.x = -7;
		if (cameraPos.x > 7)
			cameraPos.x = 7;
		if (cameraPos.z < -7)
			cameraPos.z = -7;
		if (cameraPos.z > 7)
			cameraPos.z = 7;
	}
}
#include "pathNode.h"
#include <math.h>


pathNode::pathNode(int xCoord, int yCoord, int cost) : xCoord(xCoord), yCoord(yCoord), cost(cost) {
	float radius = 0.085f;
	glm::vec3 colour;
	glm::vec2 position;
	switch (cost) {
	case -1:
		colour = glm::vec3(0.15f, 0.15f, 1.0f);
		passable = false;
		break;
	case 0:
		colour = glm::vec3(0.9f, 0.1f, 0.1f);
		passable = true;
		break;
	case 1:
		colour = glm::vec3(0.5f, 1.0f, 0.5f);
		passable = true;
		break;
	case 2:
		colour = glm::vec3(1.0f, 1.0f, 0.0f);
		passable = true;
		break;
	case 4:
		colour = glm::vec3(0.1f, 0.7f, 0.1f);
		passable = true;
		break;
	default:
		colour = glm::vec3(0.5f, 0.5f, 0.5f);
		passable = false;
		break;
	}

	float offsetX = glm::cos(glm::radians(30.0f)) * radius;
	float offsetY = glm::sin(glm::radians(30.0f)) * radius;
	float tempX;
	if (yCoord > 0) {
		tempX = (xCoord + floor(yCoord / 2)) * offsetX * 2;
		if (yCoord % 2 != 0) {
			tempX += offsetX;
		}
	}
	else {
		tempX = (xCoord + ceil(yCoord / 2)) * offsetX * 2;
		if (yCoord % 2 != 0) {
			tempX -= offsetX;
		}
	}
	
	
	float tempY = yCoord * offsetY * 3;

	position = glm::vec2(tempX, tempY);
	drawableHex = new Hexagon(radius-0.002f, colour, position);
}


pathNode::~pathNode() {

}


int pathNode::calculateHexDistance(pathNode* other) {
	int deltaX = other->getXCoord() - xCoord;
	int deltaY = other->getYCoord() - yCoord;
	
	if (sign(deltaX) == sign(deltaY) || deltaX == 0 || deltaY == 0) {
		if (abs(deltaX) > abs(deltaY)) {
			return abs(deltaX);
		} else {
			return abs(deltaY);
		}
	} else {
		return abs(deltaX) + abs(deltaY);
	}
}

int pathNode::sign(int x) {
	if (x < 0) {
		return -1;
	} else if (x > 0) {
		return 1;
	} else {
		return 0;
	}
}
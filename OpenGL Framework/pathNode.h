#pragma once
#include "Hexagon.h"

class pathNode {
public:
	pathNode(int xCoord, int yCoord, int cost);
	~pathNode();
	void addLinkedNode(pathNode* node) { linkedNodes.push_back(node); }
	vector<pathNode*> getLinkedNodes() { return linkedNodes; }
	Hexagon* getAttachedHex() { return drawableHex; }
	//Assumes hexagonal grid with y axis at a 60 degree angle
	int calculateHexDistance(pathNode* other);
	int getXCoord() { return xCoord; }
	int getYCoord() { return yCoord; }
	void setCost(int cost) { this->cost = cost; }
	int getCost() { return cost; }
	bool isPassable() { return passable; }
	void setPassable(bool isPassable) { passable = isPassable; }
private:
	Hexagon* drawableHex;
	vector<pathNode*> linkedNodes;
	int xCoord;
	int yCoord;
	int cost;
	bool passable;
	int heuristicDistance;
	int sign(int x);
};
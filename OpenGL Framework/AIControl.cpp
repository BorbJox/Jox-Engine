#include "AIControl.h"


AIControl::AIControl() {
	if (loadSampleGrid()) {
		cout << "node loading success!";
	}
}


AIControl::~AIControl() {

}

vector<pathNode*> AIControl::calculatePath(pathNode* target) {
	vector<ParentedNode*> openList;
	vector<ParentedNode*> closedList;
	vector<pathNode*> resultPath;

	//Initialise starting node
	ParentedNode* tempParentedNode = new ParentedNode();
	tempParentedNode->node = currentPosition;
	tempParentedNode->parent = tempParentedNode;
	tempParentedNode->fValue = tempParentedNode->node->calculateHexDistance(target);
	tempParentedNode->gValue = 0;
	//Add it to the open list
	openList.push_back(tempParentedNode);
	
	//Go through open list items until it's empty (dead end) or we find the goal
	while (!openList.empty()) {
		//Find node closest to goal
		//ParentedNode* tempClosestNode = std::min_element(openList.front(), openList.back()));
		ParentedNode* tempClosestNode = openList.front();
		for each (ParentedNode* node in openList) {
			if (*node < *tempClosestNode)
				tempClosestNode = node;
		}
		if (*openList.back() < *tempClosestNode)
			tempClosestNode = openList.back();

		openList.erase(find(openList.begin(), openList.end(), tempClosestNode));
		closedList.push_back(tempClosestNode);
		//If the node is the goal, we found it
		if (target == tempClosestNode->node) {
			ParentedNode* workingNode = tempClosestNode;
			while (workingNode->parent != workingNode) {
				resultPath.push_back(workingNode->node);
				workingNode = workingNode->parent;
			}
			resultPath.push_back(workingNode->node);
			for each (ParentedNode* p in openList)
				delete p;
			for each (ParentedNode* p in closedList)
				delete p;
			return resultPath;
		}
		
		//Go through the nodes connected to the closest node
		for each (pathNode* node in tempClosestNode->node->getLinkedNodes()) {
			if (node->isPassable()) {
				ParentedNode tempNode;
				tempNode.node = node;
				tempNode.parent = tempClosestNode;
				tempNode.gValue = node->getCost() + tempNode.parent->gValue;
				tempNode.fValue = tempNode.gValue + node->calculateHexDistance(target);
				bool notInLists = true;

				//Check if it's in the open list
				for each (ParentedNode* openListNode in openList) {
					if (*openListNode == tempNode) {
						if (tempNode.fValue < openListNode->fValue) {
							openListNode->parent = tempNode.parent;
							openListNode->fValue = tempNode.fValue;
							openListNode->gValue = tempNode.gValue;
						}
						notInLists = false;
						break;
					}
				}

				//Check if it's in the closed list
				for each (ParentedNode* closedListNode in closedList) {
					if (*closedListNode == tempNode) {
						
						notInLists = false;
						break;
					}
				}

				//Add to open list
				if (notInLists) {
					openList.push_back(new ParentedNode(tempNode));
				}
			}
		}
	}

	//Unfortunately must return empty path
	for each (ParentedNode* p in openList)
		delete p;
	for each (ParentedNode* p in closedList)
		delete p;
	resultPath.push_back(currentPosition);
	return resultPath;
}

bool AIControl::loadSampleGrid() {
	std::ifstream nodeFile;
	std::ifstream costsFile;
	std::ifstream connectionsFile;
	nodeFile.open("nodes/nodes.txt");
	costsFile.open("nodes/costs.txt");
	connectionsFile.open("nodes/connections.txt");
	if (!nodeFile.is_open() || !costsFile.is_open() || !connectionsFile.is_open()) {
		printf("Failed to open one of the nodes files!\n");
		return false;
	} else {

		int nodeID;
		int nodeXCoord;
		int nodeYCoord;
		int cost;
		int skipID;
		pathNode* nullNode = new pathNode(0, 0, -2);
		grid.push_back(nullNode);

		while (nodeFile >> nodeID) {
			nodeFile >> nodeXCoord;
			nodeFile >> nodeYCoord;
			costsFile >> skipID;
			costsFile >> cost;
			pathNode* tempNode = new pathNode(nodeXCoord, nodeYCoord, cost);
			if (cost == 0) {
				currentPosition = tempNode;
			}
			grid.push_back(tempNode);
		}

		int linkedNodeID;
		while (connectionsFile >> nodeID) {
			for (int i = 0; i < 6; ++i) {
				connectionsFile >> linkedNodeID;
				if (linkedNodeID != 0) {
					grid[nodeID]->addLinkedNode(grid[linkedNodeID]);
				}
			}
		}
	}
	nodeFile.close();
	costsFile.close();
	connectionsFile.close();
	return true;
}
#pragma once
#include "pathNode.h"
#include <queue>
struct ParentedNode {
	ParentedNode* parent;
	pathNode* node;
	int fValue;
	int gValue;
	bool operator<(const ParentedNode& rhs) const {
		return fValue < rhs.fValue;
	}

	bool operator==(const ParentedNode& rhs) const {
		return node == rhs.node;
	}
};



class AIControl
{
public:
	AIControl();
	~AIControl();
	std::vector<pathNode*> getHexagons() { return grid; }
	std::vector<pathNode*> calculatePath(pathNode* target);
private:
	std::vector<pathNode*> grid;
	pathNode* currentPosition;
	bool loadSampleGrid();
};


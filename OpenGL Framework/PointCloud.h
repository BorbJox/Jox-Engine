#pragma once
#include <vector>
#include "Entity.h"
#include "Point.h"
#include "glm\glm.hpp"

//Holds pointers to Points in a vector. Deletes them all when destroyed.
class PointCloud : public Entity {
public:
	PointCloud();
	PointCloud(std::vector<Point*> points);
	PointCloud(std::vector<Point*> points, glm::vec3 position);
	~PointCloud();
	void addPoint(Point* p) { points.push_back(p); }
	//Returns the vector with all the pointers to Points in it.
	std::vector<Point*> getVector() { return points; }
private:
	std::vector<Point*> points;
};


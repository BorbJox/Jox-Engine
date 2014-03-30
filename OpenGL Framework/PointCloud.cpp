#include "PointCloud.h"


PointCloud::PointCloud() : Entity() {
}

PointCloud::PointCloud(std::vector<Point*> points) : Entity(), points(points) {
}

PointCloud::PointCloud(std::vector<Point*> points, glm::vec3 position) : Entity(position), points(points) {
}

PointCloud::~PointCloud() {
	for each (Point* p in points)
		delete p;
}
#include "Point.h"


Point::Point() : Entity(), colour(glm::vec3(1.0f,1.0f,1.0f)) {

}

Point::Point(glm::vec3 position) : Entity(position), colour(glm::vec3(1.0f, 1.0f, 1.0f)) {

}

Point::Point(glm::vec3 position, glm::vec3 colour) : Entity(position), colour(colour) {

}


Point::~Point() {

}

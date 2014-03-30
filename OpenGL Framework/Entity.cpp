#include "Entity.h"

Entity::Entity() : position(glm::vec3(0.0f,0.0f,0.0f)) {

}

Entity::Entity(glm::vec3 position) : position(position) {

}

Entity::~Entity() {

}

void Entity::setPosition(glm::vec3 pos) {
	position = pos;
	renderObject->modelMatrix = glm::translate(glm::mat4(1.0), position);
}
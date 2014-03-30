#include "Hexagon.h"


Hexagon::Hexagon(float radius, glm::vec3 colour, glm::vec2 position) : colour(colour), Entity(glm::vec3(position,0.0f)) {
	for (int i = 30; i <= 330; i+=60){
		float rad = glm::radians((float)i);
		float tempX = glm::cos(rad);
		float tempY = glm::sin(rad);
		glm::vec3 tempVertex = glm::vec3(tempX, tempY, 0.0f);
		vertices.push_back(tempVertex * radius);
	}
}


Hexagon::~Hexagon() {

}

void Hexagon::changeColour(glm::vec3 col)  {
	colour = col;
}
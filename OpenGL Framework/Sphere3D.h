#pragma once
#include "Entity.h"
#include <vector>

//Derived game representation of a sphere entity. Does not handle physics
class Sphere3D : public Entity {
public:
	Sphere3D(float radius, string texturePath, glm::vec3 pos);
	~Sphere3D();
	std::vector<glm::vec3> getVertexData() { return vertices; }
	std::vector<glm::vec2> getUVData() { return uvs; }
	std::vector<glm::vec3> getNormalData() { return normals; }
	std::string getTexturePath() { return texturePath; }
	bool failedToLoad = false;
	float getRadius() { return radius; }
private:
	float radius;
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::string texturePath;
	bool loadMesh(float r);
};


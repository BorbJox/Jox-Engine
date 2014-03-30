#include "Mesh3D.h"


Mesh3D::Mesh3D() : Entity(glm::vec3(0.0f, 0.0f, 0.0f)), texturePath("img/house.png") {
	loadMesh("meshes/housetex.obj");
}

Mesh3D::Mesh3D(std::string modelPath, std::string texturePath, glm::vec3 pos) : Entity(pos), texturePath(texturePath) {
	if (!loadMesh(modelPath)) {
		failedToLoad = true;
	}
}

Mesh3D::~Mesh3D() {

}


bool Mesh3D::loadMesh(std::string path) {
	
	std::ifstream file;
	file.open(path);
	if (!file.is_open()) {
		printf("Failed to open a 3D mesh file!\n");
		return false;
	} else {
		std::vector<glm::vec3> temp_vertices;
		std::vector<glm::vec2> temp_uvs;
		std::vector<glm::vec3> temp_normals;

		char lineHeader[128];
		while (file >> lineHeader) {
			if (strcmp(lineHeader,"v") == 0) {
				glm::vec3 vertex;
				file >> vertex.x;
				file >> vertex.y;
				file >> vertex.z;
				temp_vertices.push_back(vertex);
			} 
			else if (strcmp(lineHeader,"vt") == 0)	{
				glm::vec2 uv;
				file >> uv.x;
				float tempFloat;
				file >> tempFloat;
				uv.y = 1.0f - tempFloat;
				temp_uvs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) {
				glm::vec3 normal;
				file >> normal.x;
				file >> normal.y;
				file >> normal.z;
				temp_normals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0) {
				unsigned int tempInt;
				file >> tempInt; 
				vertexIndices.push_back(tempInt);
				file.ignore();
				file >> tempInt;
				uvIndices.push_back(tempInt);
				file.ignore();
				file >> tempInt;
				normalIndices.push_back(tempInt);
				file.ignore();
				file >> tempInt;
				vertexIndices.push_back(tempInt);
				file.ignore();
				file >> tempInt;
				uvIndices.push_back(tempInt);
				file.ignore();
				file >> tempInt;
				normalIndices.push_back(tempInt);
				file.ignore();
				file >> tempInt;
				vertexIndices.push_back(tempInt);
				file.ignore();
				file >> tempInt;
				uvIndices.push_back(tempInt);
				file.ignore();
				file >> tempInt;
				normalIndices.push_back(tempInt);
			}
		}

		for each (unsigned int index in vertexIndices) {
			glm::vec3 vertex = temp_vertices[index-1];
			vertices.push_back(vertex);
		}

		for each (unsigned int index in uvIndices) {
			glm::vec2 uv = temp_uvs[index - 1];
			uvs.push_back(uv);
		}
		for each (unsigned int index in normalIndices) {
			glm::vec3 normal = temp_normals[index - 1];
			normals.push_back(normal);
		}
	}
	file.close();
	return true;
	
}
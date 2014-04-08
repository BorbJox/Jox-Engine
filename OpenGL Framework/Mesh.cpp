#include "Mesh.h"


Mesh::Mesh(std::string filename) {

	std::ifstream file;
	//Try to open the file
	file.open(filename);
	if (!file.is_open()) {
		printf("Failed to open a 3D mesh file!\n");
	}
	//If file succesfully opened
	else {
		bool readingHeaders;
		unsigned int vertexCount;
		unsigned int faceCount;
		bool foundPosition = false;
		bool foundNormals = false;
		bool foundUVs = false;
		bool foundColour = false;
		char lineHeader[64];

		//Check if the file structure is of the ply format
		file >> lineHeader;
		if (strcmp(lineHeader, "ply") != 0) {
			std::cout << "Mesh file '" << filename << "' is not suitable for reading!" << std::endl;
		}
		else {

			//Check Headers to see what the file will include
			while (file >> lineHeader) {
				//Count the amount of vertices or triangles
				if (strcmp(lineHeader, "element") == 0) {
					char tempHeader[64];
					file >> tempHeader;
					if (strcmp(tempHeader, "vertex") == 0) {
						file >> vertexCount;
					}
					else if (strcmp(tempHeader, "face") == 0) {
						file >> faceCount;
					}
				}
				//Check which properties the file provides
				else if (strcmp(lineHeader, "property") == 0) {
					char tempHeader[64];
					file >> tempHeader;
					//Float properties
					if (strcmp(tempHeader, "float") == 0) {
						file >> tempHeader;
						//Vertex Position
						if (strcmp(tempHeader, "x") == 0 || strcmp(tempHeader, "y") == 0 || strcmp(tempHeader, "z") == 0) {
							foundPosition = true;
						}
						//Normal Direction
						else if (strcmp(tempHeader, "nx") == 0 || strcmp(tempHeader, "ny") == 0 || strcmp(tempHeader, "nz") == 0) {
							foundNormals = true;
						}
						//Texture coordinates
						else if (strcmp(tempHeader, "s") == 0 || strcmp(tempHeader, "t") == 0) {
							foundUVs = true;
						}
					}
					//Char properties
					else if (strcmp(tempHeader, "uchar") == 0) {
						file >> tempHeader;
						//Vertex Colour
						if (strcmp(tempHeader, "red") == 0 || strcmp(tempHeader, "green") == 0 || strcmp(tempHeader, "blue") == 0) {
							foundColour = true;
						}
					}
				}
				//Found the end of the header
				else if (strcmp(lineHeader, "end_header") == 0) {
					break;
				}
			}

			//Read the vertex values
			for (unsigned int i = 0; i < vertexCount; ++i) {
				if (foundPosition) {
					glm::vec3 tempVertex;
					file >> tempVertex.x;
					file >> tempVertex.y;
					file >> tempVertex.z;
					vertices.push_back(tempVertex);
				}
				if (foundNormals) {
					glm::vec3 tempNormal;
					file >> tempNormal.x;
					file >> tempNormal.y;
					file >> tempNormal.z;
					normals.push_back(tempNormal);
				}
				if (foundUVs) {
					glm::vec2 tempUV;
					file >> tempUV.s;
					file >> tempUV.t;
					uvs.push_back(tempUV);
				}
				if (foundColour) {
					glm::vec3 tempColour;
					unsigned int tempValue;
					file >> tempValue;
					tempColour.r = (float)tempValue / 255.0f;
					file >> tempValue;
					tempColour.g = (float)tempValue / 255.0f;
					file >> tempValue;
					tempColour.b = (float)tempValue / 255.0f;
					colours.push_back(tempColour);
				}
			}

			//Read the element values
			for (unsigned int i = 0; i < faceCount; ++i) {
				triangleVertexIndices tempTriangle;
				file.ignore();
				file >> tempTriangle.first;
				file >> tempTriangle.second;
				file >> tempTriangle.third;
				elements.push_back(tempTriangle);
			}
		}
	}
	file.close();
}


Mesh::~Mesh() {

}

#include "Mesh.h"


Mesh::Mesh(std::string filename) {

	std::ifstream file;
	//Try to open the file
	file.open(filename);
	if (!file.is_open()) {
		std::cout << "Failed to open " << filename << "!" << std::endl;
	}
		//If file succesfully opened
	else {
		bool readingHeaders;
		unsigned int vertexCount;
		bool foundPosition = false;
		bool foundNormals = false;
		bool foundUVs = false;
		bool foundColour = false;
		char lineHeader[64];

		//Check if the file structure is of the ply format
		file >> lineHeader;
		if (strcmp(lineHeader, "ply") != 0) {
			std::cout << "Mesh file " << filename << " is not suitable for reading!" << std::endl;
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
						file >> triangleCount;
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

			if (!foundPosition) {
				std::cout << "Could not find vertex position data in the .ply file!" << std::endl;
			}
			if (!foundNormals) {
				std::cout << "Could not find vertex normals data in the .ply file!" << std::endl;
			}
			if (!foundUVs) {
				std::cout << "Could not find vertex UV data in the .ply file!" << std::endl;
			}
			if (!foundColour) {
				std::cout << "Could not find vertex colour data in the .ply file!" << std::endl;
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
			for (unsigned int i = 0; i < triangleCount; ++i) {
				file.ignore();
				for (unsigned int j = 0; j < 3; ++j) {
					int tempIndex;
					file >> tempIndex;
					indices.push_back(tempIndex);
				}
			}
		}
		
		//If all data needed exists, buffer it to the GPU.
		if (foundPosition && foundNormals && foundUVs && foundColour) {
			BufferData();
			incompleteData = false;
		}
		else {
			std::cout << "Cannot buffer " << filename << " due to incomplete data!" << std::endl;
			incompleteData = true;
		}
	}
	file.close();
}


Mesh::~Mesh() {
	if (!incompleteData) {
		glDeleteBuffers(1, &positionBuffer);
		glDeleteBuffers(1, &colourBuffer);
		glDeleteBuffers(1, &uvBuffer);
		glDeleteBuffers(1, &normalBuffer);
		glDeleteBuffers(1, &indicesBuffer);

		glDeleteVertexArrays(1, &vao);
	}
}

void Mesh::BufferData() {
	glBindVertexArray(vao);

	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);

	glGenBuffers(1, &colourBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
	glBufferData(GL_ARRAY_BUFFER, colours.size()*sizeof(glm::vec3), &colours.front(), GL_STATIC_DRAW);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size()*sizeof(glm::vec2), &uvs.front(), GL_STATIC_DRAW);

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(glm::vec3), &normals.front(), GL_STATIC_DRAW);

	glGenBuffers(1, &indicesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);
	
	//Unbind the buffers to prevent external tampering
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
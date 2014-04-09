#pragma once
#include "glew\glew.h"
#include "glfw\glfw3.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "soil\SOIL.h"
#include <vector>
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

/*
Holds information on how to draw an object, and does the draw calls when requested.
*/
class RenderObject {
public:
	RenderObject(Shader* s, Mesh* mesh, Texture* texture);
	~RenderObject();
	void Draw(glm::mat4 view, glm::mat4 projection, glm::vec3 lightPosition = glm::vec3());
	void setModelMatrix(glm::mat4 modelMatrix) { modelTransform = modelMatrix; }
	glm::mat4 getModelMatrix() { return modelTransform; }
private:
	Shader* shader;
	Mesh* mesh;
	Texture* texture;
	glm::mat4 modelTransform;
	GLuint type;
	GLuint mvpUniform;
	GLuint modelTransformUniform;
	GLuint lightPositionUniform;
	GLuint textureSamplerUniform;
	GLuint colourAmountUniform;
	void BufferData();
};
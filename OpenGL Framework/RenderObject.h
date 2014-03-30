#pragma once
#include "glew\glew.h"
#include "glfw\glfw3.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "soil\SOIL.h"
#include <vector>
#include "Shader.h"

//Renderable object handled with OpenGL
class RenderObject
{
public:
	/* Should hold some shaders and vertex data and textures and stuff and
		draw it when the renderer asks.
	*/
	RenderObject(Shader* s);
	RenderObject(GLuint type, std::vector<glm::vec3> vertices, Shader* shader, glm::vec3 position);
	RenderObject(GLuint type, std::vector<glm::vec3> vertices, glm::vec3 colour, Shader* shader, glm::vec3 position);
	RenderObject(GLuint type, std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals, Shader* shader, glm::vec3 position);
	RenderObject(GLuint type, std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, Shader* shader, glm::vec3 position);
	~RenderObject();
	void Draw(glm::mat4 view, glm::mat4 projection);
	void assignTexture(std::string texturePath);
	GLuint type;
	glm::mat4 modelMatrix;
private:
	Shader* shader;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> colours;
	std::vector<unsigned int> elements;
	GLuint texture;
	GLuint vao;
	GLuint vertexBuffer;
	GLuint elementBuffer;
	GLuint colourBuffer;
	GLuint uvBuffer;
	GLuint normalBuffer;
	void BufferData();
	GLuint mvpUniform;
	GLuint vUniform;
	GLuint mUniform;
	GLuint lightPosWorldUniform;
	GLuint lightColourUniform;
	GLuint lightPowerUniform;
	glm::vec3 lightPosition = glm::vec3(2.0f,6.0f,2.0f);
	glm::vec3 lightColour = glm::vec3(1.0f,0.9f,1.0f);
	float lightPower = 50.0f;
	bool hasColour = false;
	bool hasElements = false;
};
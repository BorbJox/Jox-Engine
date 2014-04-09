#include "RenderObject.h"


RenderObject::RenderObject(Shader* shader, Mesh* mesh, Texture* texture) : shader(shader), mesh(mesh), texture(texture) {

}

RenderObject::~RenderObject() {

}

void RenderObject::BufferData() {
	
	type = GL_TRIANGLES;

	//Bind the VAO to work with
	glBindVertexArray(mesh->getVAOID());

	//Vector position attribute
	glBindBuffer(GL_ARRAY_BUFFER, mesh->getPositionBufferID());
	GLint posAttrib = glGetAttribLocation(shader->getShaderProgram(), "position");
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);

	//Vector colour attribute
	glBindBuffer(GL_ARRAY_BUFFER, mesh->getColourBufferID());
	GLint colAttrib = glGetAttribLocation(shader->getShaderProgram(), "colour");
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

	//Vector UV attribute
	glBindBuffer(GL_ARRAY_BUFFER, mesh->getUVBufferID());
	GLint uvAttrib = glGetAttribLocation(shader->getShaderProgram(), "UV");
	glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(uvAttrib);

	//Vector normal attribute
	glBindBuffer(GL_ARRAY_BUFFER, mesh->getNormalBufferID());
	GLint normalAttrib = glGetAttribLocation(shader->getShaderProgram(), "normal");
	glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(normalAttrib);

	//Uniform attribute names
	mvpUniform = glGetUniformLocation(shader->getShaderProgram(), "MVP");
	textureSamplerUniform = glGetUniformLocation(shader->getShaderProgram(), "textureSampler");
	colourAmountUniform = glGetUniformLocation(shader->getShaderProgram(), "colourAmount");
	if (shader->handlesLighting()) {
		modelTransformUniform = glGetUniformLocation(shader->getShaderProgram(), "modelTransform");
		lightPositionUniform = glGetUniformLocation(shader->getShaderProgram(), "lightPosition");
	}

}

void RenderObject::Draw(glm::mat4 view, glm::mat4 projection, glm::vec3 lightPosition) {
	glUseProgram(shader->getShaderProgram());
	glBindVertexArray(mesh->getVAOID());

	glm::mat4 mvp = projection * view * modelTransform;

	glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &mvp[0][0]);
	if (shader->handlesLighting()) {
		glUniformMatrix4fv(modelTransformUniform, 1, GL_FALSE, &modelTransform[0][0]);
		glUniform3f(lightPositionUniform, lightPosition.x, lightPosition.y, lightPosition.z);
	}
	
	texture->bindTexture();

	glDrawElements(type, mesh->getTriangleCount(), GL_UNSIGNED_INT, nullptr);
	
	glBindVertexArray(0);
}
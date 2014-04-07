#include "RenderObject.h"


RenderObject::RenderObject(Shader* s) : shader(s) {
	glGenVertexArrays(1, &vao);
	type = GL_TRIANGLE_FAN;
	for (int i = 0; i < 10; i++)
		vertices.push_back(glm::vec3(i * 0.19f, (i * i * 0.1f) / 5, 1.0f));
	BufferData();
}

RenderObject::RenderObject(GLuint type, std::vector<glm::vec3> vertices, Shader* shader, glm::vec3 position) : shader(shader), type(type), vertices(vertices) {
	modelMatrix = glm::translate(glm::mat4(1.0), position);
	glGenVertexArrays(1, &vao);
	BufferData();
}

RenderObject::RenderObject(GLuint type, std::vector<glm::vec3> vertices, glm::vec3 colour, Shader* shader, glm::vec3 position) : shader(shader), type(type), vertices(vertices) {
	for (int i = 0; i < vertices.size(); ++i) 
		colours.push_back(colour);
	hasColour = true;
	modelMatrix = glm::translate(glm::mat4(1.0), position);
	glGenVertexArrays(1, &vao);
	BufferData();
}

RenderObject::RenderObject(GLuint type, std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals, Shader* shader, glm::vec3 position) : shader(shader), type(type), vertices(vertices), uvs(uvs), normals(normals) {
	modelMatrix = glm::translate(glm::mat4(1.0), position);
	glGenVertexArrays(1, &vao);
	BufferData();
}

RenderObject::RenderObject(GLuint type, std::vector<glm::vec3> vertices, std::vector<glm::vec2> uvs, Shader* shader, glm::vec3 position) : shader(shader), type(type), vertices(vertices), uvs(uvs) {
	modelMatrix = glm::translate(glm::mat4(1.0), position);
	glGenVertexArrays(1, &vao);
	BufferData();
}

RenderObject::~RenderObject() {
	if (hasElements)
		glDeleteBuffers(1, &elementBuffer);
	if (hasColour)
		glDeleteBuffers(1, &colourBuffer);
	glDeleteBuffers(1, &uvBuffer);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &vao);
	
}

void RenderObject::BufferData() {
	glBindVertexArray(vao);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
	GLint posAttrib = glGetAttribLocation(shader->getShaderProgram(), "position");
	if (shader->handles3D()) {
		mvpUniform = glGetUniformLocation(shader->getShaderProgram(), "MVP");
	} else {
		mUniform = glGetUniformLocation(shader->getShaderProgram(), "M");
	}
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);

	if (hasColour) {
		glGenBuffers(1, &colourBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
		glBufferData(GL_ARRAY_BUFFER, colours.size()*sizeof(glm::vec3), &colours.front(), GL_STATIC_DRAW);
		GLint colAttrib = glGetAttribLocation(shader->getShaderProgram(), "color");
		glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(colAttrib);
	}
	
	if (shader->handlesTextures()) {
		glGenBuffers(1, &uvBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glBufferData(GL_ARRAY_BUFFER, uvs.size()*sizeof(glm::vec2), &uvs.front(), GL_STATIC_DRAW);
		GLint uvAttrib = glGetAttribLocation(shader->getShaderProgram(), "vertexUV");
		glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(uvAttrib);
	}
	
	if (shader->handlesNormals()) {
		glGenBuffers(1, &normalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(glm::vec3), &normals.front(), GL_STATIC_DRAW);
		GLint normalAttrib = glGetAttribLocation(shader->getShaderProgram(), "normal");
		vUniform = glGetUniformLocation(shader->getShaderProgram(), "V");
		if (shader->handles3D())
			mUniform = glGetUniformLocation(shader->getShaderProgram(), "M");
		lightPosWorldUniform = glGetUniformLocation(shader->getShaderProgram(), "lightPosWorld");
		lightColourUniform = glGetUniformLocation(shader->getShaderProgram(), "lightColour");
		lightPowerUniform = glGetUniformLocation(shader->getShaderProgram(), "lightPower");
		glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(normalAttrib);
	}

	if (hasElements) {
		glGenBuffers(1, &elementBuffer);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size()*sizeof(unsigned int), &elements.front(), GL_STATIC_DRAW);
	}

	glBindVertexArray(0);
}

void RenderObject::assignTexture(std::string texturePath) {
	if (shader->handlesTextures()) {
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		int width, height;
		unsigned char* image = SOIL_load_image(texturePath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);

		SOIL_free_image_data(image);
	}
	else {
		printf("Error: The shader for this RenderObject doesn't handle textures!\n");
	}
}

void RenderObject::Draw(glm::mat4 view, glm::mat4 projection) {
	glUseProgram(shader->getShaderProgram());
	if (shader->handles3D()) {
		glm::mat4 mvp = projection * view * modelMatrix;
		glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &mvp[0][0]);
	} else {
		glUniformMatrix4fv(mUniform, 1, GL_FALSE, &modelMatrix[0][0]);
	}
	if (shader->handlesNormals()) {
		glUniformMatrix4fv(vUniform, 1, GL_FALSE, &view[0][0]);
		if (shader->handles3D())
			glUniformMatrix4fv(mUniform, 1, GL_FALSE, &modelMatrix[0][0]);
		glUniform3f(lightPosWorldUniform, lightPosition.x, lightPosition.y, lightPosition.z);
		glUniform3f(lightColourUniform, lightColour.r, lightColour.g, lightColour.b);
		glUniform1f(lightPowerUniform, lightPower);
		
	}
	if (shader->handlesTextures()) {
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	glBindVertexArray(vao);

	if (hasElements) {
		//glDrawElements(...);
		printf("Error: Trying to draw using elements!?\n");
	} else {
		glDrawArrays(type, 0, vertices.size());
	}
	glBindVertexArray(0);
}
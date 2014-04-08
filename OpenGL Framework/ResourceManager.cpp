#include "ResourceManager.h"


ResourceManager::ResourceManager() {

}


ResourceManager::~ResourceManager() {
	for each (std::pair<std::string,Shader*> pair in shaders) {
		delete pair.second;
	}
}

Shader* ResourceManager::getShader(shaderParameters parameters) {
	std::string vertexShaderName;
	std::string fragmentShaderName;
	//Checks what kind of parameters need to be fulfilled and selects appropriate shaders for it
	if (parameters.handlesLighting) {
		vertexShaderName = "lit_tex_col_vertex.glsl";
		fragmentShaderName = "lit_tex_col_fragment.glsl";
	}
	else {
		vertexShaderName = "tex_col_vertex.glsl";
		fragmentShaderName = "tex_col_fragment.glsl";
	}

	//Checks if the shader has already been loaded
	std::map<std::string, Shader*>::iterator foundShader = shaders.find(vertexShaderName);
	if (foundShader == shaders.end()) {
		Shader* tempShader = new Shader(parameters, vertexShaderName, fragmentShaderName);
		shaders.insert(std::pair<std::string, Shader*>(vertexShaderName, tempShader));
		return tempShader;
	}
	else {
		Shader* tempShader = foundShader->second;
		return tempShader;
	}
}

Texture* ResourceManager::getTexture(std::string filename) {
	//Looks for existing loaded texture, and creates a new one if it does not exist.
	std::map<std::string, Texture*>::iterator foundTexture = textures.find(filename);
	if (foundTexture == textures.end()) {
		Texture* tempTexture = new Texture(filename);
		textures.insert(std::pair<std::string, Texture*>(filename, tempTexture));
		return tempTexture;
	}
	else {
		Texture* tempTexture = foundTexture->second;
		return tempTexture;
	}
}

Mesh* ResourceManager::getMesh(std::string name) {

}
#pragma once
#include <map>
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"

/*
Will load up new resources into memory when requested, or give pointers to already-loaded resources for use.
*/
class ResourceManager {
public:
	ResourceManager();
	~ResourceManager();
	//Primary function holding information about existing shaders. Check Shader class for more information.
	Shader* getShader(shaderParameters parameters);
	Texture* getTexture(std::string name);
	Mesh* getMesh(std::string name);
private:
	std::map<std::string, Shader*> shaders;
	std::map<std::string, Texture*> textures;
	std::map<std::string, Mesh*> meshes;
};


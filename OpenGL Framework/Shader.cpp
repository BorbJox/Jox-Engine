#include "Shader.h"


Shader::Shader(shaderParameters parameters, std::string vertexFile, std::string fragmentFile) : params(parameters) {

	program = glCreateProgram();

	vertexShader = GenerateShader(vertexFile, GL_VERTEX_SHADER);
	glAttachShader(program, vertexShader);
	fragmentShader = GenerateShader(fragmentFile, GL_FRAGMENT_SHADER);
	glAttachShader(program, fragmentShader);
	
	loadFailed = !LinkProgram();
}


Shader::~Shader() {
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(program);
}

bool Shader::LoadShaderFile(std::string from, std::string &into)	{
	std::ifstream file;
	std::string temp;

	std::cout << "Loading shader text from " << from << std::endl;

	file.open(from.c_str());
	if (!file.is_open()){
		std::cout << "File does not exist!" << std::endl;
		return false;
	}

	while (!file.eof()){
		getline(file, temp);
		into += temp + "\n";
	}


	file.close();
	std::cout << "Loaded shader text!" << std::endl;
	return true;
}

GLuint Shader::GenerateShader(std::string from, GLenum type)	{
	std::cout << "Compiling Shader..." << std::endl;

	std::string load;
	if (!LoadShaderFile(from, load)) {
		std::cout << "Compiling failed!" << std::endl;
		loadFailed = true;
		return 0;
	}

	GLuint shader = glCreateShader(type);

	const char *chars = load.c_str();
	glShaderSource(shader, 1, &chars, NULL);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)	{
		std::cout << "Compiling failed!" << std::endl;
		char error[512];
		glGetInfoLogARB(shader, sizeof(error), NULL, error);
		std::cout << error;
		loadFailed = true;
		return 0;
	}
	std::cout << "Compiling success!" << std::endl << std::endl;
	loadFailed = false;
	return shader;
}

bool Shader::LinkProgram()	{
	if (loadFailed) {
		return false;
	}
	glLinkProgram(program);
	glUseProgram(program);
	GLint code;
	glGetProgramiv(program, GL_LINK_STATUS, &code);

	if (code != GL_TRUE)	{
		char error[2048];

		glGetProgramInfoLog(program, 2048, NULL, error);

		std::cout << std::string(error) << std::endl;
	}

	return code == GL_TRUE ? true : false;
}
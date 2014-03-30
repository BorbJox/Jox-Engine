#include "Shader.h"


Shader::Shader(bool handles3D, bool handlesTextures, bool handlesNormals, string vertexFile, string fragmentFile, string geometryFile, string tessControlShaderFile, string tesselationFile) : enabled3D(handles3D), enabledTextures(handlesTextures), enabledNormals(handlesNormals) {

	program = glCreateProgram();

	vertexShader = GenerateShader(vertexFile, GL_VERTEX_SHADER);
	glAttachShader(program, vertexShader);
	fragmentShader = GenerateShader(fragmentFile, GL_FRAGMENT_SHADER);
	glAttachShader(program, fragmentShader);
	if (!geometryFile.empty()) {
		geometryShader = GenerateShader(geometryFile, GL_GEOMETRY_SHADER);
		glAttachShader(program, geometryShader);
	}
	if (!tessControlShaderFile.empty()) {
		tcsShader = GenerateShader(tessControlShaderFile, GL_TESS_CONTROL_SHADER);
		glAttachShader(program, tcsShader);
	}
	if (!tesselationFile.empty()) {
		tesselationShader = GenerateShader(tesselationFile, GL_TESS_EVALUATION_SHADER);
		glAttachShader(program, tesselationShader);
	}
	
	loadFailed = !LinkProgram();
	
}


Shader::~Shader() {
	
}

void Shader::deleteProgram() {
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (geometryShader != 0)
		glDeleteShader(geometryShader);
	if (tcsShader != 0)
		glDeleteShader(tcsShader);
	if (tesselationShader != 0)
		glDeleteShader(tesselationShader);
	glDeleteProgram(program);
}

bool Shader::LoadShaderFile(string from, string &into)	{
	ifstream file;
	string temp;

	cout << "Loading shader text from " << from << endl;

	file.open(from.c_str());
	if (!file.is_open()){
		cout << "File does not exist!" << endl;
		return false;
	}

	while (!file.eof()){
		getline(file, temp);
		into += temp + "\n";
	}


	file.close();
	cout << "Loaded shader text!" << endl;
	return true;
}

GLuint Shader::GenerateShader(string from, GLenum type)	{
	cout << "Compiling Shader..." << endl;

	string load;
	if (!LoadShaderFile(from, load)) {
		cout << "Compiling failed!" << endl;
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
		cout << "Compiling failed!" << endl;
		char error[512];
		glGetInfoLogARB(shader, sizeof(error), NULL, error);
		cout << error;
		loadFailed = true;
		return 0;
	}
	cout << "Compiling success!" << endl << endl;
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

		cout << string(error) << endl;
	}

	return code == GL_TRUE ? true : false;
}
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include "renderer.h"
#include "shaderHandler.h"

GLuint loadShader(const char* shaderFilePath, GLenum type) {

	GLCall(GLuint shader = glCreateShader(type));
	std::ifstream shaderStream(shaderFilePath, std::ios::in);
	std::string shaderCode;

	if(shaderStream.is_open()) {
		std::stringstream sstr;
		sstr << shaderStream.rdbuf();
		shaderCode = sstr.str();
		shaderStream.close();
	} else {
		printf("Impossible to open %s. Are you in the right directory?", shaderFilePath);
		getchar();
		return 0;
	}

	GLint result = GL_FALSE;
	int InfoLogLength;

	char const* sourcePointer = shaderCode.c_str();
	GLCall(glShaderSource(shader, 1, &sourcePointer, NULL));
	GLCall(glCompileShader(shader));

	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
	GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &InfoLogLength));

	if (InfoLogLength > 0) {
		std::vector<char> shaderErrorMessage(InfoLogLength+1);
		GLCall(glGetShaderInfoLog(shader, InfoLogLength, NULL, &shaderErrorMessage[0]));
		printf("%s\n", &shaderErrorMessage[0]);
	}

	return shader;
}

GLuint createProgram(GLuint vertexShader, GLuint fragmentShader) {

	GLint result = GL_FALSE;
	int InfoLogLength;

	GLuint program = glCreateProgram();
	GLCall(glAttachShader(program, vertexShader));
	GLCall(glAttachShader(program, fragmentShader));
	GLCall(glLinkProgram(program));

	GLCall(glGetProgramiv(program, GL_LINK_STATUS, &result));
	GLCall(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength));
	if ( InfoLogLength > 0) {
		std::vector<char> programErrorMessage(InfoLogLength+1);
		GLCall(glGetShaderInfoLog(program, InfoLogLength, NULL, &programErrorMessage[0]));
		printf("%s\n", &programErrorMessage[0]);
	}

	GLCall(glDetachShader(program, vertexShader));
	GLCall(glDetachShader(program, fragmentShader));

	GLCall(glDeleteShader(vertexShader));
	GLCall(glDeleteShader(fragmentShader));


	return program;

}
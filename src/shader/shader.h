#pragma once
#include "../common/renderer.h"
#include <sstream>
#include <fstream>
#include <iostream>

class Shader {

public:

	Shader(std::string vertexShaderSource, std::string fragmentShaderSource) {

		//Creating program
		GLCall(program = glCreateProgram());

		//Creating shaders
		GLCall(GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER));
		GLCall(GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));

		//Reading VertexShader file and storing it in a stringstream
		const char *vertexShaderChar = loadFile(vertexShaderSource);


		//Attaching the source and compiling the shader
		GLCall(glShaderSource(vertexShader, 1, &vertexShaderChar, NULL));
		GLCall(glCompileShader(vertexShader));

		int success;
		char infoLog[512];

		//Compile error checking
		GLCall(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success));
		if (!success) {
			GLCall(glGetShaderInfoLog(vertexShader, 512, NULL, infoLog));
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		//Reading FragmentShader file and storing it in a stringstream
		const char *fragmentShaderChar = loadFile(fragmentShaderSource);

		//Attaching the source and compiling the shader
		GLCall(glShaderSource(fragmentShader, 1, &fragmentShaderChar, NULL));
		GLCall(glCompileShader(fragmentShader));

		//Compile error checking
		GLCall(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success));
		if (!success) {
			GLCall(glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog));
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		//Attaching and linking program
		GLCall(glAttachShader(program, vertexShader));
		GLCall(glAttachShader(program, fragmentShader));
		GLCall(glLinkProgram(program));

		//Linking error checking
		GLCall(glGetProgramiv(program, GL_LINK_STATUS, &success));
		if(!success) {
			GLCall(glGetProgramInfoLog(program, 512, NULL, infoLog));
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		GLCall(glDeleteShader(vertexShader));
		GLCall(glDeleteShader(fragmentShader));

	}

	~Shader() {
		GLCall(glDeleteProgram(program));
	}

	void use() {
		GLCall(glUseProgram(program));
	}

	GLuint getUniform(std::string name) {
		GLCall(GLuint uniform = glGetUniformLocation(program, name.c_str()));
		return uniform; 
	}

	void setUniform(GLuint ID, float value) {
		GLCall(glUniform1f(ID, value))
	}

	void setUniform(std::string name, float value) {
		GLCall(setUniform(getUniform(name), value));
	}


	void setUniform(GLuint ID, int value) {
		GLCall(glUniform1i(ID, value))
	}

	void setUniform(std::string name, int value) {
		GLCall(setUniform(getUniform(name), value));
	}


	void setUniform(GLuint ID, bool value) {
		GLCall(glUniform1i(ID, (int) value))
	}

	void setUniform(std::string name, bool value) {
		GLCall(setUniform(getUniform(name), value));
	}

	
	void setUniform(GLuint ID, glm::mat4 value) {
		GLCall(glUniformMatrix4fv(ID, 1, GL_FALSE, glm::value_ptr(value)))
	}

	void setUniform(std::string name, glm::mat4 value) {
		GLCall(setUniform(getUniform(name), value));
	}

private:

	GLuint program;

	const char* loadFile(std::string fileSource) {
		//Loading file
		std::ifstream file(fileSource);

		const char *charFile;

		//If loading was successfull, we read the file and put it into a stringstream which in turn is converted to the target type
		if (file) {
			std::stringstream ss;
			ss << file.rdbuf();
			file.close();
			charFile = ss.str().c_str();
		} else {
			std::cout << "Failed to load file: " << fileSource << "!" << std::endl;
		}

		return charFile;
	}

};
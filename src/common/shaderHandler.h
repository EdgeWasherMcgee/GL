#pragma once

#include <GL/glew.h>

GLuint loadShader(const char* shaderFilePath, GLenum type);

GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);
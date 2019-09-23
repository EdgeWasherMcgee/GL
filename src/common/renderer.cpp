#include "renderer.h"
#include <iostream>

void GLClearErrors() {
    while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {

    while(GLenum error = glGetError()) {
        std::cout << "[OpenGL error] (0x" << std::hex << error << ")" << " in file " << file << " in function " << function << " on line " << line << std::endl;
        return false;
    }
    return true;
}

void printMatrix(const glm::mat4 matrix) {

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			printf("%f, ", matrix[y][x]);
		}
		printf("\n");
	}
	printf("\n");
}

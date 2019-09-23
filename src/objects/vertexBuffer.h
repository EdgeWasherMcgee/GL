#pragma once
#include "../common/renderer.h"

class VertexBuffer {

public:

	VertexBuffer();

	void allocateData(GLsizeiptr size);

	void subData(GLuint offset, GLsizeiptr size, void *data);

	void bufferData(GLsizeiptr size, void *data);

	void deleteBuffer();

	void use();

	void disuse();

private:

	GLuint ID;
	GLuint bufferSize;

};
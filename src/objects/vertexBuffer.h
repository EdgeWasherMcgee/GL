#pragma once
#include "../common/renderer.h"

class VertexBuffer {

public:

	VertexBuffer();
	~VertexBuffer();

	void allocateData(GLsizeiptr size);

	void subData(GLuint offset, GLsizeiptr size, void *data);

	void bufferData(GLsizeiptr size, void *data);

	void use();

	void disuse();

private:

	GLuint ID;
	GLuint bufferSize;

};
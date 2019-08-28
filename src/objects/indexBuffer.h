#pragma once
#include "../common/renderer.h"

class IndexBuffer {

public:

	IndexBuffer();
	~IndexBuffer();

	void allocateData(GLsizeiptr size);

	void subData(GLuint offset, GLsizeiptr size, GLushort data[]);

	void bufferData(GLsizeiptr size, GLushort data[]);

	void use();

private:


	GLuint ID;
	GLsizeiptr bufferSize;

};
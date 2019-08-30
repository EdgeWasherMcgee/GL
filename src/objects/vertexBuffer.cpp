#include "vertexBuffer.h"

VertexBuffer::VertexBuffer() {

	GLCall(glGenBuffers(1, &ID));

}

VertexBuffer::~VertexBuffer() {

	GLCall(glDeleteBuffers(1, &ID));

}

void VertexBuffer::bufferData(GLsizeiptr size, void *data) {

	bufferSize = size + 0;

	this->use();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

}

void VertexBuffer::allocateData(GLsizeiptr size) {

	bufferSize = size + 0;

	this->use();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW));

}

void VertexBuffer::subData(GLuint offset, GLsizeiptr size, void *data) {

	this->use();
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));

}

void VertexBuffer::use() {

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, ID));

}
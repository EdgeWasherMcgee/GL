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
	GLCall(glBufferData(GL_VERTEX_ARRAY, size, data, GL_STATIC_DRAW));

}

void VertexBuffer::allocateData(GLsizeiptr size) {

	bufferSize = size + 0;

	this->use();
	GLCall(glBufferData(GL_VERTEX_ARRAY, size, NULL, GL_STATIC_DRAW));

}

void VertexBuffer::subData(GLuint offset, GLsizeiptr size, void *data) {

	this->use();
	GLCall(glBufferSubData(GL_VERTEX_ARRAY, offset, size, data));

}

void VertexBuffer::use() {

	GLCall(glBindBuffer(GL_VERTEX_ARRAY, ID));

}
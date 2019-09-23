#include "vertexBuffer.h"

VertexBuffer::VertexBuffer() {

	GLCall(glGenBuffers(1, &ID));

}

void VertexBuffer::bufferData(GLsizeiptr size, void *data) {

	bufferSize = size;

	use();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

}

void VertexBuffer::allocateData(GLsizeiptr size) {

	bufferSize = size + 0;

	use();
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW));

}

void VertexBuffer::subData(GLuint offset, GLsizeiptr size, void *data) {

	use();
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
	
}

void VertexBuffer::deleteBuffer() {

	GLCall(glDeleteBuffers(1, &ID));

}

void VertexBuffer::use() {

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, ID));

}

void VertexBuffer::disuse() {

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

}
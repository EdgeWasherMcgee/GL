#include "indexBuffer.h"

IndexBuffer::IndexBuffer() {

	GLCall(glGenBuffers(1, &ID));

}

IndexBuffer::~IndexBuffer() {

	GLCall(glDeleteBuffers(1, &ID));
}

void IndexBuffer::bufferData(GLsizeiptr size, GLushort data[]) {

	bufferSize = size;

	this->use();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, (void *) data, GL_STATIC_READ));

}

void IndexBuffer::allocateData(GLsizeiptr size) {

	bufferSize = size + 0;

	this->use();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, NULL, GL_STATIC_READ));

}

void IndexBuffer::subData(GLuint offset, GLsizeiptr size, GLushort data[]) {

	this->use();
	GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, (void *) data));

}

void IndexBuffer::use() {

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));

}

// IndexBuffer::

#include "indexBuffer.h"

IndexBuffer::IndexBuffer() {

	GLCall(glGenBuffers(1, &ID));

}

void IndexBuffer::bufferData(GLsizeiptr size, GLushort data[]) {

	bufferSize = size;

	use();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, (void *) data, GL_STATIC_DRAW));

}

void IndexBuffer::allocateData(GLsizeiptr size) {

	bufferSize = size + 0;

	use();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW));

}

void IndexBuffer::subData(GLuint offset, GLsizeiptr size, GLushort data[]) {

	use();
	GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, (void *) data));

}

void IndexBuffer::deleteBuffer() {

	GLCall(glDeleteBuffers(1, &ID));

}

inline void IndexBuffer::use() const {

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));

}

inline void IndexBuffer::disuse() const{

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

}

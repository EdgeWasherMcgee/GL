#include "vao.h"

VAO::VAO(IndexBuffer ibo, VertexBuffer vbo) {

	IBO = ibo;
	VBO = vbo;

	GLCall(glGenVertexArrays(1, &ID));
	IBO.use();
	VBO.use();
}

VAO::VAO(IndexBuffer ibo, VertexBuffer vbo, GLsizei vertices) {

	this->vertices = vertices;
	IBO = ibo;
	VBO = vbo;

	GLCall(glGenVertexArrays(1, &ID));
	this->use();
	IBO.use();
	VBO.use();
}

VAO::~VAO() {

	GLCall(glDeleteVertexArrays(1, &ID));

}

void VAO::addAttribute(GLenum type, GLsizei size) {

	this->use();
	layout.push_back({processType(type), false, size});

	unsigned long offset = 0;

	unsigned int stride = 0;

	for (auto i = layout.begin(); i != layout.end(); i++) {
		stride += sizeof(i->type) * i->size; 
	}
	
	for (int i = 0; i < layout.size(); i++) {
		GLCall(glEnableVertexAttribArray(i));

		GLCall(glVertexAttribPointer(i, 4, type, false, stride, (void *) offset));
		offset = sizeof(type) * 4;
	}

}

void VAO::use() {

	GLCall(glBindVertexArray(ID));

}

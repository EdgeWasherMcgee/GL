#include "vao.h"

VAO::VAO(IndexBuffer ibo, VertexBuffer vbo) {

	IBO = ibo;
	VBO = vbo;

	GLCall(glGenVertexArrays(1, &ID));

	this->use();
	IBO.use();
	VBO.use();
	GLCall(glBindVertexArray(0));
}

VAO::~VAO() {

	GLCall(glDeleteVertexArrays(1, &ID));

}

void VAO::addAttribute(GLenum type, GLsizei size) {

	this->use();

	unsigned long offset = 0;

	unsigned int stride = 0;

	layout.push_back({type, false, size});

	for (auto i = layout.begin(); i != layout.end(); i++) {
		stride += getTypeSize(type) * i->size; 
	}
	
	for (int i = 0; i < layout.size(); i++) {
		GLCall(glVertexAttribPointer(i, layout[i].size, layout[i].type, layout[i].normalize, stride, (void *) offset));
		offset = getTypeSize(type) * 4;

		GLCall(glEnableVertexAttribArray(i));
	}
}

GLsizei VAO::getTypeSize(GLenum type) {

	switch (type){
		case GL_FLOAT:
			return sizeof(float);

		case GL_UNSIGNED_SHORT:
			return sizeof(unsigned short);

		case GL_UNSIGNED_INT:
			return sizeof(unsigned int);
	}

	std::cout << "Type (" << type << ") not supported" << std::endl;
	return 0;
} 

void VAO::drawElements(GLenum mode, GLsizei count) {

	this->use();
	GLCall(glDrawElements(mode, count, GL_UNSIGNED_SHORT, NULL));

}

void VAO::drawArrays(GLenum mode, GLuint offset, GLsizei count) {

	this->use();
	GLCall(glDrawArrays(mode, offset, count));

}

void VAO::use() {

	GLCall(glBindVertexArray(ID));

}
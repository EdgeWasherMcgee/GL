#include "vao.h"

VertexArray::VertexArray() {

	GLCall(glGenVertexArrays(1, &ID));

	use();
	IBO.use();
	VBO.use();
	
}

VertexArray::~VertexArray() {

	GLCall(glDeleteVertexArrays(1, &ID));
	VBO.deleteBuffer();
	IBO.deleteBuffer();

}

void VertexArray::addAttribute(GLenum type, GLsizei size) {

	use();

	unsigned long offset = 0;

	unsigned int stride = 0;

	layout.push_back({type, GL_FALSE, size});

	for (auto i = layout.begin(); i != layout.end(); i++) {
		stride += getTypeSize(i->type) * i->size; 
	}
	
	for (int i = 0; i < layout.size(); i++) {

		// printf("glVertexAttribPointer(%d, %d, %d, %d, %d, %lu)\n", i, layout[i].size, layout[i].type, layout[i].normalize, stride, offset);
		GLCall(glVertexAttribPointer(i, layout[i].size, layout[i].type, layout[i].normalize, stride, (void *) offset));		
		GLCall(glEnableVertexAttribArray(i));

		offset = getTypeSize(type) * layout[i].size;
	}

	disuse();
}

GLsizei VertexArray::getTypeSize(GLenum type) const {

	switch (type) {

		case GL_FLOAT:
			return sizeof(GLfloat);

		case GL_UNSIGNED_SHORT:
			return sizeof(GLushort);

		case GL_SHORT:
			return sizeof(GLshort);

		case GL_UNSIGNED_INT:
			return sizeof(GLuint);

		case GL_INT:
			return sizeof(GLint);
	}

	std::cout << "Type (" << type << ") not supported" << std::endl;
	return 0;
} 

void VertexArray::drawElements(GLenum mode, GLsizei count) const {

	use();
	GLCall(glDrawElements(mode, count, GL_UNSIGNED_SHORT, NULL));

}

void VertexArray::drawArrays(GLenum mode, GLuint offset, GLsizei count) const {

	use();
	GLCall(glDrawArrays(mode, offset, count));

}

inline void VertexArray::use() const {

	GLCall(glBindVertexArray(ID));

}

inline void VertexArray::disuse() const {

	GLCall(glBindVertexArray(0));

}
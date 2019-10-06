#include "vao.h"

VertexArray::VertexArray() {

	GLCall(glGenVertexArrays(1, &ID));

	use();
	IBO.use();
	VBO.use();
	
}

void VertexArray::addAttribute(VertexStorageMode vertexStorage, GLenum type, GLsizei size, GLsizei count) {

	use();

	unsigned int stride = 0;

	unsigned int offset = 0;

	if (vertexStorage == VertexFirst) {

		firstByteSize = 0;

		firstLayout.push_back({type, GL_FALSE, size, count});

		for (int i = 0; i < firstLayout.size(); i++) {
			GLCall(glVertexAttribPointer(i, firstLayout[i].size, firstLayout[i].type, firstLayout[i].normalize, stride, INT2VOIDP firstByteSize));		
			GLCall(glEnableVertexAttribArray(i));

			firstByteSize += getTypeSize(type) * firstLayout[i].size * firstLayout[i].count;
		}

	}

	if (vertexStorage == VertexWeave) {

		weaveByteSize = 0;

		weaveLayout.push_back({type, GL_FALSE, size, count});

		for (auto i = weaveLayout.begin(); i != weaveLayout.end(); i++) {
			stride += getTypeSize(i->type) * i->size; 
		}
	
	
		for (int i = 0; i < weaveLayout.size(); i++) {

			// printf("glVertexAttribPointer(%d, %d, %d, %d, %d, %lu)\n", i, weaveLayout[i].size, weaveLayout[i].type, weaveLayout[i].normalize, stride, offset);
			GLCall(glVertexAttribPointer(i + firstLayout.size(), weaveLayout[i].size, weaveLayout[i].type, weaveLayout[i].normalize, stride, INT2VOIDP (firstByteSize + offset)));		
			GLCall(glEnableVertexAttribArray(i + firstLayout.size()));

			offset += getTypeSize(weaveLayout[i].type) *weaveLayout[i].size;
			weaveByteSize += getTypeSize(weaveLayout[i].type) * weaveLayout[i].size * weaveLayout[i].count;
		}
	}

	if(vertexStorage == VertexLast) {

		lastByteSize = 0;

		lastLayout.push_back({type, GL_FALSE, size, count});

		for (int i = 0; i < lastLayout.size(); i++) {
			GLCall(glVertexAttribPointer(i + firstLayout.size() + weaveLayout.size(), lastLayout[i].size, lastLayout[i].type, lastLayout[i].normalize, stride, INT2VOIDP (firstByteSize + weaveByteSize + lastByteSize)));		
			GLCall(glEnableVertexAttribArray(i + firstLayout.size() + weaveLayout.size()));

			lastByteSize += getTypeSize(type) * lastLayout[i].size;
		}

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

void VertexArray::deleteBuffer() {

	GLCall(glDeleteVertexArrays(1, &ID));
	VBO.deleteBuffer();
	IBO.deleteBuffer();

}
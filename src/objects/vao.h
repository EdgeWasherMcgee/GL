#pragma once
#include "../common/renderer.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include <vector>

struct vertexArrayObjectLayout {

	GLenum type;
	bool normalize;
	GLsizei size;

};

class VAO {

public:

	VAO(IndexBuffer ibo, VertexBuffer vbo);
	~VAO();

	void addAttribute(GLenum type, GLsizei size);

	void drawElements(GLenum mode, GLsizei count);

	void drawArrays(GLenum mode, GLuint offset, GLsizei count);

	void use();

private:

	std::vector<vertexArrayObjectLayout> layout;

	GLuint ID;

	IndexBuffer IBO;
	VertexBuffer VBO;

	GLsizei getTypeSize(GLenum type);

};
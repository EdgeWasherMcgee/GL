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
	VAO(IndexBuffer ibo, VertexBuffer vbo, GLsizei vertices);
	~VAO();

	void addAttribute(GLenum type, GLsizei stride);

	void use();

private:

	std::vector<vertexArrayObjectLayout> layout;

	GLuint ID;
	GLsizei vertices;

	IndexBuffer IBO;
	VertexBuffer VBO;

};
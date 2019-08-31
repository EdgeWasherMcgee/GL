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

class VertexArray {

public:

	VertexArray();
	~VertexArray();

	void addAttribute(GLenum type, GLsizei size);

	void drawElements(GLenum mode, GLsizei count);

	void drawArrays(GLenum mode, GLuint offset, GLsizei count);

	inline void use();

	inline void disuse();

	IndexBuffer IBO;
	VertexBuffer VBO;

private:

	std::vector<vertexArrayObjectLayout> layout;

	GLuint ID;

	GLsizei getTypeSize(GLenum type);

};
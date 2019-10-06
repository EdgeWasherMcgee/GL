#pragma once
#include "../common/renderer.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include <vector>

enum VertexStorageMode {

	VertexFirst = 0,
	VertexWeave = 1,
	VertexLast = 2

};

struct vertexArrayObjectLayout {

	GLenum type;
	bool normalize;
	GLsizei size;
	GLsizei count;

};

class VertexArray {

public:

	VertexArray();

	void addAttribute(VertexStorageMode vertexStorage, GLenum type, GLsizei size, GLsizei count);

	void drawElements(GLenum mode, GLsizei count) const;

	void drawArrays(GLenum mode, GLuint offset, GLsizei count) const;

	inline void use() const;

	inline void disuse() const;

	void deleteBuffer();

	IndexBuffer IBO;
	VertexBuffer VBO;

private:


	std::vector<vertexArrayObjectLayout> firstLayout;
	std::vector<vertexArrayObjectLayout> weaveLayout;
	std::vector<vertexArrayObjectLayout> lastLayout;

	GLsizei firstByteSize;
	GLsizei weaveByteSize;
	GLsizei lastByteSize;

	GLuint ID;

	GLsizei getTypeSize(GLenum type) const;

};
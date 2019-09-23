#pragma once
#include "../common/renderer.h"

class IndexBuffer {

public:

	IndexBuffer();

	void allocateData(GLsizeiptr size);

	void subData(GLuint offset, GLsizeiptr size, GLushort data[]);

	void bufferData(GLsizeiptr size, GLushort data[]);

	void deleteBuffer();

	inline void use() const;

	inline void disuse() const;

private:


	GLuint ID;
	GLsizeiptr bufferSize;

};
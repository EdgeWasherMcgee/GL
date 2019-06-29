LINKERFLAGS = -lGL -lGLU -lGLEW -lglfw
COMPILEFILES = App.cpp Renderer.cpp IndexBuffer.cpp VertexBuffer.cpp VertexBufferLayout.cpp VertexArray.cpp
COMPILEFLAGS = -g

app: ${COMPILEFILES}
	g++ -o $@ ${COMPILEFILES} ${LINKERFLAGS}


debug: ${COMPILEFILES}
	g++ -o $@ ${COMPILEFILES} ${COMPILEFLAGS} ${LINKERFLAGS}

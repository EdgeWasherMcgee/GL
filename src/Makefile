LINKERFLAGS = -lGL -lGLU -lGLEW -lglfw
COMPILEFILES = App.cpp ./common/renderer.cpp ./common/shaderHandler.cpp
COMPILEFLAGS = -g

app: ${COMPILEFILES}
	g++ -o $@ ${COMPILEFILES} ${LINKERFLAGS}


debug: ${COMPILEFILES}
	g++ -o $@ ${COMPILEFILES} ${COMPILEFLAGS} ${LINKERFLAGS}

clean:
	rm debug app
SOURCEFILES = common/renderer.cpp objects/vao.cpp objects/vertexBuffer.cpp objects/indexBuffer.cpp camera.cpp
OBJFILES = ${notdir ${SOURCEFILES:.cpp=.o}}
INCLUDES = -lGL -lGLU -lGLEW -lglfw
DEBUGPARAMS = -g

try: try.cpp ${OBJFILES}
	g++ -o $@ try.cpp $(OBJFILES) ${INCLUDES}

app: App.cpp ${OBJFILES}
	g++ -o $@ App.cpp $(OBJFILES) ${INCLUDES}

debug: ${SOURCEFILES}
	g++ ${SOURCEFILES} ${DEBUGPARAMS} -o $@ ${INCLUDES}

%.o : %.cpp
	g++ -c $< -o $@ 

%.o : common/%.cpp
	g++ -c $< -o $@ 

%.o : objects/%.cpp
	g++ -c $< -o $@

clean: 
	rm -f *.o app try

print:
	@echo "OBJFILES: $(OBJFILES)"

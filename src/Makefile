SOURCEFILES = App.cpp common/renderer.cpp
OBJFILES = ${notdir ${SOURCEFILES:.cpp=.o}}
INCLUDES = -lGL -lGLU -lGLEW -lglfw
DEBUGPARAMS = -g

app: ${OBJFILES}
	g++ -o $@ $(OBJFILES) ${INCLUDES}

debug: ${SOURCEFILES}
	g++ ${SOURCEFILES} ${DEBUGPARAMS} -o $@ ${INCLUDES}

%.o : %.cpp
	g++ -c $< -o $@ 

%.o : common/%.cpp
	g++ -c $< -o $@ 


clean: 
	rm -f *.o app

print :
	@echo "OBJFILES: $(OBJFILES)"

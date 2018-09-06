EXECUTABLE=text.x
OUTDIR = build
FLAGS = -std=c++11 -lglut -lGL -lGLU
GCC = c++

all: directories $(EXECUTABLE)
	./$(EXECUTABLE)

$(EXECUTABLE): $(OUTDIR)/main.o 
	$(GCC) $(FLAGS) -o $(EXECUTABLE) $(OUTDIR)/main.o -lglut -lGL -lGLU

$(OUTDIR)/main.o: main.cpp
	$(GCC) $(FLAGS) -c main.cpp -o $(OUTDIR)/main.o 

directories: $(OUTDIR)

$(OUTDIR):
	mkdir -p $(OUTDIR)

clean: 
	rm -rf $(OUTDIR)
	rm $(EXECUTABLE)

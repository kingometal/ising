EXECUTABLE=ising.x
OUTDIR = build
FLAGS = -std=c++11 -lSDL2 -lSDL2_image -lpthread
GCC = c++


all: directories $(EXECUTABLE)


$(EXECUTABLE): $(OUTDIR)/main.o $(OUTDIR)/view.o
	$(GCC) -o $(EXECUTABLE) $(OUTDIR)/view.o $(OUTDIR)/main.o $(FLAGS)

$(OUTDIR)/main.o: main.cpp $(OUTDIR)/view.o view.h
	$(GCC) $(FLAGS) -c main.cpp -o $(OUTDIR)/main.o

$(OUTDIR)/view.o: view.cpp view.h
	$(GCC) $(FLAGS) -c view.cpp -o $(OUTDIR)/view.o

directories: $(OUTDIR)

$(OUTDIR):
	mkdir -p $(OUTDIR)

clean: 
	rm -rf $(OUTDIR)
	rm $(EXECUTABLE)



run: all
	./$(EXECUTABLE)

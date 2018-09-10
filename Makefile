# Defines
EXECUTABLE=waves.x
OUTDIR = build
FLAGS = -std=c++11 -lSDL2 -lpthread
GCC = c++


# Default make target
all: directories $(EXECUTABLE)


$(EXECUTABLE): $(OUTDIR)/main.o
	$(GCC) -o $(EXECUTABLE) $(OUTDIR)/main.o $(OUTDIR)/View.o $(OUTDIR)/Model.o $(FLAGS)

$(OUTDIR)/main.o: main.cpp $(OUTDIR)/View.o $(OUTDIR)/Model.o
	$(GCC) $(FLAGS) -c main.cpp -o $(OUTDIR)/main.o

$(OUTDIR)/View.o: View.cpp View.h $(OUTDIR)/Model.o
	$(GCC) $(FLAGS) -c View.cpp -o $(OUTDIR)/View.o

$(OUTDIR)/Model.o: Model.cpp Model.h ModelInterface.h
	$(GCC) $(FLAGS) -c Model.cpp -o $(OUTDIR)/Model.o


directories: $(OUTDIR)

$(OUTDIR):
	mkdir -p $(OUTDIR)


# Additional make targets
clean: 
	rm -rf $(OUTDIR)
	rm $(EXECUTABLE)

run: all
	./$(EXECUTABLE)

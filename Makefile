# Defines
EXECUTABLE=ising.x
OUTDIR = build
FLAGS = -std=c++11 -lSDL2 -lpthread
GCC = c++


# Default make target
all: directories $(EXECUTABLE)


$(EXECUTABLE): $(OUTDIR)/main.o
	$(GCC) -o $(EXECUTABLE) $(OUTDIR)/main.o $(OUTDIR)/view.o $(OUTDIR)/model.o $(FLAGS)

$(OUTDIR)/main.o: main.cpp $(OUTDIR)/view.o $(OUTDIR)/model.o
	$(GCC) $(FLAGS) -c main.cpp -o $(OUTDIR)/main.o

$(OUTDIR)/view.o: view.cpp view.h $(OUTDIR)/model.o
	$(GCC) $(FLAGS) -c view.cpp -o $(OUTDIR)/view.o

$(OUTDIR)/model.o: model.cpp model.h modelinterface.h
	$(GCC) $(FLAGS) -c model.cpp -o $(OUTDIR)/model.o


directories: $(OUTDIR)

$(OUTDIR):
	mkdir -p $(OUTDIR)


# Additional make targets
clean: 
	rm -rf $(OUTDIR)
	rm $(EXECUTABLE)

run: all
	./$(EXECUTABLE)

OUTDIR = build
FLAGS = -std=c++11 `pkg-config --cflags gtk+-2.0 --libs`
GCC = c++

all: directories ising.x
#:w	./ising.x 100 3

ising.x: $(OUTDIR)/main.o $(OUTDIR)/view.o $(OUTDIR)/model.o
	$(GCC) $(FLAGS) -o ising.x $(OUTDIR)/main.o $(OUTDIR)/view.o $(OUTDIR)/model.o `pkg-config --cflags gtk+-2.0 --libs`;

$(OUTDIR)/main.o: main.cpp view.h
	$(GCC) $(FLAGS) -c main.cpp -o $(OUTDIR)/main.o

$(OUTDIR)/model.o: model.cpp model.h
	$(GCC) $(FLAGS) -c model.cpp -o $(OUTDIR)/model.o

$(OUTDIR)/view.o: view.cpp view.h
	$(GCC) $(FLAGS) -c view.cpp -o $(OUTDIR)/view.o


directories: $(OUTDIR)


$(OUTDIR):
	mkdir -p $(OUTDIR)

clean: 
	rm -rf $(OUTDIR)
	rm ising.x

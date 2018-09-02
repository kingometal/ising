all: ising.x
	./ising.x 100 3
ising.x:
	c++  -o ising.x ising.cc `pkg-config --cflags gtk+-2.0 --libs`; 

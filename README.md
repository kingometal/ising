# A visualisation of ising model configurable using hotkeys
 
# note about the implementation: 
the code is written by a person (me) who had a very vague idea of c/c++ at that time. I will try to fix it if I come to this

At this point I have no idea of how to write a README

# Description
The purpose of the program is to visualize the ising model.
The program simulates the ising model on a rectangular lattice of variable size.
The lattice nodes are called "fields" here.
It visualizes the ising model and shows the current temperature, magnetic field and magnetization.

The propagation of mean magnetization is stored into the file m.out

Mean magnetization values per field are stored internally, and can be displayed by pressing "m"(toggle-key) and reset by pressing "c".


# List of the hotkeys:
Arrow up, a    : increment the magnetic field (H) by the magnetic field step (dH) -> H = H + dH

Arrow down, s  : decrement the magnetic field (H) by the magnetic field step (dH) -> H = H - dH

Arrow left, l  : increase the magnetic field step (dH) by the factor ten -> dH = dH * 10

Arrow right, k : decrease the magnetic field step (dH) by the factor ten -> dH = dH / 10

NUM + , q      : increment temperature (T) by the temperature step (dT) -> T = T + dT

NUM - , w      : decrement temperature (T) by the temperature step (dT) -> T = T - dT

NUM * , i      : increase the temperature step (dH) by the factor ten -> dT = dT * 10

NUM / , o      : decrease the temperature step (dH) by the factor ten -> dT = dT / 10

NUM 0          : reset magnetic field (H) to zero

r              : reset simulation and settings (reset means "fill all fields with random values")

n              : reset simulation but leave settings at current values

e              : increase speed by factor 2

d              : decrease speed by factor 2

m              : toggle showing mean magnetization values

c              : reset stored mean magnetization values


# Compile instructions: 
Simply run "make". An executable ising.x would be created and run on a 100x100 lattice with magnification of 3

# Prerequisites: 
The following packages are required to compile it:

pgk-config, gtk+-2.0, gcc
 


# Command line parameters: 
ising.x \<lattice size\> \<magnification\>

\<lattice size\>: the simulation simulates an ising model on rectangular lattice of size \<lattice size\>x\<lattice size\>

\<magnification\>: each field of the lattice is displayed as \<magnification\>x\<magnification\> pixels. 


# Experimental: Docker
For those who prefer using Docker instead of installing required libraries, can try to compile and run the code from a docker-container.
The script <b>runIsingInDocker.sh</b> contains all required commands and should run out-of-the box. 
The only prerequisite is installed docker and current user being in the docker group (or run the script as sudo, which is generally not recommended).

I mark this feature experimental because I experienced freezes of the program when running it this way.

# Future scope
I plan to enhance the source code readability and structure to make the program more comprehensive.

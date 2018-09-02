# A visualisation of ising model configurable using hotkeys
# 
# note about the implementation: the code is written by a person (me) who had a very vague idea of c/c++ at that time. I will try to fix it if I come to this
# At this point I have no idea of how to write a README
#
# The program stores mean magnetization into the file m.out
# The program stores mean magnetization values per field (a field is one node in the ising lattice), which can be displayed by pressing "m" and reset by pressing "c"
#
#
# List of the hotkeys:
# Arrow up, a    : increment the magnetic field (H) by the magnetic field step (dH) -> H = H + dH
# Arrow down, s  : decrement the magnetic field (H) by the magnetic field step (dH) -> H = H - dH
# Arrow left, l  : increase the magnetic field step (dH) by the factor ten -> dH = dH * 10
# Arrow right, k : decrease the magnetic field step (dH) by the factor ten -> dH = dH / 10
# NUM + , q      : increment temperature (T) by the temperature step (dT) -> T = T + dT
# NUM - , w      : decrement temperature (T) by the temperature step (dT) -> T = T - dT
# NUM * , i      : increase the temperature step (dH) by the factor ten -> dT = dT * 10
# NUM / , o      : decrease the temperature step (dH) by the factor ten -> dT = dT / 10
# NUM 0          : reset magnetic field (H) to zero
# r              : reset simulation and settings (reset means "fill all fields with random values")
# n              : reset simulation but leave settings at current values
# e              : increase speed by factor 2
# d              : decrease speed by factor 2
# m              : toggle showing mean magnetization values
# c              : reset stored mean magnetization values
#
#
# Compile instructions: 
# the bash script "compile.sh" does the job. It creates an executable ising.x and runs it on a 100x100 lattice with magnification of 3
# 
#
# Prerequisites: 
# following packages are required to compile it:
# pgk-config, gtk+-2.0, gcc
# 
#
#
# command line parameters: ising.h <lattice size> <magnification>
# <lattice size>: the simulation simulates an ising model on rectangular lattice of size <lattice size>x<lattice size>
# <magnification>: each field of the lattice is displayed as <magnification>x<magnification> pixels. 

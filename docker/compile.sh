#!/bin/bash
SCRIPTPATH="$( cd "$(dirname "$0")" ; pwd -P )"
cd $SCRIPTPATH/..
c++  -o ising.x ising.cc `pkg-config --cflags gtk+-2.0 --libs`; 
chmod +x ising.x
cd -
$SCRIPTPATH/../ising.x 100 3

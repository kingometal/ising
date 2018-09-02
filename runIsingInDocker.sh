#!/bin/bash
docker build -t ising-image .
#docker run --rm -it -e DISPLAY -v $(pwd)/../:/src -v /tmp/.X11-unix:/tmp/.X11-unix:ro -v $XAUTHORITY:/root/.Xauthority --net=host ising-image
#docker run --rm -it -e DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix:ro -v $XAUTHORITY:/root/.Xauthority --net=host ising-image
docker run --rm -it -e DISPLAY -v $XAUTHORITY:/root/.Xauthority --net=host ising-image 

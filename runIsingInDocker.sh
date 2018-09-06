#!/bin/bash
set -ex
docker build -t opengltest-image .
docker run --rm -it -e DISPLAY -v $XAUTHORITY:/root/.Xauthority --net=host --name opengltest-container opengltest-image 

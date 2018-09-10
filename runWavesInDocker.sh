#!/bin/bash
set -ex
docker build -t waves-image .
docker run --rm -it -e DISPLAY -v $XAUTHORITY:/root/.Xauthority --net=host --name waves-container waves-image 

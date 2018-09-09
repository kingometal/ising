#FROM alpine:3.7
FROM ubuntu:bionic

# http://lazyfoo.net/tutorials/SDL/01_hello_SDL/index2.php
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y make
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --fix-missing libsdl2-dev libsdl2-image-dev
#RUN DEBIAN_FRONTEND=noninteractive apt-get install -y g++
#RUN DEBIAN_FRONTEND=noninteractive apt-get install -y libfltk1.3-dev 
#RUN DEBIAN_FRONTEND=noninteractive apt-get install -y pkg-config
#RUN DEBIAN_FRONTEND=noninteractive apt-get install -y freeglut3-dev
#RUN DEBIAN_FRONTEND=noninteractive apt-get install -y libgl1-mesa-dev libglew1.5-dev freeglut3-dev libglm-dev

#COPY *.cc /
COPY *.cpp /
COPY *.h /
COPY Makefile /
CMD make run


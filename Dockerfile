#FROM alpine:3.7
FROM ubuntu:bionic

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y git make
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y g++
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y libfltk1.3-dev 
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y pkg-config
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y freeglut3-dev
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y libgl1-mesa-dev libglew1.5-dev freeglut3-dev libglm-dev
RUN find -iname "*glut*.pc"

#COPY *.cc /
COPY *.cpp /
#COPY *.h /
COPY Makefile /
CMD make


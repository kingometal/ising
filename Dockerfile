FROM alpine:3.7

RUN apk add --no-cache pkgconfig gtk+2.0-dev g++ libcanberra-gtk2 make

COPY *.cc /
COPY *.cpp /
COPY *.h /
COPY Makefile /
CMD make 


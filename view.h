#ifndef ISING_VIEW_H
#define ISING_VIEW_H

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 480;

void complete_ising_init(int argc, char **argv);

void* fillPixels(void*arg);
void* run(void* ptr);

#endif // ISING_VIEW_H

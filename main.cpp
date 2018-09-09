#include "view.h"
#include <pthread.h>
#include <iostream>



//void putPixelRGB(SDL_Renderer* renderer, int x, int y, unsigned char r, unsigned char g, unsigned char b)
//{
//    SDL_SetRenderDrawColor(renderer, (Uint8)r, (Uint8)g, (Uint8)b, 255);
//    SDL_RenderDrawPoint(renderer, x, y);
//}


int main(int argc, char** argv) 
{
    uint32_t PixelBuffer[SCREEN_WIDTH*SCREEN_HEIGHT];
    pthread_t thread_info;
    int  iret;

    iret = pthread_create( &thread_info, NULL, &run, PixelBuffer);

    pthread_t thread_info2;
    int  iret2;
    iret2 = pthread_create( &thread_info2, NULL, &fillPixels, PixelBuffer);

    pthread_join(thread_info2, NULL);

    pthread_join(thread_info, NULL);
    //    run((void*) NULL);
    return 0;
}

#include "view.h"
#include <SDL2/SDL.h>
#include <chrono>
#include <iostream>

namespace
{

//    uint32_t PixelBuffer[SCREEN_WIDTH*SCREEN_HEIGHT];
    bool Quit;
}

void* run(void* ptr)
{
    std::cout << "start run" << std::endl;
    uint32_t* PixelBuffer = (uint32_t*) ptr;
    std::cout << "pixbuf" << PixelBuffer[0] << std::endl;
    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;
    //The surface contained by the window
    SDL_Surface* gScreenSurface = NULL;

    //Start up SDL and create window
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "Ising Model", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );

            if (NULL == gScreenSurface)
            {
                printf( "Can not get surface! SDL_Error: %s\n", SDL_GetError() );
            }
            else
            {

                //Main loop flag
                Quit = false;
                //Event handler
                SDL_Event e;
                uint32_t* pixels = ((Uint32 *) (gScreenSurface->pixels));


                std::chrono::milliseconds currentTime = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
                std::chrono::milliseconds previousCheckpoint = currentTime;
                int framecount = 0;

                // Main Loop
                while( !Quit )
                {
                    while( SDL_PollEvent( &e ) != 0 )
                    {
                        //User requests quit
                        if( e.type == SDL_QUIT )
                        {
                            Quit = true;
                        }

                        //User presses a key
                        else if( e.type == SDL_KEYDOWN )
                        {
                            //Select surfaces based on key press
                            switch( e.key.keysym.sym )
                            {
                            case SDLK_q: Quit = true;
                                break;

                            default:
                                break;
                            }

                        }
                    }

                    //-----------------------
                    // FPS counter
                    {
                        ++framecount;
                        currentTime = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
                        if ( (currentTime - previousCheckpoint).count() >= 1000)
                        {
                            if (currentTime > previousCheckpoint)
                            {
                                std::cout << "fps:" << (double) (framecount) / (double) ((currentTime-previousCheckpoint).count()/1000.0) << std::endl;
                            }
                            framecount = 0;
                            previousCheckpoint = currentTime;
                        }
                    }
                    //-----------------------


                    //                SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );
                    //-----------------------
                    // Fill Surface
                    {
                        if (gScreenSurface != NULL)
                        {
                            for (int y = 0; y < gScreenSurface->h; y++)
                            {
                                int index0 = y * gScreenSurface->w;
                                for (int x = 0; x < gScreenSurface->w; x++)
                                {
                                    int index = index0 + x;
                                    //                            std::cout << "new pixel RGB: " << (newPixel&0xFF) << " " << ((newPixel >> 8) &0xFF) << " " << ((newPixel >> 16) &0xFF) << " "<< ((newPixel >> 24) &0xFF) << " "<< std::endl;

                                    pixels[index] = PixelBuffer[index];
                                }
                            }

                        }
                        //-----------------------

                        //Update the surface
                        SDL_UpdateWindowSurface( gWindow );
                        //                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    }
                }

                //Deallocate surface
                SDL_FreeSurface( gScreenSurface );
                gScreenSurface = NULL;
            }
            //Destroy window
            SDL_DestroyWindow( gWindow );
            gWindow = NULL;
        }
        //Quit SDL subsystems
        SDL_Quit();
    }
    return NULL;
}

void* fillPixels(void* arg)
{
    std::cout << "start fill pixels" << std::endl;
    uint32_t* PixelBuffer = (uint32_t*) arg;
    std::cout << "pixbuf" << PixelBuffer[0] << std::endl;
    int timer = 0;
    while (false == Quit)
    {
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            int index0 = y * SCREEN_WIDTH;
            for (int x = 0; x < SCREEN_WIDTH; x++)
            {
                int index = index0 + x;

                uint32_t newPixel = 0;
                newPixel |= 255 << 24 ;
                newPixel |= ((y+timer)%255) << 16 ;
                newPixel |= ((x+timer)%255) << 8 ;
                newPixel |= (timer)%255  ;
                PixelBuffer[index] = newPixel;
            }
        }
        timer++;
    }
    return NULL;
}



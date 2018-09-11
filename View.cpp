#include "View.h"
#include "ModelInterface.h"
#include <SDL2/SDL.h>
#include <chrono>
#include <iostream>
#include <unistd.h>

namespace
{
    bool Quit;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    const int MAX_FPS = 50;
}

void* RunView(void* arg)
{
    ModelInterface* model = static_cast<ModelInterface*>(arg);

    int height = model->GetHeight();
    int width = model->GetWidth();

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        SDL_Window* gWindow = SDL_CreateWindow( "Ising Model", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get window surface
            SDL_Surface* gScreenSurface = SDL_GetWindowSurface( gWindow );

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


                //-----------------
                // Init FPS counter
                std::chrono::milliseconds currentTime = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
                std::chrono::milliseconds previousCheckpoint = currentTime;
                int framecount = 0;
                uint64_t currentFrameOutputTime = SDL_GetPerformanceCounter();
                uint64_t lastFrameOutputTime = currentFrameOutputTime;
		double min_frame_time = 1.0/(double)MAX_FPS;

                //-----------------

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
                            pthread_mutex_lock(&mutex); // critical section
                            switch( e.key.keysym.sym )
                            {
                            case SDLK_q: Quit = true;
                                break;
                            case SDLK_KP_PLUS:
                                model->KeyPressed(KEY_NUM_PLUS);
                                break;
                            case SDLK_KP_MINUS:
                                model->KeyPressed(KEY_NUM_MINUS);
                                break;
                            case SDLK_KP_DIVIDE:
                                model->KeyPressed(KEY_NUM_DIVIDE);
                                break;
                            case SDLK_KP_MULTIPLY:
                                model->KeyPressed(KEY_NUM_MULTIPLY);
                                break;
                            case SDLK_LEFT:
                                model->KeyPressed(KEY_ARROW_LEFT);
                                break;
                            case SDLK_RIGHT:
                                model->KeyPressed(KEY_ARROW_RIGHT);
                                break;
                            case SDLK_UP:
                                model->KeyPressed(KEY_ARROW_UP);
                                break;
                            case SDLK_DOWN:
                                model->KeyPressed(KEY_ARROW_DOWN);
                                break;
                            case SDLK_a:
                                model->KeyPressed(KEY_A);
                                break;
                            case SDLK_s:
                                model->KeyPressed(KEY_S);
                                break;


                            default:
                                break;
                            }
                            pthread_mutex_unlock(&mutex); // end of critical section
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
                        pthread_mutex_lock(&mutex);
                        if (gScreenSurface != NULL)
                        {
                            for (int y = 0; y < gScreenSurface->h; y++)
                            {
                                int index0 = y * gScreenSurface->w;
                                for (int x = 0; x < gScreenSurface->w; x++)
                                {
                                    int index = index0 + x;
                                    if (model->GetBinaryData(x, y))
                                    {
                                        pixels[index] = 0x00000000;
                                    }
                                    else
                                    {
                                        pixels[index] = 0xFFFFFFFF;
                                    }

                                }
                            }
                        }
                        pthread_mutex_unlock(&mutex);
                        //-----------------------
                        //Update the surface
                        currentFrameOutputTime = SDL_GetPerformanceCounter();
                        if ((double)(currentFrameOutputTime-lastFrameOutputTime)/(double) SDL_GetPerformanceFrequency() > min_frame_time)
                        {
                           SDL_UpdateWindowSurface( gWindow );
                           lastFrameOutputTime = currentFrameOutputTime;
                        }
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

void* RunModel(void* arg)
{
    ModelInterface* model = static_cast<ModelInterface*> (arg);

    while (false == Quit)
    {
        pthread_mutex_lock(&mutex);
        model->Iterate();
        pthread_mutex_unlock(&mutex);
	usleep(100);
    }
    return NULL;
}



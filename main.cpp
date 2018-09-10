#include "view.h"
#include "model.h"
#include <pthread.h>
#include <iostream>

const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 300;

int main(int argc, char** argv) 
{
    Ising::Model model (SCREEN_WIDTH, SCREEN_HEIGHT);

    { // drawing thread
	    pthread_t thread_info;
	    int  iret;
        iret = pthread_create( &thread_info, NULL, &RunView, &model);
	    { // calculating thread
		    pthread_t thread_info2;
		    int  iret2;
            iret2 = pthread_create( &thread_info2, NULL, &RunModel, &model);
		    pthread_join(thread_info2, NULL);
	    }
	pthread_join(thread_info, NULL);
    }
    return 0;
}

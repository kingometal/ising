#ifndef ISING_VIEW_H
#define ISING_VIEW_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

//fenstergroesse
//int height, width;
//the global pixmap that will serve as our buffer

void complete_ising_init(int argc, char **argv);


//gboolean timer_exe(GtkWidget * window);

//gboolean on_window_expose_event(GtkWidget * da, GdkEventExpose * event, gpointer user_data);
//gboolean keypress( GtkWidget *wi, GdkEventKey *event, gpointer func_data);

class View
{
    public:
        View();
        ~View();
//    static int WindowWidth;
//    static int WindowHeight;
    int Magnitude;

    void SetWindowHeight(int height);
    void SetWindowWidth(int width);
    void SetMagnitude(int magn);

    void InitGtk(int argc, char *argv[]);
//    static void *do_draw(void *ptr);
    //    static gboolean timer_exe(GtkWidget *window);
};


#endif // ISING_VIEW_H

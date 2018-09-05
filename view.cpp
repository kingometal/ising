#include "view.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <tuple>
#include <vector>
#include <cmath>

// ...

using namespace std::chrono;
using namespace std;


void complete_ising_init(int argc, char** argv)
{
//    mOut = fopen ("m.out", "w");
}

namespace
{
    int currently_drawing = 0;
    int WindowWidth = 0;
    int WindowHeight = 0;
    int calculating = 0;
    int magnitude = 2;
    int* buffer1;
    int* buffer2;

    GdkPixmap *pixmap = NULL;
    cairo_surface_t *cst;
    cairo_t *cr;
    cairo_t *cr_pixmap;

    void * do_draw(void *ptr){
        currently_drawing = 1;

        static int framecount = 0;
        static milliseconds previousCheckpoint;
        ++framecount;
        milliseconds currentTime = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
        if ( (currentTime - previousCheckpoint).count() >= 1000)
//        if (++execcount % maxExecCount == 0)
        {
//            std::cout << "timer exe" << execcount << ":" << currentTime.count() << std::endl;
            if (currentTime > previousCheckpoint)
            {
                std::cout << "fps:" << (double) (framecount) / (double) ((currentTime-previousCheckpoint).count()/1000.0) << std::endl;
            }
            framecount = 0;
            previousCheckpoint = currentTime;
        }


        gdk_threads_enter();
//        gdk_drawable_get_size(pixmap, &WindowWidth, &WindowHeight);
        static int counter = 0;
        static int MaxCounter = 255;
        if (++counter % MaxCounter == 0)
        {
            counter = 0;
        }
    //    do_ising(cr);
//        cairo_set_source_rgb (cr, 1.0, 0.5, 1.0);
//        cairo_paint(cr);
//        cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
        double timeValue = 2*((counter/(double)MaxCounter)<0.5?(counter/(double)MaxCounter):1.0-(counter/(double)MaxCounter));

        for (int j = 0; j< WindowHeight; j+=magnitude)
        {
            int index1 = j*WindowWidth;
            for (int k = 0; k< WindowWidth ; k+=magnitude){
                int index = index1 + k;
                buffer1[index] = timeValue*255.0;
                if (abs(buffer2[index] - buffer1[index]) >= 10)
                {
                    cairo_set_source_rgba (cr, (buffer1[index]/(double) 255), (buffer1[index]/(double) 255), 0, 1);
                    cairo_rectangle(cr, k, j, magnitude,magnitude);
                    cairo_fill (cr);
                    buffer2[index] = buffer1[index];
                }
            }
        }

//        cairo_fill(cr);

        //When dealing with gdkPixmap's, we need to make sure not to
        //access them from outside gtk_main().
        cairo_paint(cr_pixmap);
        gdk_threads_leave();

        currently_drawing = 0;

        return NULL;
    }

    typedef void * (*THREADFUNCPTR)(void *);

gboolean timer_exe(GtkWidget * window)
    {
        static int queuecounter = 0;
        static gboolean first_execution = TRUE;
        if (first_execution)
        {
            cst = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, WindowWidth, WindowHeight);
            cr = cairo_create(cst);
            cr_pixmap = gdk_cairo_create(pixmap);
            cairo_set_source_surface (cr_pixmap, cst, 0, 0);
            cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
            cairo_paint(cr);
            cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
            buffer1 = (int*) malloc((int)sizeof(int)*WindowHeight*WindowWidth);
            buffer2 = (int*) malloc((int)sizeof(int)*WindowHeight*WindowWidth);
            for (int i = 0; i < WindowHeight*WindowWidth; i++)
            {
                buffer1[i] = 1;
                buffer2[i] = 0;
            }
    //        cairo_paint(cr_pixmap);
        }

    //use a safe function to get the value of currently_drawing so
    //we don't run into the usual multithreading issues
        int drawing_status = g_atomic_int_get(&currently_drawing);

    //if we are not currently drawing anything, launch a thread to
    //update our pixmap
        if(drawing_status == 0){
            static pthread_t thread_info;
            int  iret;
            if(first_execution != TRUE){
                pthread_join(thread_info, NULL);
            }
            iret = pthread_create( &thread_info, NULL, &do_draw, NULL);

            gtk_widget_queue_draw_area(window, 0, 0, WindowWidth, WindowHeight);
        }
        else
        {
//            cout << "skip" << endl;
        }


    //    //tell our window it is time to draw our animation.
    //    gdk_drawable_get_size(pixmap, &width, &height);

        first_execution = FALSE;
        return TRUE;
    }


    gboolean calculate()
    {
    }


    gboolean on_window_expose_event(GtkWidget * da, GdkEventExpose * event, gpointer user_data){
        gdk_draw_drawable(da->window,
            da->style->fg_gc[GTK_WIDGET_STATE(da)], pixmap,
            // Only copy the area that was exposed.
            event->area.x, event->area.y,
            event->area.x, event->area.y,
            event->area.width, event->area.height);
        return TRUE;
    }

    //wird aufgerufen, wenn eine taste gedrueckt wurde
    gboolean keypress( GtkWidget *wi, GdkEventKey *event, gpointer func_data){
        std::cout << "key value:" << event->keyval << std::endl;
        bool reset = 0;
        switch (event->keyval){
    //                case 65362:     H = H+dH;    reset = 1;	break;                                          //UP
    //                case 65364:     H = H-dH;    reset = 1;	break;                                          //DOWN
    //                case 65361:     dH *= 10;    break;                                          //LEFT
    //                case 65363:     dH /= 10;    break;                                          //RIGHT
    //                case 65451:     T = T+dT;    updateT();	break;                          // +
    //                case 65453:     T = T-dT;    if (T<0.0) T = 0.0;	updateT();	break;  // -
                        case 65451:     magnitude = magnitude+1; break;                          // +
                        case 65453:     magnitude = (magnitude>1)?magnitude-1:magnitude;	break;  // -
    //                case 65450:     dT *= 10;    break;                                          // *
    //                case 65455:     dT /= 10;    break;                                          // /
    //                case 65456:     H = 0;          reset = 1;	break;                                          // 0
    //                case 114:       init_ising();   reset = 1;	break;                          //r
    //                case 110:       set_lattice();  reset = 1;	break;                          //n
    //                case 97:        H += dH;     reset = 1;	break;                          //a
    //                case 115:       H -= dH;     reset = 1;	break;                          //s
    //                case 108:       dH /= 10;    break;                                          //l
    //                case 107:       dH *= 10;    break;                                          //k
                        case 113:       exit(1);     break;                           //q
    //                case 113:       T += dT;     updateT();     break;                           //q
    //                case 119:       T -= dT;     if (T<0.0) T=0.0;	updateT();	break;  //w
    //                case 105:       dT *= 10;    break;                                          //i
    //                case 111:       dT /= 10;    break;                                          //o
    //                case 101:       speed *= 2;     break;                                          //e
    //                case 100:       speed /= 2;     break;                                          //d
    //                case 109:       showmeanvalues= !showmeanvalues;	break;                  //m
    //        case 99:        resetMeanValues();	break;                                  //c
        }
    ////      printf ("%i \n", event->keyval);//ich benutze diese zeile um die keyvals fuer neue tastenbefehle zu bestimmen
    //    update_strings();
    //    if (reset) resetCounter();
            return TRUE;
    }
}



View::View()
{

}

View::~View()
{
//    delete pointsCache[0];
//    delete pointsCache[1];
}

void View::SetWindowHeight(int height)
{
    WindowHeight = height;
}

void View::SetWindowWidth(int width)
{
    WindowWidth = width;
}

void View::SetMagnitude(int magn)
{
    Magnitude = magn;
}

void View::InitGtk(int argc, char *argv[])
{
    if (!g_thread_supported ())
    {
        g_thread_init(NULL);
    }
    gdk_threads_init();
    gdk_threads_enter();
    gtk_init(&argc, &argv);
    GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(window), "expose_event", G_CALLBACK(on_window_expose_event), NULL);
    g_signal_connect(G_OBJECT(window), "key_press_event", G_CALLBACK(keypress), NULL);
    gtk_window_set_default_size  ((GtkWindow*) window,  WindowHeight, WindowWidth);
    //this must be done before we define our pixmap so that it can reference
    //the colour depth and such
    std::cout << "showing window" << std::endl;
    gtk_widget_show_all(window);

    pixmap = gdk_pixmap_new(window->window,WindowWidth,WindowHeight,-1);

    gtk_widget_set_app_paintable(window, TRUE);
    gtk_widget_set_double_buffered(window, FALSE);

    (void)g_timeout_add(10, (GSourceFunc) timer_exe, window);
//    (void)g_timeout_add(60, (GSourceFunc) calculate, window);

    gtk_main();
    gdk_threads_leave();
}



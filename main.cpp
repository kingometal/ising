#include "view.h"
#include "model.h"


int main (int argc, char *argv[]){
    Model model;
    View view;

    srand(time(0));
    if (argc == 2)
    {
        model.SetGridHeight(atoi(argv[1]));
        model.SetGridWidth(atoi(argv[1]));
        view.SetWindowHeight(atoi(argv[1]));
        view.SetWindowWidth(atoi(argv[1]));
    }
    else if (argc == 3)
    {
        view.SetMagnitude(atoi(argv[2]));

        model.SetGridHeight(atoi(argv[1]));
        model.SetGridWidth(atoi(argv[1]));
        view.SetWindowHeight(atoi(argv[1]));
        view.SetWindowWidth(atoi(argv[1]));
    }
    else
    {
        model.SetGridHeight(100);
        model.SetGridWidth(100);
        view.SetWindowHeight(100);
        view.SetWindowWidth(100);
    }
    model.InitModel();

    //we need to initialize all these functions so that gtk knows
    //to be thread-aware
    view.InitGtk(argc, argv);




//    //set up our pixmap so it is ready for drawing

//    //because we will be painting our pixmap manually during expose events
//    //we can turn off gtk's automatic painting and double buffering routines.
//    gtk_widget_set_app_paintable(window, TRUE);
//    gtk_widget_set_double_buffered(window, FALSE);

//    (void)g_timeout_add(30, (GSourceFunc)timer_exe, window);

//    gtk_main();
//    gdk_threads_leave();

    return 0;
}



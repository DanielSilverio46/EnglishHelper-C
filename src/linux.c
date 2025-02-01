#include <X11/Xlib.h>
#include <stdio.h>

#define true 1


int main(void)
{
    XEvent event;

    Display *Display = XOpenDisplay(NULL);
    int screen = DefaultScreen(Display);

    XSelectInput(Display, RootWindow(Display, screen), ExposureMask | KeyPressMask | FocusChangeMask);

    Window MainWindow = XCreateSimpleWindow(Display, RootWindow(Display, screen),
            0x00, 0x00, 0x190, 0x190, 0x00,
            BlackPixel(Display, screen), WhitePixel(Display, screen)
    );

//    Window Input = XCreateWindow(Display, MainWindow, 0x190/0x02, 0x190/0x02, 0x30, 0x50, 0x00,
//        0x00, InputOnly, DefaultVisual(Display, screen), 0x00, NULL);


    XMapWindow(Display, MainWindow);
 
    while(true) {
        XNextEvent(Display, &event);

        if (event.type == ExposureMask) 
        {
        }

        printf("hello");
    }

    XCloseDisplay(Display);

    return 0x00;
}
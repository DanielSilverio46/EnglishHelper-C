#include <X11/Xlib.h>

#define true 1

int main(void)
{
    XEvent event;

    Display *Display = XOpenDisplay(NULL);
    int screen = DefaultScreen(Display);

    Window MainWindow = XCreateSimpleWindow(Display, RootWindow(Display, screen),
            0x00, 0x00, 0x190, 0x190, 0x00,
            BlackPixel(Display, screen), WhitePixel(Display, screen)
    );

    XSelectInput(Display, MainWindow, ExposureMask | KeyPressMask);

    XMapWindow(Display, MainWindow);


    while(true)
    {
        XNextEvent(Display, &event);
    };

    XCloseDisplay(Display);

    return 0x00;
}
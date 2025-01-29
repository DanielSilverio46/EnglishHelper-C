#include <X11/Xlib.h>

int main(void)
{
    Display *MainDisplay = XOpenDisplay(NULL);

    XCloseDisplay(MainDisplay);

    return 0x00;
}
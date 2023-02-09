#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>

int main()
{
    Display *display = XOpenDisplay(NULL);
    int screen = DefaultScreen(display);
    Window root = RootWindow(display, screen);
    XEvent event;
    XWindowAttributes attrs;
    printf("code");
    XSelectInput(display, root, ButtonPressMask | ButtonReleaseMask | PointerMotionMask);

    while (1) {
        XNextEvent(display, &event);
        switch (event.type) {
            case ButtonPress:
                if (event.xbutton.y == 0)
                    printf("Mouse left button pressed at y = %d\n", event.xbutton.y);
                break;
            case ButtonRelease:
                if (event.xbutton.subwindow != None)
                    printf("Mouse left button released on file\n");
                break;
            case MotionNotify:
                XGetWindowAttributes(display, root, &attrs);
                if (event.xmotion.y == 0)
                    printf("Mouse moved to y = %d\n", event.xmotion.y);
                break;
        }
    }

    XCloseDisplay(display);
    return 0;
}

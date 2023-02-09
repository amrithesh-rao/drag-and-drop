#include <X11/Xlib.h>
#include <stdio.h>

int main()
{
    Display *display = XOpenDisplay(NULL);
    Window root = DefaultRootWindow(display);
    XEvent event;

    XGrabPointer(display, root, False,
                ButtonPressMask, GrabModeAsync,
                GrabModeAsync, None, None, CurrentTime);

    while (1) {
        XNextEvent(display, &event);
        if (event.type == ButtonPress) {
            // char *file = XGetAtomName(display, event.xbutton.subwindow);
            // printf("File path: %s\n", file);
            // XFree(file);
            // break;
        }
    }

    XUngrabPointer(display, CurrentTime);
    XCloseDisplay(display);
    return 0;
}

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>

int main()
{
    Display *display = XOpenDisplay(NULL);
    Window root = DefaultRootWindow(display);
    XWindowAttributes attributes;
    XGetWindowAttributes(display, root, &attributes);
    int screen_width = attributes.width;
    int screen_height = attributes.height;

    // get mouse position
    Window root_return, child_return;
    int root_x, root_y, win_x, win_y;
    unsigned int mask_return;

    XQueryPointer(display, root, &root_return, &child_return, &root_x, &root_y, &win_x, &win_y, &mask_return);
    int rightmost_coordinate = screen_width - root_x;
    printf("Rightmost coordinate of mouse: %d\n", rightmost_coordinate);

    XCloseDisplay(display);

    return 0;
}

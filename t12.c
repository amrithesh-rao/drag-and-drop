#include <X11/Xlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    Display *display = XOpenDisplay(NULL);
    Window root_window = XDefaultRootWindow(display);

    XEvent event;
    int is_dragging = 0;
    int start_x, start_y;

    while (1) {
        XQueryPointer(display, root_window, &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
        if (event.xbutton.state & Button1Mask) {
            if (!is_dragging) {
                is_dragging = 1;
                start_x = event.xbutton.x;
                start_y = event.xbutton.y;
            }
        } else {
            if (is_dragging) {
                is_dragging = 0;
                if(event.xbutton.x == 0)
                printf("Dragged from (%d, %d) to (%d, %d)\n", start_x, start_y, event.xbutton.x, event.xbutton.y);
            }
        }
    }

    XCloseDisplay(display);
    return 0;
}

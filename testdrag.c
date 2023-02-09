#include <X11/Xlib.h>
#include <stdio.h>

int main()
{
  Display *display;
  Window root_window;
  XEvent event;

  display = XOpenDisplay(NULL);
  root_window = XDefaultRootWindow(display);
  
  XAllowEvents(display, AsyncPointer, CurrentTime);
  XGrabPointer(display, root_window, False,
               ButtonPressMask | ButtonReleaseMask,
               GrabModeAsync, GrabModeAsync, None, None, CurrentTime);

// rightmost width
  // XWindowAttributes attributes;
  // XGetWindowAttributes(display, root_window, &attributes);
  // int screen_width = attributes.width;
  // int screen_height = attributes.height;

  while (1) {
    XNextEvent(display, &event);
    switch (event.type) {
      case ButtonPress:
        if (event.xbutton.button == Button1) {
          printf("Left mouse button pressed\n");
        }
        break;
      case ButtonRelease:
        if (event.xbutton.button == Button1) {
            printf("Left mouse button released\n");
            // int x = event.xbutton.x;
            // int y = event.xbutton.y;
            // if(x == 0 || x == screen_width-1)
            // printf("Mouse coordinate: (%d, %d)\n", x, y);
        }
        break;
    }
  }

  XCloseDisplay(display);
  return 0;
}




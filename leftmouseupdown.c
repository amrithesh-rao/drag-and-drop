#include <X11/Xlib.h>
#include <stdio.h>

int main()
{
  Display *dpy;
  Window root_window;
  XEvent event;

  dpy = XOpenDisplay(NULL);
  root_window = XDefaultRootWindow(dpy);
  XAllowEvents(dpy, AsyncPointer, CurrentTime);
  XGrabPointer(dpy, root_window, False,
               ButtonPressMask | ButtonReleaseMask,
               GrabModeAsync, GrabModeAsync, None, None, CurrentTime);

  while (1) {
    XNextEvent(dpy, &event);
    switch (event.type) {
      case ButtonPress:
        if (event.xbutton.button == Button1) {
          printf("Left mouse button pressed\n");
        }
        break;
      case ButtonRelease:
        if (event.xbutton.button == Button1) {
            printf("Left mouse button released\n");
            int x = event.xbutton.x;
            int y = event.xbutton.y;
            if(x == 0)
            printf("Mouse coordinate: (%d, %d)\n", x, y);
        }
        break;
    }
  }

  XCloseDisplay(dpy);
  return 0;
}




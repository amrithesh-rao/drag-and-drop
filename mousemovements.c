#include <X11/Xlib.h>
#include <stdio.h>

int main()
{
  Display *dpy;
  Window root_window;
  XEvent event;
  int root_x, root_y;

  dpy = XOpenDisplay(NULL);
  root_window = XDefaultRootWindow(dpy);
  XAllowEvents(dpy, AsyncPointer, CurrentTime);
  XGrabPointer(dpy, root_window, False,
               ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
               GrabModeAsync, GrabModeAsync, None, None, CurrentTime);

  while (1) {
    XNextEvent(dpy, &event);
    switch (event.type) {
      case MotionNotify:
        root_x = event.xmotion.x_root;
        root_y = event.xmotion.y_root;
        printf("Mouse moved to (%d, %d)\n", root_x, root_y);
        break;
    }
  }

  XCloseDisplay(dpy);
  return 0;
}

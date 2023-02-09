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
        printf("Mouse button pressed\n");
        break;
      case ButtonRelease:
        printf("Mouse button released\n");
        break;
    }
  }

  XCloseDisplay(dpy);
  return 0;
}

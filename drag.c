#include <X11/Xlib.h>
#include <stdio.h>

int main()
{
  Display *dpy;
  Window root_window;
  XEvent event;
  int start_x, start_y, end_x, end_y;
  int is_dragging = 0;

  dpy = XOpenDisplay(NULL);
  root_window = XDefaultRootWindow(dpy);
  XAllowEvents(dpy, AsyncPointer, CurrentTime);
  XGrabPointer(dpy, root_window, False,
               ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
               GrabModeAsync, GrabModeAsync, None, None, CurrentTime);

  while (1) {
    XNextEvent(dpy, &event);
    switch (event.type) {
      case ButtonPress:
        if (event.xbutton.button == Button1) {
          start_x = event.xbutton.x;
          start_y = event.xbutton.y;
          is_dragging = 1;
        }
        break;
      case ButtonRelease:
        if (event.xbutton.button == Button1) {
          end_x = event.xbutton.x;
          end_y = event.xbutton.y;
          is_dragging = 0;
          printf("Left mouse button drag and dropped from (%d, %d) to (%d, %d)\n",
                 start_x, start_y, end_x, end_y);
        }
        break;
      case MotionNotify:
        if (is_dragging) {
          end_x = event.xmotion.x;
          end_y = event.xmotion.y;
        }
        break;
    }
  }

  XCloseDisplay(dpy);
  return 0;
}

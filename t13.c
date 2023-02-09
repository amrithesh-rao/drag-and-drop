#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <X11/Xatom.h>

int main(int argc, char** argv) {
  Display* display = XOpenDisplay(NULL);
  Window root = DefaultRootWindow(display);
  
  Atom selection = XInternAtom(display, "PRIMARY", False);
  Atom target = XInternAtom(display, "text/plain", False);
  XConvertSelection(display, selection, target, XA_PRIMARY, root, CurrentTime);

  XSync(display, False);
  XEvent event;
  while (1) {
     printf("start Received X event! Type: %d\n", event.type);
    int result = XNextEvent(display, &event);
    if (result == 0) {
      printf("Received X event! Type: %d\n", event.type);
      if (event.type == SelectionNotify) {
        break;
      }
    } else {
      printf("Failed to receive X event\n");
      break;
    }
  }

  XCloseDisplay(display);
  return 0;
}

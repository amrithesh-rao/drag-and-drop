#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <X11/Xatom.h>

int main(int argc, char** argv) {
    printf("sdfsdf");
    fflush(stdout);
  Display* display = XOpenDisplay(NULL);
  Window root = DefaultRootWindow(display);
      printf("sdfsdf");
    fflush(stdout);
  Atom selection = XInternAtom(display, "PRIMARY", False);
  Atom target = XInternAtom(display, "UTF8_STRING", False);
  XConvertSelection(display, selection, target, XA_PRIMARY, root, CurrentTime);
    int x = 0;
  XEvent event;
      printf("sdfsdf");
    fflush(stdout);
  while (x<20) {
    x++;
    printf("%d",x);
    fflush(stdout);
    printf("sdfsdfddd");
    fflush(stdout);
    XNextEvent(display, &event);
    fflush(stdout);
    printf("sdfsdfsfsdfsdf");
    fflush(stdout);
    if (event.type == SelectionNotify) {
      if (event.xselection.property == None) {
        fflush(stdout);
        printf("Selection request failed\n");
      } else {
        Atom type;
        int format;
        unsigned long n_items, bytes_after;
        unsigned char* data;
        int result = XGetWindowProperty(display, root, XA_PRIMARY, 0, LONG_MAX,
                                        False, target, &type, &format, &n_items,
                                        &bytes_after, &data);
        if (result == Success) {
            fflush(stdout);
          printf("Selected files: \n%s\n", data);
          XFree(data);
        } else {
            fflush(stdout);
          printf("Failed to get window property\n");
        }
        break;
      }
      
    }
    sleep(1);
  }
  XCloseDisplay(display);
  return 0;
}

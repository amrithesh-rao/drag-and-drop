#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <string.h>

int main()
{
  Display *display = XOpenDisplay(NULL);
  int screen = DefaultScreen(display);
  Window root = RootWindow(display, screen);

  // Get the mouse position
  Window child_window;
  int x, y;
  unsigned int mask;
  XQueryPointer(display, root, &child_window, &child_window, &x, &y, &x, &y, &mask);

  // Get the window attributes
  XWindowAttributes attributes;
  XGetWindowAttributes(display, child_window, &attributes);

  // Get the file path property
  Atom type;
  int format;
  unsigned long nitems;
  unsigned long bytes_after;
  unsigned char *data = NULL;
  Atom file_path = XInternAtom(display, "_NET_WM_NAME", False);
  XGetWindowProperty(display, child_window, file_path, 0, 1024, False,
    AnyPropertyType, &type, &format, &nitems, &bytes_after, &data);
  if (type == None)
  {
    fprintf(stderr, "File path not found\n");
    return -1;
  }

  // Print the file path
  printf("File path: %s\n", data);

  XCloseDisplay(display);
  return 0;
}

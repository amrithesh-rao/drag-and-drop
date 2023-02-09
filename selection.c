// #include <X11/Xlib.h>
// #include <X11/Xatom.h>
// #include <X11/Xutil.h>
// #include <stdio.h>
// #include <stdlib.h>

// int main(void)
// {
//     Display *dpy;
//     Window win;
//     XEvent ev;
//     Atom sel;

//     dpy = XOpenDisplay(NULL);
//     if (!dpy) {
//         fprintf(stderr, "Failed to open display\n");
//         exit(1);
//     }

//      win = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, 1, 1, 0, 0, 0);
//      XSelectInput(dpy, win, ButtonPressMask);

//      sel = XInternAtom(dpy, "PRIMARY", False);
//      XConvertSelection(dpy, sel, XA_STRING, XA_STRING, win, CurrentTime);

//     while (1) {
//         XNextEvent(dpy, &ev);
//     printf("gdfgdfg\n");
//         // if (ev.type == SelectionNotify) {
//         //     // Atom actual_type;
//         //     // int actual_format;
//         //     // unsigned long nitems;
//         //     // unsigned long bytes_after;
//         //     // unsigned char *data;
//         //     // XGetWindowProperty(dpy, win, XA_STRING, 0, ~0, False, AnyPropertyType, &actual_type, &actual_format, &nitems, &bytes_after, &data);
//         //     // printf("Selection: %s\n", (char *)data);
//         //     // XFree(data);
//         //     // exit(0);
//         // }
//      switch (ev.type) {
//       case ButtonPress:
//           if(ev.xbutton.button == Button1){
//             printf("sdfsf");
//         }
//         break;
//      }
//     }
//     return 0;
// }
#include <X11/Xlib.h>
#include <stdio.h>

int main() {
  Display *dpy = XOpenDisplay(NULL);
  Window root = DefaultRootWindow(dpy);

  XSelectInput(dpy, root, ButtonPressMask);

  XEvent event;
  while (1) {
    XNextEvent(dpy, &event);
    if (event.type == ButtonPress) {
      printf("Button press detected!\n");
    }
  }

  XCloseDisplay(dpy);
  return 0;
}

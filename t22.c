#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xmu/StdCmap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    Display *display = XOpenDisplay(NULL);
    Window root = DefaultRootWindow(display);

    Atom selection = XInternAtom(display, "XdndSelection", False);
    Window selection_owner = XGetSelectionOwner(display, selection);

    if (selection_owner != None) {
        Atom type;
        int format;
        unsigned long nitems;
        unsigned long after;
        unsigned char *data;

        int result = XGetWindowProperty(display, root, selection, 0, 0xFFFFFFFF, False,
                                        AnyPropertyType, &type, &format, &nitems, &after, &data);

        if (result == Success) {
            int count;
            char **list = Xutf8TextPropertyToTextList(display, &data, &count);


            for (int i = 0; i < count; i++) {
                char *url = list[i];

                if (strstr(url, "file://") == url) {
                    char *file = url + 7;
                    printf("File: %s\n", file);
                }
            }

            XFree(list);
            XFree(data);
        }
    }

    XCloseDisplay(display);
    return 0;
}

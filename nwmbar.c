#include <X11/Xlib.h>
#include <assert.h>
#include <string.h>


int main() {
  Display *dpy = XOpenDisplay(NULL);
  assert(dpy);

  int blackColor = BlackPixel(dpy, DefaultScreen(dpy));
  int whiteColor = WhitePixel(dpy, DefaultScreen(dpy));

  Window w = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0,
         200, 100, 0, blackColor, blackColor);

  XSelectInput(dpy, w, ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask);

  XMapWindow(dpy, w);
  GC gc = XCreateGC(dpy, w, 0, NULL);
  XSetForeground(dpy, gc, whiteColor);

  XFontStruct * font_info;

  /*  Load a font called "9x15"  */

  if ( (font_info = XLoadQueryFont(dpy, "9x15")) == NULL ) {
    return 1;
  }
  XSetFont(dpy, gc, font_info->fid);

  static int font_height;
  static int length;
  static char * message = "yay it works";

  length = XTextWidth(font_info, message, strlen(message));
  font_height = font_info->ascent + font_info->descent;

  while(1) {
    XEvent e;
    XNextEvent(dpy, &e);

    switch(e.type) {
      case Expose:
        if ( e.xexpose.count != 0 )
          break;

        XDrawString(dpy, w, gc, 0, font_height, message, strlen(message));
        break;
      case ButtonPress:
      case KeyPress:
        /*  Clean up and exit  */
        XUnloadFont(dpy, font_info->fid);
        XFreeGC(dpy, gc);
        XCloseDisplay(dpy);

        return 0;
    }
  }

  return 0;
}

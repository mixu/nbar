#include <X11/Xlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

static void nbar_exit();

typedef struct {
  Display *dpy;
  int screen;
  GC gc;
  Window win;
  // drawing
  int font_height;
  XFontStruct * font_info;
} NBarData;

static NBarData nbar;

int nbar_init() {
  nbar.dpy = XOpenDisplay(NULL);
  assert(nbar.dpy);

  int blackColor = BlackPixel(nbar.dpy, DefaultScreen(nbar.dpy));
  int whiteColor = WhitePixel(nbar.dpy, DefaultScreen(nbar.dpy));

  nbar.win = XCreateSimpleWindow(nbar.dpy, DefaultRootWindow(nbar.dpy), 0, 0,
         200, 100, 0, blackColor, blackColor);

  XSelectInput(nbar.dpy, nbar.win, ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask);

  XMapWindow(nbar.dpy, nbar.win);
  nbar.gc = XCreateGC(nbar.dpy, nbar.win, 0, NULL);
  XSetForeground(nbar.dpy, nbar.gc, whiteColor);


  /*  Load a font called "9x15"  */

  if ( (nbar.font_info = XLoadQueryFont(nbar.dpy, "9x15")) == NULL ) {
    return 1;
  }
  XSetFont(nbar.dpy, nbar.gc, nbar.font_info->fid);

  static int length;
  static char * message = "yay it works";

  length = XTextWidth(nbar.font_info, message, strlen(message));
  nbar.font_height = nbar.font_info->ascent + nbar.font_info->descent;

  // return the connection number so the node binding can use it with libev.
  return XConnectionNumber(nbar.dpy);
}

void nbar_loop() {
  XEvent e;
  static char * message = "yay it works";

  while(XPending(nbar.dpy)) {
    XNextEvent(nbar.dpy, &e);
    switch(e.type) {
      case Expose:
        if ( e.xexpose.count != 0 )
          break;

        XDrawString(nbar.dpy, nbar.win, nbar.gc, 0, nbar.font_height, message, strlen(message));
        break;
      case ButtonPress:
      case KeyPress:
        fprintf( stdout, "keypress\n");
        break;
    }
  }
}

void nbar_exit() {
  XUnloadFont(nbar.dpy, nbar.font_info->fid);
  XFreeGC(nbar.dpy, nbar.gc);
  /*
  XCloseDisplay(nbar.dpy);
  */
}

int main() {
  nbar_init();

  while(1) {
    nbar_loop();
  }

  return 0;
}

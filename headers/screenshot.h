#include <iostream>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <X11/keysymdef.h>
#include <png.h>

static void save_png(const char *filename, XImage* img);
int capture_screenshot();
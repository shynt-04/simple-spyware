#include <iostream>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <X11/keysymdef.h>
#include <png.h>

#include "../headers/screenshot.h"

using namespace std;

// https://www.codemadness.nl/downloads/xscreenshot.c
static void save_png(const char *filename, XImage* img) {
    FILE *fp = fopen(filename, "wb"); // use FILE* struct for png function
    if (!fp) {
        cerr << "ERROR: Unable to open file for writing" << "\n";
        return;
    }
 
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        cerr << "ERROR: Unable to create PNG write struct" << "\n";
        fclose(fp);
        return;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        cerr << "ERROR: Unable to create PNG info struct" << "\n";
        png_destroy_write_struct(&png, nullptr);
        fclose(fp);
        return;
    }
 
    if (setjmp(png_jmpbuf(png))) {
        cerr << "ERROR: Error during PNG creation" << "\n";
        png_destroy_write_struct(&png, &info);
        fclose(fp);
        return;
    }

    png_init_io(png, fp);
 
    png_set_IHDR(
        png,
        info,
        img->width, img->height,
        8,
        PNG_COLOR_TYPE_RGB,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );

    png_write_info(png, info);
 
    png_bytep row = (png_bytep) malloc(3 * img->width * sizeof(png_byte));
    for (int y = 0; y < img->height; ++ y) {
        for (int x = 0; x < img->width; ++ x) {
            long pixel = XGetPixel(img, x, y);
            row[x*3 + 0] = (pixel & img->red_mask) >> 16; // R
            row[x*3 + 1] = (pixel & img->green_mask) >> 8; // B
            row[x*3 + 2] = (pixel & img->blue_mask); // G
        }
        png_write_row(png, row);
    }

    png_write_end(png, nullptr);
    png_destroy_write_struct(&png, &info);
    fclose(fp);
    free(row);
}

// https://github.com/resurrecting-open-source-projects/scrot/blob/master/src/scrot.c
int capture_screenshot() {
    // system("scrot -o screenshot.png");
    // implementation of scrot -o
    Display* display = XOpenDisplay(nullptr);
    if (!display) {
        cerr << "ERROR: Unable to open X Display" << "\n";
        return EXIT_FAILURE;
    }
    int screen = DefaultScreen(display);
    Window root = RootWindow(display, screen);

    XWindowAttributes gwa; 
    XGetWindowAttributes(display, root, &gwa); // get current window attribute

    XImage* img = XGetImage(display, root, 0, 0, gwa.width, gwa.height, AllPlanes, ZPixmap);
    if (!img) {
        cerr << "ERROR: Unable to get image" << "\n";
        XCloseDisplay(display);
        return EXIT_FAILURE;
    }
    save_png("screenshot.png", img);
    XDestroyImage(img);
    XCloseDisplay(display);

    return EXIT_SUCCESS;
}
#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED


#include "../main.h"



typedef struct _window{
    uint16_t width;
    uint16_t height;
    Color backgroundColor;
    char* title;
} window;


void create_window();






#endif
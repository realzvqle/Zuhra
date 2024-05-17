#ifndef BUTTONS_H_INCLUDED
#define BUTTONS_H_INCLUDED





#include "drawtext.h"

typedef enum ButtonState{
    BUTTON_NOT_INTERACTED,
    BUTTON_HOVER,
    BUTTON_CLICK_LEFT,
    BUTTON_CLICK_RIGHT,
    BUTTON_DOWN_LEFT,
    BUTTON_DOWN_RIGHT
} ButtonState;



ButtonState draw_button(char* text, int x, int y, int sizeX, int sizeY, Color baseColor, Color textColor, Color hoverColor, int textSize);
ButtonState draw_button_ex(char* text, int x, int y, int sizeX, int sizeY, Font font, Color baseColor, Color textColor, Color hoverColor, int textSize);
int lua_draw_button(lua_State *L);

#endif
#ifndef SHAPES_H_INCLUDED
#define SHAPES_H_INCLUDED




#include "../../main.h"

void draw_rect(int posX, int posY, int width, int height, Color color);
int lua_draw_rect(lua_State* L);

void draw_circle(int centerX, int centerY, float radius, Color color);
int lua_draw_circle(lua_State* L);


#endif
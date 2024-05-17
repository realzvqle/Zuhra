#ifndef DRAWTEXT_H_INCLUDED
#define DRAWTEXT_H_INCLUDED




#include "../../main.h"



void draw_text(char* text, int x, int y, int size, Color color);
int lua_draw_text(lua_State* L);
void draw_text_ex(char* text, int x, int y, Font font, int size, Color color);
int lua_draw_circle(lua_State* L);
#endif
#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED



#include "../main.h"

//int start_renderer(state* state);
int lua_create_color(lua_State* L);
Color create_color(int r, int g, int b, int a);


int lua_change_background(lua_State* L);
void change_background(Color color);
#endif
#include "shapes.h"





void draw_rect(int posX, int posY, int width, int height, Color color){
    DrawRectangle(posX, posY, width, height, color);
}

int lua_draw_rect(lua_State* L){
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2) + 90;
    int width = luaL_checkinteger(L, 3);
    int height = luaL_checkinteger(L, 4);
    Color color = GetColor(luaL_checkinteger(L, 5));
    draw_rect(x, y, width, height, color);
    lua_pushnil(L);
    return 0;
}


void draw_circle(int centerX, int centerY, float radius, Color color){
    DrawCircle(centerX, centerY, radius, color);
}

int lua_draw_circle(lua_State* L){
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2) + 90;
    int radius = luaL_checkinteger(L, 3);
    Color color = GetColor(luaL_checkinteger(L, 4));
    draw_circle(x, y, radius, color);
    lua_pushnil(L);
    return 0;
}
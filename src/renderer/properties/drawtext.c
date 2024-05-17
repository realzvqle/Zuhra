#include "drawtext.h"


extern state* stte;



void draw_text(char* text, int x, int y, int size, Color color) {
	DrawTextEx(stte->currentFont, text, (Vector2) { x, y }, size, 4, color);
}

int lua_draw_text(lua_State* L){
    const char* text = luaL_checkstring(L, 1);
    int x = luaL_checkinteger(L, 2);
    int y = luaL_checkinteger(L, 3) + 90;
    int size = luaL_checkinteger(L, 4);
    Color color = GetColor(luaL_checkinteger(L, 5));
    draw_text((char*)text, x, y, size, color);
    lua_pushnil(L);
    return 0;
}

void draw_text_ex(char* text, int x, int y, Font font, int size, Color color) {
	DrawTextEx(font, text, (Vector2) { x, y }, size, 4, color);
}
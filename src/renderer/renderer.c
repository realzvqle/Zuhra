#include "renderer.h"




// int start_renderer(state* state){



//     return 0;
// }


extern state* stte;


Color create_color(int r, int g, int b, int a){
    Color clr = {r,g,b,a};
    return clr;
}


static unsigned int color_to_hex(Color color) {
    // Combine the color components into a single hex value
    unsigned int hexValue = (color.r << 24) | (color.g << 16) | (color.b << 8) | color.a;
    return hexValue;
}


int lua_create_color(lua_State* L){
    int r = luaL_checkinteger(L, 1);
    int g = luaL_checkinteger(L, 2);
    int b = luaL_checkinteger(L, 3);
    int a = luaL_checkinteger(L, 4);
    Color color = create_color(r,g,b,a);
    lua_pushinteger(L, color_to_hex(color));
    return 1;
}


void change_background(Color color){
    stte->backgroundColor = color;
}

int lua_change_background(lua_State* L){
    Color color = GetColor(luaL_checkinteger(L, 1));
    change_background(color);
    lua_pushnil(L);
    return 1;
}
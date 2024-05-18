
#include "renderer.h"
#include "topbar/topbar.h"
#include "../networking/request.h"


thrd_t thread;

int start_renderer(state* state, lua_State* L, requestData* data){
    if(!data->init){
        //data->result = NULL;
        data->status = -1;
         if (thrd_create(&thread, fetch_lua_script, (void*)data) != thrd_success) {
            fail("Failed to create fetch thread\n");
            return 1;
         }
        data->shouldLoad = true;
        data->init = TRUE;
    }
    draw_topbar();
    if (data == NULL) {
        fail("Failed to allocate memory for requestData\n");
        return 0;
    } 
       
    if (thrd_join(thread, NULL) == thrd_success) {
        if (data->status == 0) {
            if (data->result != NULL) {
                int result = luaL_loadstring(L, data->result);
                int presult = lua_pcall(L, 0, 0, 0);                     
                if (result != LUA_OK || presult != LUA_OK) {
                    ClearBackground(BLACK);
                    fail("Failed Compiling Lua File\n");
                    lua_pop(L, 1);
                }         
                else{
                    ClearBackground(state->backgroundColor);
                    //state->backgroundColor = BLACK;
                    state->reload = false;
                }
                //free(data->result);  
                //data->result = NULL;
                }
                } else {
                    ClearBackground(BLACK);
                    state->backgroundColor = BLACK;
                    fail("Failed to fetch Lua script\n");
                }
                data->status = -1;
                thrd_create(&thread, fetch_lua_script, (void*)data);
    }
    else{
        fail("Failed Making Trhead\n");
    }          
    info("%s\n", data->url);
    return 0;
}


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
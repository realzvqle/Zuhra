#include "window.h"
#include "../renderer/properties/buttons.h"
#include "../renderer/properties/drawtext.h"
#include "../renderer/properties/shapes.h"
#include "../renderer/renderer.h"
#include "../renderer/topbar/topbar.h"
#include "../networking/request.h"

window* win;
state* stte;

static window* setup_window(){
    window* win = (window*)malloc(sizeof(window));
    if(!win){
        fail("Failed Allocating Memory At WINDOW-CREATION level\n");
        return NULL;
    }
    win->width = 1600;
    win->height = 900;
    win->title = "Zuhra Broswer";

    return win;
}

void create_window() {
    naettInit(NULL);
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    requestData* data = (requestData*)malloc(sizeof(requestData));
    if (data == NULL) {
        fail("Failed to allocate memory for requestData\n");
        return;
    }
    data->url = NULL;
    data->result = NULL;
    data->status = -1;

    // Register Lua functions
    lua_register(L, "draw_button", lua_draw_button);
    lua_register(L, "draw_text", lua_draw_text);
    lua_register(L, "draw_rect", lua_draw_rect);
    lua_register(L, "draw_circle", lua_draw_circle);
    lua_register(L, "create_color", lua_create_color);
    lua_register(L, "change_background", lua_change_background);

    stte = (state*)malloc(sizeof(state));
    if (stte == NULL) {
        fail("Failed to allocate memory for state\n");
        return;
    }

    win = setup_window();
    if (!win) {
        fail("Failed Setting Up Window\n");
        return;
    }
    pass("Successfully Setup Window\n");

    SetTraceLogLevel(LOG_FATAL);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(win->width, win->height, win->title);
    pass("Created Window\n");

    stte->currentFont = LoadFontEx("resources/Roboto-Bold.ttf", 400, NULL, 0);
    stte->backgroundColor = WHITE;
    if (stte->currentFont.texture.id == 0) {
        fail("Failed Loading Font\n");
        return;
    }
    pass("Loaded Font\n");

    stte->currentFile = "realzvqle.github.io/test/IDK.LUA";

    char buffer[998];
    sprintf(buffer, "https://%s", stte->currentFile);
    data->url = strdup(buffer);
    info("%s\n", data->url);
    thrd_t thread;
    if (thrd_create(&thread, fetch_lua_script, (void*)data) != thrd_success) {
        fail("Failed to create fetch thread\n");
        return;
    }

    while (!WindowShouldClose()) {
        char buffer[998];
        sprintf(buffer, "https://%s", stte->currentFile);
        data->url = strdup(buffer);
        ClearBackground(BLACK);
        info("FPS is currently %d\n[!] Window Size is (x=%d, y=%d)\n", GetFPS(), GetScreenWidth(), GetScreenHeight());
        BeginDrawing();
        draw_topbar();

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
                        ClearBackground(stte->backgroundColor);
                        stte->backgroundColor = BLACK;

                    }
                    free(data->result);  
                    data->result = NULL;
                }
            } else {
                ClearBackground(BLACK);
                stte->backgroundColor = BLACK;
                fail("Failed to fetch Lua script\n");
            }
            data->status = -1;
            thrd_create(&thread, fetch_lua_script, (void*)data);
        }

        EndDrawing();
    }

    pass("Exited Window\n");
    CloseWindow();
    UnloadFont(stte->currentFont);
    free(stte);
    free(win);
    free(data->url);
    free(data);
    lua_close(L);
}

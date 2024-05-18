#include "window.h"
#include "../renderer/properties/buttons.h"
#include "../renderer/properties/drawtext.h"
#include "../renderer/properties/shapes.h"
#include "../renderer/renderer.h"
#include "../networking/request.h"

window* win;
state* stte;
requestData* data;
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

    stte->currentFile = "realzvqle.github.io/test/SCRIPT.LUA";

    data = (requestData*)malloc(sizeof(requestData));
    data->init = false;
    thrd_t thread;
    if (thrd_create(&thread, fetch_lua_script, (void*)data) != thrd_success) {
        fail("Failed to create fetch thread\n");
        return;
    }
    stte->reload = true;
    while (!WindowShouldClose()) {
        sprintf(stte->buffer, "https://%s", stte->currentFile);
        data->url = strdup(stte->buffer);
        info("FPS is currently %d\n[!] Window Size is (x=%d, y=%d)\n", GetFPS(), GetScreenWidth(), GetScreenHeight());
        BeginDrawing();
        start_renderer(stte, L, data);

       // ClearBackground(BLACK);
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

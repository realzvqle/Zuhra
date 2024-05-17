#include "topbar.h"
#include "../properties/input.h"


extern state* stte;



void draw_topbar(){
    static bool isActive = false;
    draw_text_box((Rectangle){0, 0 + 90, GetScreenWidth(), 90}, stte->currentFile, 990, &isActive, WHITE);
}
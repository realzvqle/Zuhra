#include "topbar.h"
#include "../properties/input.h"
#include "../properties/buttons.h"
#include "../../networking/request.h"

extern state* stte;
extern requestData* data;


void draw_topbar(){
    static bool isActive = false;
    Rectangle rect = {0, 0 + 90, GetScreenWidth(), 60};
    draw_text_box(rect, stte->currentFile, 990, &isActive, BLACK);
    ButtonState button = draw_button("start", rect.x, rect.y-30, GetScreenWidth(), 30, WHITE, BLACK, GRAY, NULL);

    if(button == BUTTON_CLICK_LEFT){
        data->init = FALSE;
        data->shouldLoad = FALSE;
        ClearBackground(WHITE);
        stte->backgroundColor = WHITE;
    }
}
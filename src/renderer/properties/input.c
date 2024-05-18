#include "input.h"
#include "drawtext.h"
extern state* stte;


void draw_text_box(Rectangle box, char *text, int maxLength, bool *active, Color textColor) {
    box.y = box.y - 90;
    DrawRectangle(box.x, box.y, box.width, box.height, *active ? WHITE : GRAY);
    DrawRectangleLines(box.x + 1, box.y + 1, box.width + 1, box.height + 1, *active ? BLACK : DARKGRAY);

    draw_text(text, box.x + 5, box.y + 8, 20, textColor);
    if (CheckCollisionPointRec(GetMousePosition(), box) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        *active = true;
    } else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        *active = false;
    }
    if (*active) {
        int key = GetKeyPressed();
        bool shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
        while (key > 0) {
            if ((key >= 32 && key <= 125) && (strlen(text) < (maxLength - 1))) {
                int len = strlen(text);
                if (shift && isalpha(key)) {
                    text[len] = toupper((char)key);
                } else {
                    text[len] = (char)key;
                }
                text[len + 1] = '\0';
            }

            key = GetKeyPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE)) {
            int len = strlen(text);
            if (len > 0) {
                text[len - 1] = '\0';
            }
        }
        int textWidth = MeasureText(text, 20);
        if (textWidth < box.width - 10) {
            int cursorX = box.x + 5 + textWidth;
            int cursorY = box.y + 8;
            if ((GetTime() * 2.0f) - (int)(GetTime() * 2.0f) > 0.5f) {
                draw_text("    _", cursorX, cursorY, 20, BLACK);
            }
        }
    }
}
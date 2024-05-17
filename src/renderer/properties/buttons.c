#include "buttons.h"


extern state* stte;


ButtonState draw_button(char* text, int x, int y, int sizeX, int sizeY, Color baseColor, Color textColor, Color hoverColor, int textSize) {
    if (!textSize) {
        textSize = sizeY / 2;
    }
    bool isMouseOver = CheckCollisionPointRec(GetMousePosition(), (Rectangle) { x, y, sizeX, sizeY });
    Color buttonColor = isMouseOver ? hoverColor : baseColor;
    DrawRectangle(x, y, sizeX, sizeY, buttonColor);
    int textWidth = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        textWidth += MeasureText(&text[i], textSize);
    }
    int textX = x + (sizeX - MeasureTextEx(stte->currentFont, text, textSize, 4).x) / 2;
    int textY = y + (sizeY - textSize) / 2;
    draw_text(text, textX, textY, textSize, textColor);
    if (isMouseOver && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        DrawRectangleLinesEx((Rectangle) { x, y, sizeX, sizeY }, 2, textColor);
        return BUTTON_DOWN_LEFT;
    }
    if (isMouseOver && IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
        DrawRectangleLinesEx((Rectangle) { x, y, sizeX, sizeY }, 2, textColor);
        return BUTTON_DOWN_RIGHT;
    }
    if (isMouseOver && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        DrawRectangleLinesEx((Rectangle) { x, y, sizeX, sizeY }, 2, textColor);
        return BUTTON_CLICK_LEFT;
    }
    if (isMouseOver && IsMouseButtonReleased(MOUSE_RIGHT_BUTTON)) {
        DrawRectangleLinesEx((Rectangle) { x, y, sizeX, sizeY }, 2, textColor);
        return BUTTON_CLICK_RIGHT;
    }
    if (isMouseOver) {
        DrawRectangleLinesEx((Rectangle) { x, y, sizeX, sizeY }, 2, textColor);
        return BUTTON_HOVER;
    }
    return BUTTON_NOT_INTERACTED;
}

int lua_draw_button(lua_State *L) {
    const char* text = luaL_checkstring(L, 1);
    int x = luaL_checkinteger(L, 2);
    int y = luaL_checkinteger(L, 3) + 90;
    int sizeX = luaL_checkinteger(L, 4);
    int sizeY = luaL_checkinteger(L, 5);
    Color baseColor = GetColor(luaL_checkinteger(L, 6));
    Color textColor = GetColor(luaL_checkinteger(L, 7));
    Color hoverColor = GetColor(luaL_checkinteger(L, 8));
    int textSize = luaL_optinteger(L, 9, 0);
    ButtonState state = draw_button((char*)text, x, y, sizeX, sizeY, baseColor, textColor, hoverColor, textSize);

    lua_pushinteger(L, state);

    return 1;
}

ButtonState draw_button_ex(char* text, int x, int y, int sizeX, int sizeY, Font font, Color baseColor, Color textColor, Color hoverColor, int textSize) {
    if (!textSize) {
        textSize = sizeY / 2;
    }
    bool isMouseOver = CheckCollisionPointRec(GetMousePosition(), (Rectangle) { x, y, sizeX, sizeY });
    Color buttonColor = isMouseOver ? hoverColor : baseColor;
    DrawRectangle(x, y, sizeX, sizeY, buttonColor);
    int textWidth = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        textWidth += MeasureText(&text[i], textSize);
    }
    int textX = x + (sizeX - MeasureTextEx(font, text, textSize, 4).x) / 2;
    int textY = y + (sizeY - textSize) / 2;
    draw_text_ex(text, textX, textY, font, textSize, textColor);
    if (isMouseOver && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        DrawRectangleLinesEx((Rectangle) { x, y, sizeX, sizeY }, 2, textColor);
        return BUTTON_DOWN_LEFT;
    }
    if (isMouseOver && IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
        DrawRectangleLinesEx((Rectangle) { x, y, sizeX, sizeY }, 2, textColor);
        return BUTTON_DOWN_RIGHT;
    }
    if (isMouseOver && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        DrawRectangleLinesEx((Rectangle) { x, y, sizeX, sizeY }, 2, textColor);
        return BUTTON_CLICK_LEFT;
    }
    if (isMouseOver && IsMouseButtonReleased(MOUSE_RIGHT_BUTTON)) {
        DrawRectangleLinesEx((Rectangle) { x, y, sizeX, sizeY }, 2, textColor);
        return BUTTON_CLICK_RIGHT;
    }
    if (isMouseOver) {
        DrawRectangleLinesEx((Rectangle) { x, y, sizeX, sizeY }, 2, textColor);
        return BUTTON_HOVER;
    }
    return BUTTON_NOT_INTERACTED;
}
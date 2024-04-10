#ifndef BUTTON_H
#define BUTTON_H
#include <raylib.h>
#include "game.h"

typedef struct
{
    enum
    {
        STILL,
        HOLD
    } state;
    Vector2 size;
    Vector2 pos;
    Texture2D tex;
} Button;

Button* init_button(Vector2 pos, const char* tex_path);
bool is_button_pressed(Button* button);
void draw_button(Button* button);

#endif
#include "include/button.h"
#include "include/game.h"
#include <raylib.h>
#include <stdlib.h>

Button* init_button(Vector2 pos, const char* tex_path)
{
    Button* button = calloc(1, sizeof(Button));

    button->tex = LoadTexture(tex_path);

    button->size.x = button->tex.width / 2 * 4;
    button->size.y = button->tex.height * 4;
    button->pos = pos;

    return button;
}

bool is_button_pressed(Button* button)
{
    if(GetMousePosition().x < button->pos.x ||
    GetMousePosition().x > button->pos.x + button->size.x ||
    GetMousePosition().y < button->pos.y ||
    GetMousePosition().y > button->pos.y + button->size.y
    )
    {
        if(button->state == HOLD) button->state = STILL;
        return false;
    }
    if(IsMouseButtonPressed(0) && button->state == STILL)
    {
        button->state = HOLD;
    }
    else if(IsMouseButtonReleased(0) && button->state == HOLD)
    {
        button->state = STILL;
        PlaySound(btn_sound);
        return true;
    }
    return false;
}

void draw_button(Button* button)
{
    DrawTexturePro(button->tex, (Rectangle){ button->state * button->tex.width / 2, 0 , button->tex.width/2, button->tex.height},
        (Rectangle){ button->pos.x, button->pos.y, button->size.x, button->size.y}, (Vector2){ 0 }, 0, WHITE);
}
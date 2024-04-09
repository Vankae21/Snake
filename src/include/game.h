#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "food.h"

#define TILE_SIZE 32
#define ROWS 16
#define COLS 16
#define WIDTH COLS * TILE_SIZE
#define HEIGHT (ROWS * TILE_SIZE + 192)
#define TITLE "GEYM"
#define FPS 60

extern Sound btn_sound;

void init();
void update();
void late_update();
void finish();
void replace_food(Food* food, Snake* snake);

void start();
void restart(Snake* snake);
void main_menu();

#endif
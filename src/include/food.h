#ifndef FOOD_H
#define FOOD_H

#include <raylib.h>

typedef struct
{
	int i;
	int j;
	Texture2D tex;
} Food;

Food* init_food(const char* tex_path);
void draw_food(Food* food);

#endif
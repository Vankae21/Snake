#include "include/food.h"
#include "include/game.h"
#include <stdlib.h>

Food* init_food(const char* tex_path)
{
	Food* food = calloc(1, sizeof(Food));
	
	food->i = 0;
	food->j = 0;

	food->tex = LoadTexture(tex_path);

	return food;
}

void draw_food(Food* food)
{
	Rectangle rec = { food->i * TILE_SIZE, food->j * TILE_SIZE, TILE_SIZE, TILE_SIZE };
	DrawTexturePro(food->tex, (Rectangle){ 0, 0, food->tex.width, food->tex.height}, rec, (Vector2){ 0 }, 0, WHITE);
}
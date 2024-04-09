#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "include/game.h"
#include "include/button.h"
#include "include/snake.h"
#include "include/tile.h"
#include "include/food.h"
#include "include/utils.h"

Snake* snake = (void*)0;
Food* food = (void*)0;
Tile* tiles[COLS][ROWS];

bool is_started = false;
bool is_paused = false;
bool lose = false;

unsigned short cur_score = 0;
unsigned short high_score = 0;

FILE* file = (void*)0;
const char* data_path = "player.txt";

// ui

Font font; 
Sound btn_sound;

Button* start_btn = (void*)0;
Button* replay_btn = (void*)0;
Button* main_btn = (void*)0;
Button* pause_btn = (void*)0;


void init()
{
	file = fopen(data_path, "r");

	if(!file)
	{
		file = fopen(data_path, "w");
		fprintf(file, "%d", 0);
		fclose(file);	

	}
	else
	{
		char buffer[16];
		fgets(buffer, 16, file);
		fclose(file);
		high_score = char_to_int(buffer);
	}

	srand(time(0));
	// tiles
	for(int i = 0; i < COLS; i++)
	{
		for(int j = 0; j < ROWS; j++)
		{
			tiles[i][j] = calloc(1, sizeof(Tile));
			tiles[i][j]->i = i;
			tiles[i][j]->j = j;
		}
	}

	snake = init_snake("assets/snake.png");
	food = init_food("assets/strawberry.png");
	
	food->i = -1;
	food->j = -1;

	// ui

	font = LoadFontEx("assets/JOYSTIX_MONOSPACE.otf", 64, (void*)0, 300);

	btn_sound = LoadSound("assets/blipSelect.wav");

	int btn_y = HEIGHT - 192 + 64;

	start_btn = init_button((Vector2){ WIDTH/2 - 32, btn_y }, "assets/start_btn.png");
	replay_btn = init_button((Vector2){ WIDTH/2 + 64, btn_y }, "assets/replay_btn.png");
	pause_btn = init_button((Vector2){ WIDTH/2 - 32, btn_y }, "assets/pause_btn.png");
	main_btn = init_button((Vector2){ WIDTH/2 - 128, btn_y }, "assets/main_btn.png");


}

void update()
{	

	// UI
	if(!is_started)
	{
		if(is_button_pressed(start_btn))
		{
			start();
		}
	}
	else
	{

		if(snake->bodies[0]->i == food->i && snake->bodies[0]->j == food->j)
		{
			enlarge_snake(snake);
			replace_food(food, snake);
			cur_score++;
		}

		if(IsKeyPressed(KEY_ESCAPE) || is_button_pressed(pause_btn))
		{
			is_paused = is_paused ? false : true;
		}

		if(lose || is_paused)
		{
			if(is_button_pressed(replay_btn))
			{
				restart(snake);
			}
			else if(is_button_pressed(main_btn))
			{
				main_menu();
			}

			return;
		}
	}

	// GAME

	

	update_snake(snake);

	for(int i = 1; i < snake->len; i++)
	{
		if(snake->bodies[0]->i == snake->bodies[i]->i && snake->bodies[0]->j == snake->bodies[i]->j)
		{
			lose = true;
			if(cur_score > high_score)
			{
				file = fopen(data_path, "w");
				fprintf(file, "%d", cur_score);
				fclose(file);
				high_score = cur_score;
			}
		}
	}
}

void late_update()
{
	// grids

	Color line_color = { 100, 150, 100, 255 };

	for(int i = 0; i < COLS; i++)
	{
		for(int j = 0; j < ROWS; j++)
		{
			DrawRectangleLines(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE, line_color);
		}
	}
	
	draw_snake(snake);
	draw_food(food);

	// ui

	char highscore_buffer[20];
	sprintf(highscore_buffer, "High score:%d", high_score);

	if(!is_started)
	{
		draw_button(start_btn);
		
		DrawTextEx(font, highscore_buffer, (Vector2){ 8 ,HEIGHT - 192 }, 32, 0, line_color);
		DrawTextEx(font, "Made by: Huseyn Aga", (Vector2){ 8 ,HEIGHT - 164 }, 32, 0, line_color);	
	}
	else
	{
		draw_button(pause_btn);

		char buffer[64];
		sprintf(buffer, "Score:%d", cur_score);
		DrawTextEx(font, buffer, (Vector2){ WIDTH - MeasureTextEx(font, buffer, 32, 0).x - 8,HEIGHT - 192 }, 32, 0, line_color);

		if(lose || is_paused)
		{
			draw_button(replay_btn);
			draw_button(main_btn);
			DrawTextEx(font, highscore_buffer, (Vector2){ 8 ,HEIGHT - 192 }, 32, 0, line_color);
		}
	}
}

void finish()
{
	free(snake);
	free(food);
	free(main_btn);
	free(pause_btn);
	free(replay_btn);
	free(start_btn);
}

void replace_food(Food* food, Snake* snake)
{
	int i = 0; int j = 0; int counter = 0;

	int grid_num = rand() % (ROWS*COLS - snake->len);

	bool is_collided = false;

	for(; i < COLS; i++)
	{
		for(; j < ROWS; j++)
		{
			is_collided = false;
			for(int k = 0; k < snake->len; k++)
			{
				if(snake->bodies[k]->i == i && snake->bodies[k]->j == j)
				{
					is_collided = true;
					break;
				}
			}
			if(is_collided) continue;
			if(counter == grid_num)
			{
				food->i = i;
				food->j = j;
				return;
			}
			counter++;
		}
		j = 0;
	}
}

void restart(Snake* snake)
{
	lose = false;
	is_paused = false;
	is_started = true;
	
	cur_score = 0;
	
	recreate_snake(snake);
	replace_food(food, snake);
}

void start()
{
	is_started = true;
	lose = false;
	is_paused = false;

	cur_score = 0;
	
	replace_food(food, snake);
}

void main_menu()
{
	is_paused = false;
	is_started = false;
	lose = false;

	cur_score = 0;

	recreate_snake(snake);
	food->i = -1; food->j = -1;
}
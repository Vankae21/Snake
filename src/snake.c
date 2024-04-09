#include "include/snake.h"
#include "include/game.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

float timer = 0;
float tick_time = 0.16f;
bool time_passed(float* timer, float time_to_pass);
void move_last_to_first(Snake* snake);

Snake* init_snake(const char* tex_path)
{
	Snake* snake = calloc(1, sizeof(Snake));

	snake->dir = (Vector2){ 1, 0 };
	snake->len = 1;

	// body

	snake->bodies = calloc(snake->len, sizeof(Body*));
	
	snake->bodies[0] = calloc(1, sizeof(Body));
	snake->bodies[0]->i = 0;
	snake->bodies[0]->j = 0;

	snake->tex = LoadTexture(tex_path);
	snake->head_case = 1;

	return snake;
}

bool turned = false;
void update_snake(Snake* snake)
{	
	int key = GetKeyPressed();
	
	if(!turned)
	switch(key)
	{
		case KEY_A:
			if(snake->dir.x != 1 || snake->len == 1)
			{
				snake->dir = (Vector2){ -1, 0 };
				turned = true;
				snake->head_case = 3;
			}
			break;
		case KEY_D:
			if(snake->dir.x != -1 || snake->len == 1)
			{
				snake->dir = (Vector2){ 1, 0 };
				turned = true;
				snake->head_case = 1;
			}
			break;
		case KEY_W:
			if(snake->dir.y != 1 || snake->len == 1)
			{
				snake->dir = (Vector2){ 0, -1 };
				turned = true;
				snake->head_case = 0;
			}
			break;
		case KEY_S:
			if(snake->dir.y != -1 || snake->len == 1)
			{
				snake->dir = (Vector2){ 0, 1 };
				turned = true;
				snake->head_case = 2;
			}
			break;
		default:
			break;
	}

	if(time_passed(&timer, tick_time))
	{
		if(snake->len > 1)
		move_last_to_first(snake);

		
		snake->bodies[0]->i += snake->dir.x;
		snake->bodies[0]->j += snake->dir.y;

		turned = false;
	}

	if(snake->bodies[0]->i == COLS)
	{
		snake->bodies[0]->i = 0;
	}
	else if(snake->bodies[0]->i == -1)
	{
		snake->bodies[0]->i = COLS - 1; 
	}
	if(snake->bodies[0]->j == ROWS)
	{
		snake->bodies[0]->j = 0;
	}
	else if(snake->bodies[0]->j == -1)
	{
		snake->bodies[0]->j = ROWS - 1;
	}
}

void draw_snake(Snake* snake)
{

	for(int i = 1; i < snake->len; i++)
	{
		Rectangle rec = { snake->bodies[i]->i * TILE_SIZE, snake->bodies[i]->j * TILE_SIZE, TILE_SIZE, TILE_SIZE };
		
		DrawTexturePro(snake->tex, (Rectangle){ snake->tex.width / 5 * 4, 0, snake->tex.width / 5, snake->tex.height },
			rec, (Vector2){ 0 }, 0, WHITE);
	}
	
	Rectangle rec = { snake->bodies[0]->i * TILE_SIZE, snake->bodies[0]->j * TILE_SIZE, TILE_SIZE, TILE_SIZE };
	
	DrawTexturePro(snake->tex, (Rectangle){ snake->tex.width / 5 * snake->head_case, 0, snake->tex.width / 5, snake->tex.height },
		rec, (Vector2){ 0 }, 0, WHITE);

}

bool time_passed(float* timer, float time_to_pass)
{
	if(*timer + GetFrameTime() < time_to_pass)
	{
		*timer += GetFrameTime();
		return false;
	}
	*timer = 0;
	return true;
}

void enlarge_snake(Snake* snake)
{
	snake->len++;
	snake->bodies = realloc(snake->bodies, snake->len * sizeof(Body*));

	Body* last_body = calloc(1, sizeof(Body));
	last_body->i = snake->bodies[0]->i + snake->dir.x;
	last_body->j = snake->bodies[0]->j + snake->dir.y;
	snake->bodies[snake->len - 1] = last_body;

	move_last_to_first(snake);

	snake->bodies[0]->i += snake->dir.x;
	snake->bodies[0]->j += snake->dir.y;
}

void move_last_to_first(Snake* snake)
{
	Body** bodies = snake->bodies;
	int len = snake->len;

	Body** new_bodies = calloc(len, sizeof(Body*));



	for(int i = 1; i < len; i++)
	{
		new_bodies[i] = bodies[i - 1];
	}
	new_bodies[0] = bodies[len - 1];

	new_bodies[0]->i = new_bodies[1]->i;
	new_bodies[0]->j = new_bodies[1]->j;

	free(snake->bodies);

	snake->bodies = new_bodies;
}

void recreate_snake(Snake* snake)
{
	for(int i = 1; i < snake->len; i++)
	{
		free(snake->bodies[i]);
	}
	snake->len = 1;
	snake->bodies = realloc(snake->bodies, snake->len * sizeof(Body*));
	snake->bodies[0]->i = 0;
	snake->bodies[0]->j = 0;
	snake->dir = (Vector2){ 1, 0 };
	snake->head_case = 1;

	timer = 0;
}












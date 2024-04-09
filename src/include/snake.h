#ifndef SNAKE_H
#define SNAKE_H

#include <raylib.h>

typedef struct
{
	int i;
	int j;
} Body;

typedef struct
{
	unsigned short len;
	Body** bodies;
	Vector2 dir;
	Texture2D tex;
	int head_case;
} Snake;

Snake* init_snake(const char* tex_path);
void update_snake(Snake* snake);
void draw_snake(Snake* snake);
void enlarge_snake(Snake* snake);
void recreate_snake(Snake* snake);

#endif
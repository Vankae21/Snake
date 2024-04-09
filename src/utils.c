#include "include/utils.h"

float vec2_len(Vector2 vec)
{
	return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

Vector2 vec2_normalize(Vector2 vec)
{
	return vec2_len(vec) == 0 ? (Vector2){0} : (Vector2){ .x = vec.x/vec2_len(vec), .y = vec.y/vec2_len(vec) };
}

bool is_rec_circle_colliding(Rectangle rec, Circle cir)
{
	return (rec.x + rec.width >= cir.center.x - cir.radius &&
			cir.center.x + cir.radius >= rec.x &&
			rec.y + rec.height >= cir.center.y - cir.radius &&
			cir.center.y + cir.radius >= rec.y);
}

float vec2_distance(Vector2 vec_a, Vector2 vec_b)
{
	return sqrtf((vec_a.x - vec_b.x) * (vec_a.x - vec_b.x) + (vec_a.y - vec_b.y) * (vec_a.y - vec_b.y));
}

int char_to_int(const char* str)
{
	int result = 0;

	for(int i = 0; str[i] != '\0'; i++)
	{
		result = result * 10 + str[i] - 48;
	}

	return result;
}
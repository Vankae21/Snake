#include <raylib.h>
#include "include/game.h"

int main(int argc, char** argv)
{
	InitWindow(WIDTH, HEIGHT, TITLE);
	InitAudioDevice();
	SetTargetFPS(FPS);
	SetExitKey(0);

	init();

	Color bg_color = { 161, 187, 157, 255 };

	while(!WindowShouldClose())
	{
		update();
		BeginDrawing();
		ClearBackground(bg_color);
		late_update();
		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();
	finish();

	return 0;
}
#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define NUM_STARS 100

typedef struct {
	int x;
	int y;
} Star;

//mebbe struct for planet later


int main(void) {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Solar Sys");
	SetTargetFPS(60);
	
	srand(time(NULL));
	Star stars[NUM_STARS];

	for (int i = 0; i < NUM_STARS; i++) {
	  stars[i].x = rand() % SCREEN_WIDTH;
	  stars[i].y = rand() % SCREEN_HEIGHT;
	}

	while (!WindowShouldClose()) {
	  BeginDrawing();
	  ClearBackground(BLACK);
	  
	  for (int i = 0; i < NUM_STARS; i++) {
		DrawText(".", stars[i].x, stars[i].y, 16, WHITE);
	  }
	  //draw 3D spheres for planets
	  EndDrawing();
	 }
	CloseWindow();
	return 0;
}


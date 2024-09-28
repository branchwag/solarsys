#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

//mebbe struct for planet later


int main(void) {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Solar Sys");
	SetTargetFPS(60);
	int frameCount = 0;
	int numOfStars = 100;
	

	

	while (!WindowShouldClose()) {
	  frameCount++;
	  BeginDrawing();
	  ClearBackground(BLACK);

	  //draw stars	
	srand(time(NULL));
	int randomPosNumber = rand();
	int rangePosMin = 1;
	int rangePosMax = SCREEN_WIDTH;
	int randomPosInRange = (rand() % (rangePosMax - rangePosMin + 1)) + rangePosMin;

	  for (int i = 0; i < numOfStars; i++) {
	  DrawText(".", randomPosInRange, randomPosInRange, 16, WHITE);
	  }
	  //draw 3D spheres for planets
	  EndDrawing();
	 }
	CloseWindow();
	return 0;
}


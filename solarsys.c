#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define NUM_STARS 100

typedef struct {
	int x;
	int y;
	float brightness;
	float twinkleSpeed;
	float twinklePhase;
} Star;

//mebbe struct for planet later

float RandomFloat(float min, float max) {
	return min + (float)rand() / (float)RAND_MAX * (max - min);
}

int main(void) {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Solar Sys");
	SetTargetFPS(60);
	
	srand(time(NULL));
	Star stars[NUM_STARS];

	for (int i = 0; i < NUM_STARS; i++) {
	  stars[i].x = rand() % SCREEN_WIDTH;
	  stars[i].y = rand() % SCREEN_HEIGHT;       
	  stars[i].brightness = RandomFloat(0.5f, 1.0f);
          stars[i].twinkleSpeed = RandomFloat(0, 1.0f);
          stars[i].twinklePhase = RandomFloat(0, 2 * PI);
	}

	float timeElapsed = 0.0f;

	while (!WindowShouldClose()) {
	  timeElapsed += GetFrameTime();

	  BeginDrawing();
	  ClearBackground(BLACK);
	  
	  for (int i = 0; i < NUM_STARS; i++) {
            float twinkle = sinf(timeElapsed * stars[i].twinkleSpeed + stars[i].twinklePhase);
            stars[i].brightness = (twinkle + 1.0f) / 2.0f * 0.5f + 0.5f;
            
            unsigned char alpha = (unsigned char)(stars[i].brightness * 255);
            Color starColor = {255, 255, 255, alpha};

            int starSize = (twinkle > 0) ? 2 : 1;

            DrawCircle(stars[i].x, stars[i].y, starSize, starColor);
	  }
	  //draw 3D spheres for planets
	  EndDrawing();
	 }
	CloseWindow();
	return 0;
}


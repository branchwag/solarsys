#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900
#define NUM_STARS 100
#define NUM_PLANETS 8

typedef struct {
	int x;
	int y;
	float brightness;
	float twinkleSpeed;
	float twinklePhase;
} Star;

typedef struct {
	Vector3 position;
	float radius;
	float orbitRadius;
	float orbitSpeed;
	Color color;
	Model model;
	Texture2D texture;
} Planet;

float RandomFloat(float min, float max) {
	return min + (float)rand() / (float)RAND_MAX * (max - min);
}

int main(void) {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Solar Sys");
	SetTargetFPS(60);

	Camera3D camera = { 0 };
	camera.position = (Vector3){ 0.0f, 2.0f, 25.0f };
	camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;

	srand(time(NULL));

  //init
	Star stars[NUM_STARS];
	for (int i = 0; i < NUM_STARS; i++) {
	  stars[i].x = rand() % SCREEN_WIDTH;
	  stars[i].y = rand() % SCREEN_HEIGHT;       
	  stars[i].brightness = RandomFloat(0.5f, 1.0f);
          stars[i].twinkleSpeed = RandomFloat(0, 1.0f);
          stars[i].twinklePhase = RandomFloat(0, 2 * PI);
	}

      Planet planets[NUM_PLANETS];
      const char* texturePaths[] = {"sun.png", "mercury.png", "venus.png", "earth.png", "mars.png", "jupiter.png", "saturn.png", "uranus.png"};
      Color planetColors[] = {GOLD, GRAY, BEIGE, BLUE, RED, ORANGE, YELLOW, SKYBLUE};

      for (int i = 0; i < NUM_PLANETS; i++) {
	planets[i].radius = 0.5f + i * 0.2f;
	planets[i].orbitRadius = 5.0f + i * 3.0f;
	planets[i].orbitSpeed = (8 - i) * 0.1f;
	planets[i].color = planetColors[i];
	planets[i].model = LoadModelFromMesh(GenMeshSphere(planets[i].radius, 32, 32));
	planets[i].texture = LoadTexture(texturePaths[i]);
	planets[i].model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = planets[i].texture;
  }

	float timeElapsed = 0.0f;

	while (!WindowShouldClose()) {
	  if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) camera.position.x += 0.1f;
	  if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) camera.position.x -= 0.1f;
	  if(IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) camera.position.z -= 0.1f;
	  if(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) camera.position.z += 0.1f;

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
	  BeginMode3D(camera);
	  
	  for (int i = 0; i < NUM_PLANETS; i++) {
	      float angle = timeElapsed * planets[i].orbitSpeed;
	      planets[i].position.x = cosf(angle) * planets[i].orbitRadius;
	      planets[i].position.z = sinf(angle) * planets[i].orbitRadius;
	      planets[i].position.y = 0;

	      DrawModel(planets[i].model, planets[i].position, 1.0f, planets[i].color);
    }
	  
	  EndMode3D();
	  
          DrawText("Move camera with arrow keys or WASD", 10, 10, 20, DARKGRAY);
	  EndDrawing();
	 }
	for (int i = 0; i < NUM_PLANETS; i++) {
	   UnloadTexture(planets[i].texture);
	   UnloadModel(planets[i].model);
	}

	CloseWindow();
	return 0;
}


#ifndef RAYLIB
#define RAYLIB
#include <bits/stdc++.h>
#include "raylib.h"
#endif 
using namespace std;
#include "./birds.hpp"
int total_birds = 800;
int screenWidth = 800;
int screenHeight = 800;
float viewRadius = 70;
  
int main()
{
    SetRandomSeed(1);
    Bird *birds = (Bird *)malloc(sizeof(Bird) * total_birds);

    for (int i = 0; i < total_birds; i++)
    {
        birds[i] = Bird(screenWidth, screenHeight);
    }
    InitWindow(screenWidth, screenHeight, "Flocking Birds");
    SetTargetFPS(30);
   
    while (!WindowShouldClose())
    {
        // adjust birds position and velocity
        for (int i = 0; i < total_birds; i++)
        {
            birds[i].alignment(birds, total_birds, viewRadius);
            birds[i].cohesion(birds, total_birds, viewRadius);
            birds[i].separation(birds, total_birds, viewRadius);
            birds[i].updateVel(4);
            birds[i].move(screenWidth, screenHeight);
            birds[i].drawBird();
        }

        // Draw birds with position and velocity
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = 0; i < total_birds; i++)
        {
            birds[i].drawBird();
        }
        EndDrawing();
    }
  
    CloseWindow();
    MemFree(birds);
    return 0;
} 
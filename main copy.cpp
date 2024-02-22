#ifndef RAYLIB
#define RAYLIB
#include <bits/stdc++.h>
#include "raylib.h"
#endif
using namespace std;
#include "./slider.cpp"
#include "./birds.hpp"
#define FPS 10

int total_birds = 4000;
int screenWidth = 1000;
int screenHeight = 800;
float alignmentRadius = 50;
float cohesionRadius = 50;
float separationRadius = 50;

int main()
{
    SetRandomSeed(1);
    Bird *birds = (Bird *)malloc(sizeof(Bird) * total_birds);
    for (int i = 0; i < total_birds; i++)
    {
        birds[i] = Bird(screenWidth, screenHeight);
    }

    InitWindow(screenWidth, screenHeight, "Flocking Birds");
    SetTargetFPS(FPS);
    float value = 50.0f;
   
    Slider SeparationRadius(50, 50, 200, 20, separationRadius, "Separation");
    Slider CohesionRadius(50, 100, 200, 20, cohesionRadius, "Cohesion");
    Slider AlignmentRadius(50, 150, 200, 20, alignmentRadius, "Alignment");

    while (!WindowShouldClose())
    {
        for (int i = 0; i < total_birds; i++)
        {
            birds[i].alignment(birds, total_birds, alignmentRadius);
            birds[i].cohesion(birds, total_birds, cohesionRadius);
            birds[i].separation(birds, total_birds, separationRadius);
            birds[i].setMag(12);
            birds[i].move(screenWidth, screenHeight);
            birds[i].drawBird();
        }

        // Draw birds with position and velocity
        BeginDrawing();
        ClearBackground(RAYWHITE);

        AlignmentRadius.UpdateSlider(alignmentRadius);
        CohesionRadius.UpdateSlider(cohesionRadius);
        SeparationRadius.UpdateSlider(separationRadius);

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
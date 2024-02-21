#ifndef RAYLIB
#define RAYLIB
#include <bits/stdc++.h>
#include "raylib.h"
#endif
using namespace std;
#include "./slider.cpp"
#include "./birds.hpp"
#define FPS 60

int total_birds = 800;
int screenWidth = 800;
int screenHeight = 800;
float alignmentRadius = 100;
float cohesionRadius = 100;
float separationRadius = 100;

int main()
{
    SetRandomSeed(1);
    Bird *birds = (Bird *)malloc(sizeof(Bird) * total_birds);
    for (int i = 0; i < total_birds; i++)
    {
        birds[i] = Bird(screenWidth, screenHeight);
    }

    
    InitWindow(screenWidth, screenHeight, "Flocking Birds");
    SetTargetFPS(FPS );
    float value = 50.0f;
    
    Slider SeparationRadius(50,50,200,20,value, "Separation");
    Slider CohesionRadius(50,100,200,20,value, "Cohesion");
    Slider AlignmentRadius(50,150,200,20,value, "Alignment");
    

    while (!WindowShouldClose())
    {
        // if (IsKeyPressed(KEY_Q))
        // {
        //     separationRadius += 10;
        //     cout << separationRadius << endl;
        // }
        // if (IsKeyDown(KEY_W))
        // {
        //     separationRadius -= 10;
        //     cout << separationRadius << endl;
        // }
        // if (IsKeyDown(KEY_A))
        // {
        //     cohesionRadius += 10;
        //     cout << cohesionRadius << endl;
        // }
        // else if (IsKeyPressed(KEY_S))
        // {
        //     cohesionRadius -= 10;
        //     cout << cohesionRadius << endl;
        // }
        // else if (IsKeyPressed(KEY_Z))
        // {  
        //     alignmentRadius += 10;
        //     cout << alignmentRadius << endl;
        // } 
        // else if (IsKeyPressed(KEY_X))
        // {
        //     alignmentRadius -= 10;
        //     cout << alignmentRadius << endl;
        // }

        for (int i = 0; i < total_birds; i++)
        {
            birds[i].alignment(birds, total_birds, alignmentRadius);
            birds[i].cohesion(birds, total_birds, cohesionRadius);
            birds[i].separation(birds, total_birds, separationRadius);
            birds[i].setMag(30);
            birds[i].move(screenWidth, screenHeight);
            birds[i].drawBird();
        }
 
        // Draw birds with position and velocity
        BeginDrawing();
        ClearBackground(RAYWHITE);

        AlignmentRadius.UpdateSlider(alignmentRadius);
        CohesionRadius.UpdateSlider(cohesionRadius);
        SeparationRadius.UpdateSlider(separationRadius);
        // if (IsKeyDown(KEY_UP))
        // {
        //     DrawText("Upper arrow key is pressed!", 10, 10, 20, RED);
        // }

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
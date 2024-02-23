#ifndef RAYLIB
#define RAYLIB
#include "raylib.h"
#include <bits/stdc++.h>
#endif
using namespace std;

class Slider
{
    Rectangle slider;
    float value;
    string name;
    int limit;

public:
    Slider();
    Slider(float x, float y, float width, float height, float &value, string name, int limit);
    void UpdateSlider(float &sliderVal);
};

Slider::Slider(float x, float y, float width, float height, float &value, string name, int limit)
{
    this->slider = {x, y, width, height};
    this->value = value;   
    this -> name = name;
    this -> limit = limit;
}

void Slider::UpdateSlider(float &sliderVal){
    DrawRectangleRec(slider, LIGHTGRAY);
    DrawRectangle((int)slider.x + (int)((this->value / (float)limit) * slider.width), (int)slider.y, 2, (int)slider.height, RED);

    if (CheckCollisionPointRec(GetMousePosition(), this->slider) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        this->value = ((GetMouseX() - slider.x) / slider.width) * (this -> limit);
    }
    sliderVal = this -> value;
    DrawText(TextFormat("%s %02.2f",this -> name.c_str(),this->value), this -> slider.x, this -> slider.y +20, 20, DARKGRAY);
}

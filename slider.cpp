#ifndef RAYLIB
#define RAYLIB
#include "raylib.h"
#include <bits/stdc++.h>
#endif

class Slider
{
    Rectangle slider;
    float value;
    string name;
    
public:
    Slider();
    Slider(float x, float y, float width, float height, float &value, string name);
    void UpdateSlider(float &sliderVal);
};

Slider::Slider(float x, float y, float width, float height, float &value, string name)
{
    this->slider = {x, y, width, height};
    this->value = value;   
    this -> name = name;
}

void Slider::UpdateSlider(float &sliderVal){
    DrawRectangleRec(slider, LIGHTGRAY);
    DrawRectangle((int)slider.x + (int)((this->value / 100.0f) * slider.width), (int)slider.y, 2, (int)slider.height, RED);

    if (CheckCollisionPointRec(GetMousePosition(), this->slider) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        this->value = ((GetMouseX() - slider.x) / slider.width) * 100.0f;
    }
    sliderVal = this -> value;
    DrawText(TextFormat("%s %02.2f",this -> name.c_str(),this->value), this -> slider.x, this -> slider.y +20, 20, DARKGRAY);
}

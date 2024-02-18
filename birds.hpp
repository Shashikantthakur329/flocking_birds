#ifndef RAYLIB
#define RAYLIB
#include "raylib.h"
#include <bits/stdc++.h>
#endif

using namespace std;

class Bird
{
    Vector2 pos;
    Vector2 vel;
    Color color;
    int magVel;

public:
    Bird(int width, int height);
    Vector2 getPos();
    Vector2 getVel();
    void updateVel(int magVel);
    float getDist(Vector2 anotherPos);
    Vector2 getDir(Vector2 anotherPos);
    void changeVel(Vector2 dir, float rate);
    // void move(int width, int height);
    void move(int screenWidth, int screenHeight);
    void drawBird();
    Vector2 alignment(Bird *birds, int total_birds, int radius);
    void cohesion(Bird *birds, int total_birds, int radius);
    void separation(Bird *birds, int total_birds, int radius);
};

Bird::Bird(int screenWidth, int screenHeight)
{
    int x = GetRandomValue(0, screenWidth - 1);
    int y = GetRandomValue(0, screenHeight - 1);
    pos.x = x;
    pos.y = y;
    vel.x = GetRandomValue(-100, 100) / 1000.f;
    vel.y = GetRandomValue(-100, 100) / 1000.f;
    float magVel = sqrt(vel.x * vel.x + vel.y * vel.y);
    vel.x = vel.x / magVel;
    vel.y = vel.y / magVel;
    color = (Color){0, 0, 0, 100};
}

Vector2 Bird::getPos()
{
    return this->pos;
}

Vector2 Bird::getVel()
{
    return this->vel;
}

float Bird::getDist(Vector2 aPos)
{
    float dx = aPos.x - pos.x;
    float dy = aPos.y - pos.y;
    return sqrt(dx * dx + dy * dy);
}

void Bird::changeVel(Vector2 dir, float rate)
{
    return;
}

Vector2 Bird::getDir(Vector2 anotherPos)
{
    float dx = anotherPos.x - pos.x;
    float dy = anotherPos.y - pos.y;
    float dist = getDist(anotherPos);

    if (dist == 0.0f)
        dist = 1;
    Vector2 dirn = (Vector2){dx * (1 / dist), dy * (1 / dist)};
    return dirn;
}

void Bird::move(int screenWidth, int screenHeight)
{
    pos.x += vel.x;
    pos.y += vel.y;
    if(pos.x >= screenWidth - 50 || pos.x <= 30){
        vel.x *= 0.9;
        // pos.x = 200;
    }
    if(pos.y >= screenHeight - 50 || pos.y <= 30){
        vel.y *= 0.9;
        // pos.y = 200;
    }
    if(pos.x >= screenWidth || pos.x <= 0){
        vel.x *= -1;
        // pos.x = 200;
    }
    if(pos.y >= screenHeight || pos.y <= 0){
        vel.y *= -1;
        // pos.y = 200;
    }
    // if (pos.x >= screenWidth)
    // {
    //     pos.x = 2;
    // }
    // else if (pos.x <= 0)
    // {
    //     pos.x = screenWidth - 2;
    // }
    // if (pos.y >= screenHeight)
    // {
    //     pos.y = 2;
    // }
    // else if (pos.y <= 0)
    // {
    //     pos.y = screenHeight - 2;
    // }
    pos.x += 2*vel.x;
    pos.y += 2*vel.y;
}

void Bird::updateVel(int magVel)
{
    vel.x *= magVel;
    vel.y *= magVel;
    return;
}

void Bird::drawBird()
{
    DrawCircle(pos.x, pos.y, 3, color);
    // DrawPixelV(pos, color);
}

Vector2 Bird::alignment(Bird *birds, int total_birds, int radius)
{
    Vector2 retDir = {0, 0};
    int birdCount = 0;
    for (int i = 0; i < total_birds; i++)
    {
        float dist = getDist(birds[i].getPos());
        if (dist <= radius)
        {
            birdCount++;
            retDir.x += birds[i].getVel().x;
            retDir.y += birds[i].getVel().y;
        }
    }
    float magntDir = sqrt(retDir.x * retDir.x + retDir.y * retDir.y);
    retDir.x = retDir.x / magntDir;
    retDir.y = retDir.y / magntDir;

    // velocity badh rhi hai har baar
    vel.x += retDir.x;
    vel.y += retDir.y;

    float magVel = sqrt(vel.x * vel.x + vel.y * vel.y);
    vel.x = vel.x / magVel;
    vel.y = vel.y / magVel;
    return retDir;
}

void Bird::cohesion(Bird *birds, int total_birds, int radius)
{
    Vector2 dirPos = {0, 0};
    int numBirds = 0;
    for (int i = 0; i < total_birds; i++)
    {
        if (getDist(birds[i].getPos()) <= radius)
        {
            numBirds++;
            dirPos.x = dirPos.x + birds[i].getPos().x;
            dirPos.y = dirPos.y + birds[i].getPos().y;
        }
    }

    int magVel = sqrt(dirPos.x * dirPos.x + dirPos.y * dirPos.y);
    vel.x += dirPos.x / magVel;
    vel.y += dirPos.y / magVel;
}

void Bird::separation(Bird *birds, int total_birds, int radius)
{
    Vector2 dirPos = {0, 0};
    int numBirds = 0;
    for (int i = 0; i < total_birds; i++)
    {
        if (getDist(birds[i].getPos()) <= radius)
        {
            numBirds++;
            dirPos.x = dirPos.x + birds[i].getPos().x;
            dirPos.y = dirPos.y + birds[i].getPos().y;
        }
    }
    dirPos.x *= -1;
    dirPos.y *= -1;
    int magVel = sqrt(dirPos.x * dirPos.x + dirPos.y * dirPos.y);
    vel.x += dirPos.x / magVel;
    vel.y += dirPos.y / magVel;
}
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
    Vector2 acc;
    Color color;
    int magVel;
    int magAcc;

public:
    Bird(int width, int height);
    Vector2 getPos();
    Vector2 getVel();
    void setMag(int magVel);
    float getDist(Vector2 anotherPos);
    Vector2 getDir(Vector2 anotherPos);
    void changeVel(Vector2 dir, float rate);
    // void move(int width, int height);
    void move(int screenWidth, int screenHeight);
    void drawBird();
    Vector2 alignment(Bird *birds, int total_birds, float radius);
    void cohesion(Bird *birds, int total_birds, float radius);
    void separation(Bird *birds, int total_birds, float radius);
};

Bird::Bird(int screenWidth, int screenHeight)
{
    int x = GetRandomValue(0, screenWidth - 1);
    int y = GetRandomValue(0, screenHeight - 1);
    this->pos.x = x;
    this->pos.y = y;
    this->vel.x = GetRandomValue(-100, 100) / 100.f;
    this->vel.y = GetRandomValue(-100, 100) / 100.f;
    // cout << this->pos.x << " " << this->pos.y << endl;
    // cout << this->vel.x << " " << this->vel.y << endl;
    this->acc.x = 0;
    this->acc.y = 0;
    this->magAcc = 3;
    this->magVel = 6;
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
    this -> vel.x += this -> acc.x;
    this -> vel.y += this -> acc.y;
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

    this->vel.x += this->acc.x;
    this->vel.y += this->acc.y;

    this->pos.x += this->vel.x;
    this->pos.y += this->vel.y;
    
    // cout<<this -> pos.x << " " << this -> pos.y <<" "<< this -> vel.x << " " << this -> vel.y<<endl;
    // cout<<this -> acc.x << " "<<this -> acc.y<<endl;
    if (this->pos.y >= screenHeight - 1)
    {
        this->pos.y = 0;
    }
    if (this->pos.y < 0)
    {
        this->pos.y = screenHeight - 2;
    }
    
    if (this->pos.x >= screenWidth - 1)
    {
        this->pos.x = 0;
    }
    if (this->pos.x < 0)
    {
        this->pos.x = screenWidth - 2;
    }
}

void Bird::setMag(int magVels)
{
    float mag = sqrt(this->vel.x * this->vel.x + this->vel.y * this->vel.y);
    if (mag >= magVel)
    {
        this->vel.x = this->vel.x / mag;
        this->vel.y = this->vel.y / mag;
        this->vel.x *= magVels;
        this->vel.y *= magVels;
    }

    float macc = sqrt(acc.x * acc.x + acc.y * acc.y);
    if (macc < this -> magAcc)
    {
        return;
    }
    this -> acc.x = this -> acc.x / macc;
    this -> acc.y = this -> acc.y / macc;

    return;
}

void Bird::drawBird()
{
    // DrawPixel(pos.x, pos.y, color);
    DrawCircle(pos.x, pos.y, 2, color);
}

Vector2 Bird::alignment(Bird *birds, int total_birds, float radius)
{
    Vector2 retDir = {0, 0};
    int birdCount = 0;
    for (int i = 0; i < total_birds; i++)
    {
        float dist = getDist(birds[i].getPos());
        if (dist > 0.01 && dist <= radius)
        {
            birdCount++;
            retDir.x += birds[i].getVel().x;
            retDir.y += birds[i].getVel().y;
        }
    }

    if (birdCount > 0)
    {
        retDir.x /= birdCount;
        retDir.y /= birdCount;
    }

    acc.x += retDir.x;
    acc.x += retDir.y;

    return retDir;
}

void Bird::cohesion(Bird *birds, int total_birds, float radius)
{
    Vector2 dirPos = {0, 0};
    int numBirds = 0;
    for (int i = 0; i < total_birds; i++)
    {
        float dist = getDist(birds[i].getPos());
        if ( dist != 0 && dist <= radius)
        {
            numBirds++;
            dirPos.x += (birds[i].getPos().x - pos.x);
            dirPos.y += (birds[i].getPos().y - pos.y);
        }
    }

    Vector2 dir;
    if (numBirds > 0)
    {
        dir.x = dirPos.x / numBirds;
        dir.y = dirPos.y / numBirds;
    }

    acc.x += dir.x;
    acc.y += dir.y;

    // float magVel = sqrt(dir.x * dir.x + dir.y * dir.y);
    // acc.x += (dir.x / magVel);
    // acc.y += (dir.y / magVel);
}

void Bird::separation(Bird *birds, int total_birds, float radius)
{
    Vector2 dirPos = {0, 0};
    int numBirds = 0;
    int minm = INT_MAX;
    for (int i = 0; i < total_birds; i++)
    {
        float d = getDist(birds[i].getPos());
        if (d != 0 && d <= radius)
        {
            numBirds++;
            dirPos.x += (pos.x - birds[i].getPos().x);
            dirPos.y += (pos.y - birds[i].getPos().y);
            dirPos.x /= (d * d);
            dirPos.y /= (d * d);
        }
    }
    // Vector2 dir;
    acc.x += dirPos.x;
    acc.y += dirPos.y;
    return;

    // dir.x *= -1;
    // dir.y *= -1;
 
    // dirPos = dir;
    // int magVel = sqrt(dirPos.x * dirPos.x + dirPos.y * dirPos.y);
    // vel.x += dirPos.x / magVel;
    // vel.y += dirPos.y / magVel;
}
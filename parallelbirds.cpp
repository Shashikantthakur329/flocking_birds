#ifndef RAYLIB
#define RAYLIB
#include "raylib.h"
#include <bits/stdc++.h>
#endif
#include <pthread.h>
#include "./birds.hpp"
#include "./parallelbirds.hpp"

// input for parallel cohesion, separation and alignment
struct input
{
    Bird *birdArr;
    Bird *currBird;
    int size;
    float radius;
    pthread_barrier_t *barrier;
    Vector2 *result; // to store the result
};

class ParallelBird : public Bird
{
public:
    ParallelBird(int screenWidth, int screenHeight);
    // void* parallel_cohesion(void *args);
    Vector2 cohesion(Bird *birds, int total_birds, float radius);
    Vector2 separation(Bird *birds, int total_birds, float radius);
    Vector2 alignment(Bird *birds, int total_birds, float radius);
};

ParallelBird::ParallelBird(int screenWidth, int screenHeight)
    : Bird(screenWidth, screenHeight) // Call the base class (Bird) constructor
{
}

void *parallel_cohesion(void *args)
{
    input *inp = (input *)args;
    Bird *birdArr = inp->birdArr;
    Bird *currBird = inp->currBird;
    int size = inp->size;
    float radius = inp->radius;
    pthread_barrier_t *barrier = inp->barrier;
    Vector2 *res = inp->result;

    int numBirds = 0;
    Vector2 retDir = {0, 0};
    Vector2 currPos = currBird->getPos();

    for (int i = 0; i < size; i++)
    {
        float dist = currBird->getDist(birdArr[i].getPos());
        if (dist != 0 && dist <= radius)
        {
            numBirds++;
            retDir.x += (birdArr[i].getPos().x - currPos.x);
            retDir.y += (birdArr[i].getPos().y - currPos.y);
        }
    }

    if (numBirds > 0)
    {
        retDir.x = retDir.x / numBirds;
        retDir.y = retDir.y / numBirds;
    }

    pthread_barrier_wait(barrier);
    *res = retDir;
    // currBird->addAcc(retDir);
    return res;
}

Vector2 ParallelBird::cohesion(Bird *birds, int total_birds, float radius)
{
    Vector2 ret = {0, 0};
    int size = total_birds / numOfThreads;
    pthread_t threads[numOfThreads];
    Vector2 *results = new Vector2[numOfThreads];

    pthread_barrier_t barrier; /*  */
    pthread_barrier_init(&barrier, NULL, numOfThreads + 1);
    for (int j = 0; j < numOfThreads; j++)
    {
        input inp = {birds + j * size, this, size, radius, &barrier, &results[j]};
        pthread_create(&threads[j], NULL, parallel_cohesion, (void *)(&inp));
    }

    // Wait for all threads to reach the barrier before continuing
    pthread_barrier_wait(&barrier);

    // Join threads after they finish
    for (int j = 0; j < numOfThreads; j++)
    {
        pthread_join(threads[j], NULL);
    }

    for (int j = 0; j < numOfThreads; j++)
    {
        ret.x += results[j].x;
        ret.y += results[j].y;
    }

    // Destroy the barrier
    pthread_barrier_destroy(&barrier);
    this->addAcc(ret);
    return ret;
}

void *parallel_separation(void *args)
{
    input *inp = (input *)args;
    Bird *birdArr = inp->birdArr;
    Bird *currBird = inp->currBird;
    int size = inp->size;
    float radius = inp->radius;
    pthread_barrier_t *barrier = inp->barrier;
    Vector2 *res = inp->result;

    int numBirds = 0;
    Vector2 retDir = {0, 0};
    Vector2 currPos = currBird->getPos();
    Vector2 dirPos = {0, 0};
    
    for (int i = 0; i < size; i++)
    {
        float d = currBird->getDist(birdArr[i].getPos());
        if (d != 0 && d <= radius)
        {
            numBirds++;
            dirPos.x += (currPos.x - birdArr[i].getPos().x);
            dirPos.y += (currPos.y - birdArr[i].getPos().y);
            dirPos.x /= (d * d);
            dirPos.y /= (d * d);
        }
    }

    // if (numBirds > 0)
    // {
    //     retDir.x = retDir.x / numBirds;
    //     retDir.y = retDir.y / numBirds;
    // }

    pthread_barrier_wait(barrier);
    *res = retDir;
    // currBird->addAcc(retDir);
    return res;
}

Vector2 ParallelBird::separation(Bird *birds, int total_birds, float radius)
{
    Vector2 ret = {0, 0};
    int size = total_birds / numOfThreads;
    pthread_t threads[numOfThreads];
    Vector2 *results = new Vector2[numOfThreads];

    pthread_barrier_t barrier; /*  */
    pthread_barrier_init(&barrier, NULL, numOfThreads + 1);
    for (int j = 0; j < numOfThreads; j++)
    {
        input inp = {birds + j * size, this, size, radius, &barrier, &results[j]};
        pthread_create(&threads[j], NULL, parallel_separation, (void *)(&inp));
    }

    pthread_barrier_wait(&barrier);
    for (int j = 0; j < numOfThreads; j++)
    {
        pthread_join(threads[j], NULL);
    }

    for (int j = 0; j < numOfThreads; j++)
    {
        ret.x += results[j].x;
        ret.y += results[j].y;
    }

    // Destroy the barrier
    pthread_barrier_destroy(&barrier);
    this->addAcc(ret);
    return ret;
}

void *parallel_alignment(void *args)
{
    input *inp = (input *)args;
    Bird *birdArr = inp->birdArr;
    Bird *currBird = inp->currBird;
    int size = inp->size;
    float radius = inp->radius;
    pthread_barrier_t *barrier = inp->barrier;
    Vector2 *res = inp->result;

    int numBirds = 0;
    Vector2 retDir = {0, 0};
    // Vector2 currPos = currBird->getPos();

    for (int i = 0; i < size; i++)
    {
        float d = currBird->getDist(birdArr[i].getPos());
        if (d > 0.01 && d <= radius)
        {
            numBirds++;
            retDir.x += birdArr[i].getVel().x;
            retDir.y += birdArr[i].getVel().y;
        }
    }

    if (numBirds > 0)
    {
        retDir.x /= numBirds;
        retDir.y /= numBirds;
    }

    pthread_barrier_wait(barrier);
    *res = retDir;
    // currBird->addAcc(retDir);
    return res;
}

Vector2 ParallelBird::alignment(Bird *birds, int total_birds, float radius)
{
    Vector2 ret = {0, 0};
    int size = total_birds / numOfThreads;
    pthread_t threads[numOfThreads];
    Vector2 *results = new Vector2[numOfThreads];

    pthread_barrier_t barrier; /*  */
    pthread_barrier_init(&barrier, NULL, numOfThreads + 1);
    for (int j = 0; j < numOfThreads; j++)
    {
        input inp = {birds + j * size, this, size, radius, &barrier, &results[j]};
        pthread_create(&threads[j], NULL, parallel_alignment, (void *)(&inp));
    }

    pthread_barrier_wait(&barrier);
    for (int j = 0; j < numOfThreads; j++)
    {
        pthread_join(threads[j], NULL);
    }

    for (int j = 0; j < numOfThreads; j++)
    {
        ret.x += results[j].x;
        ret.y += results[j].y;
    }

    // Destroy the barrier
    pthread_barrier_destroy(&barrier);
    this->addAcc(ret);
    return ret;
}

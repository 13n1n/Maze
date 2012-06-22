#ifndef BALL_H
#define BALL_H

#include <utility>

#include "point.h"

#define X first
#define Y second

class ball: public point{
private:
    void __ball(float r);
public:
    float radius;
    ball();
    ball(float r);
    ball(float x, float y);
    ball(float x, float y, float r);
};

#endif // BALL_H

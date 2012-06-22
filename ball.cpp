#include "ball.h"

void ball::__ball(float r = 0.15){
    radius = r;
}

ball::ball(): point(){
    __ball();
}

ball::ball(float r): point(){
    __ball(r);
}

ball::ball(float x, float y): point(x, y){
    __ball();
}

ball::ball(float x, float y, float r): point(x, y){
    __ball(r);
}

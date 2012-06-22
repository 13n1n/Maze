#include "point.h"
#include <iostream>

float _abs(float _x){
    return (_x >= 0) ? _x : -_x;
}

float _max(float a, float b){
    return (a > b) ? a : b;
}

float _min(float a, float b){
    return (a < b) ? a : b;
}

point::point(float x, float y){
    m_coords.X = x;
    m_coords.Y = y;

    mass = 1;
}

point::point(){
    m_coords.X = 0;
    m_coords.Y = 0;

    mass = 1;
}

void point::setcoords(float x, float y){
    m_coords.X = x;
    m_coords.Y = y;
}

void point::move(float k = 1.f){
    m_coords.X += k*(m_pvector.X / (float)mass);
    m_coords.Y += k*(m_pvector.Y / (float)mass);

    m_pvector.X *= 0.95;
    m_pvector.Y *= 0.95;
}

void point::applysecondnewtonlaw(float k = 1.f){
    m_pvector.X = _max(-0.8f, _min(0.8f, m_pvector.X + k*m_fvector.X));
    m_pvector.Y = _max(-0.8f, _min(0.8f, m_pvector.Y + k*m_fvector.Y));
    //std::cerr << m_pvector.X << " " << m_pvector.Y << std::endl;
}

void point::setpulse(std::pair<float, float> v){
    m_pvector = v;
}

std::pair<float, float> point::getforce(){
    return m_fvector;
}

void point::addpulse(std::pair<float, float> v){
    m_pvector.X += v.X;
    m_pvector.Y += v.Y;
}

void point::setforce(std::pair<float, float> v){
    m_fvector = v;
}

void point::addforce(std::pair<float, float> v){
    m_fvector.X += v.X;
    m_fvector.Y += v.Y;
}

#define BOUNCE 0.8f

void point::bounce(std::pair<float, float> q){
    float _move = sqrt(m_pvector.X*m_pvector.X + m_pvector.Y*m_pvector.Y);
    float sina = q.Y / sqrt(q.X*q.X + q.Y*q.Y), cosa = q.X / sqrt(q.X*q.X + q.Y*q.Y),
            sinb = m_pvector.Y / _move, cosb = m_pvector.X / _move;
    float cosba = cosa*cosb + sina*sinb;
    float tx = _move*cosa*cosba, ty = _move*sina*cosba;
    float x = m_pvector.X - tx - BOUNCE*tx, y = m_pvector.Y - ty - BOUNCE*ty;
    m_pvector = std::pair<float, float> (x, y);
}

std::pair<float, float> point::getcoords(){
    return m_coords;
}

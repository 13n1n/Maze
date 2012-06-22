#ifndef POINT_H
#define POINT_H
#define X first
#define Y second

#include <utility>
#include <cmath>

float _abs(float _x);

float _max(float a, float b);

float _min(float a, float b);

class point{
    std::pair<float, float> m_coords;
    std::pair<float, float> m_pvector;
    std::pair<float, float> m_fvector;
public:
    point(float x, float y);
    point();

    unsigned mass;

    void move(float);
    void applysecondnewtonlaw(float);
    void bounce(std::pair<float, float>);
    void setpulse(std::pair<float, float>);
    void addpulse(std::pair<float, float>);
    void setforce(std::pair<float, float>);
    std::pair<float, float> getforce();
    void addforce(std::pair<float, float>);

    std::pair<float, float> getcoords();
    void setcoords(float x, float y);
};

#endif // POINT_H

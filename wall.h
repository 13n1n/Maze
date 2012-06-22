#ifndef WALL_H
#define WALL_H

#include <utility>

class Wall{
public:
    Wall(int x1, int y1, int x2, int y2);

    std::pair<float, float> coords1;
    std::pair<float, float> coords2;
};

#endif // WALL_H

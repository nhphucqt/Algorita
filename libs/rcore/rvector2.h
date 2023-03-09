#ifndef RVECTOR2_H
#define RVECTOR2_H

#include <cmath>
namespace raylib {
    #include "raylib.h"
}

template<typename T>
raylib::Vector2 toVector(const T &x, const T &y) {
    return raylib::Vector2{(float)(x),(float)(y)};
}

raylib::Vector2 operator - (const raylib::Vector2 &a, const raylib::Vector2 &b);
float getDist(const raylib::Vector2 &v1, const raylib::Vector2 &v2);

#endif
#ifndef RVECTOR2_H
#define RVECTOR2_H

#include <cmath>
namespace raylib {
    #include "raylib.h"
}
#include "../core/ccppclass.h"

template<typename T>
raylib::Vector2 toVector2(const T &x, const T &y) {
    return raylib::Vector2{(float)(x),(float)(y)};
}

raylib::Vector2 operator - (const raylib::Vector2 &a, const raylib::Vector2 &b);
raylib::Vector2 operator + (const raylib::Vector2 &a, const raylib::Vector2 &b);

raylib::Vector2 operator - (const TrVector &tv, const raylib::Vector2 &v);
raylib::Vector2 operator + (const TrVector &tv, const raylib::Vector2 &v);

float getDist(const raylib::Vector2 &v1, const raylib::Vector2 &v2);

#endif
#ifndef RVECTOR2_H
#define RVECTOR2_H

#include <assert.h>
#include <cmath>
// #include <iostream>
#include "../conf_raylib.h"

const raylib::Vector2 X_AXIS = raylib::Vector2{1, 0};
const raylib::Vector2 Y_AXIS = raylib::Vector2{0, 1};

template<typename T>
raylib::Vector2 toVector2(const T &x, const T &y) {
    return raylib::Vector2{(float)(x),(float)(y)};
}

raylib::Vector2 operator - (const raylib::Vector2 &a, const raylib::Vector2 &b);
raylib::Vector2 operator + (const raylib::Vector2 &a, const raylib::Vector2 &b);

raylib::Vector2 operator * (const raylib::Vector2 &v, double k);
raylib::Vector2 operator / (const raylib::Vector2 &v, double k);

double vsqrlen(const raylib::Vector2 &v);
double veclen(const raylib::Vector2 &v);
double dist(const raylib::Vector2 &a, const raylib::Vector2 &b);

double operator % (const raylib::Vector2 &a, const raylib::Vector2 &b);
double operator * (const raylib::Vector2 &a, const raylib::Vector2 &b);

double angle2(const raylib::Vector2 &a, const raylib::Vector2 &b); // radian
double angle(const raylib::Vector2 &a, const raylib::Vector2 &b); // radian

raylib::Vector2 trans(const raylib::Vector2 &v, double dist);

#endif
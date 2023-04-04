#ifndef RVECTOR2_H
#define RVECTOR2_H

#include <assert.h>
#include <cmath>
// #include <iostream>
#include "../conf_raylib.h"

const Vector2 Z_VECT = Vector2{0, 0};
const Vector2 X_AXIS = Vector2{1, 0};
const Vector2 Y_AXIS = Vector2{0, 1};

template<typename T>
Vector2 toVector2(const T &x, const T &y) {
    return Vector2{(float)(x), (float)(y)};
}

template<typename T>
Vector2 toSqrVector2(const T &x) {
    return Vector2{(float)(x), (float)(x)};
}

Vector2 resizeVector(const Vector2 &v, double k);

Vector2 revVector(const Vector2 &v);
Vector2 unitVector(const Vector2 &v);
Vector2 normVector(const Vector2 &v); // Counter-clockwise

Vector2 operator - (const Vector2 &a, const Vector2 &b);
Vector2 operator + (const Vector2 &a, const Vector2 &b);

Vector2 operator * (const Vector2 &v, double k);
Vector2 operator / (const Vector2 &v, double k);

double vsqrlen(const Vector2 &v);
double veclen(const Vector2 &v);
double dist(const Vector2 &a, const Vector2 &b);

double operator % (const Vector2 &a, const Vector2 &b);
double operator * (const Vector2 &a, const Vector2 &b);

bool CCW(const Vector2 &a, const Vector2 &b, const Vector2 &c);
bool CW(const Vector2 &a, const Vector2 &b, const Vector2 &c);

double angle2(const Vector2 &a, const Vector2 &b); // radian
double angle(const Vector2 &a, const Vector2 &b); // radian

Vector2 trans(const Vector2 &dir, double dist);
Vector2 trans(const Vector2 &v, const Vector2 &dir, double dist);
Vector2 rotate(const Vector2 &v, double a); // a rad

#endif
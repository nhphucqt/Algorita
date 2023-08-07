#include "rVector2.h"

Vector2 revVector(const Vector2 &v) {
    return Vector2{-v.x, -v.y};
}

Vector2 resizeVector(const Vector2 &v, double k) {
    return v / veclen(v) * k;
}

Vector2 unitVector(const Vector2 &v) {
    return v / veclen(v);
}

Vector2 normVector(const Vector2 &v) { // Counter-clockwise
    return Vector2{-v.y, v.x} / veclen(v);
}

Vector2 operator - (const Vector2 &a, const Vector2 &b) {
    return Vector2{a.x-b.x, a.y-b.y};
}

void operator -= (Vector2& a, const Vector2& b) {
    a = a - b;
}

Vector2 operator + (const Vector2 &a, const Vector2 &b) {
    return Vector2{a.x+b.x, a.y+b.y};
}

void operator += (Vector2& a, const Vector2& b) {
    a = a + b;
}

Vector2 operator * (const Vector2 &v, double k) {
    return Vector2{(float)(v.x * k), (float)(v.y * k)};
}

Vector2 operator / (const Vector2 &v, double k) {
    return Vector2{(float)(v.x / k), (float)(v.y / k)};
}

double vsqrlen(const Vector2 &v) {
    return v.x * v.x + v.y * v.y;
}

double veclen(const Vector2 &v) {
    return sqrt(vsqrlen(v));
}

double dist(const Vector2 &a, const Vector2 &b) {
    return veclen(a - b);
}

double operator % (const Vector2 &a, const Vector2 &b) {
    return a.x * b.y - a.y * b.x;
}
double operator * (const Vector2 &a, const Vector2 &b) {
    return a.x * b.x + a.y * b.y;
}

double angle2(const Vector2 &a, const Vector2 &b) { // radian
    return atan2(a % b, a * b);
}

double angle(const Vector2 &a, const Vector2 &b) { // radian
    return fabs(angle2(a, b));
}

bool CCW(const Vector2 &a, const Vector2 &b, const Vector2 &c) {
    return (b - a) % (c - b) > 0;
}

bool CW(const Vector2 &a, const Vector2 &b, const Vector2 &c) {
    return (b - a) % (c - b) < 0;
}


Vector2 trans(const Vector2 &dir, double dist) {
    return resizeVector(dir, dist);
}

Vector2 trans(const Vector2 &v, const Vector2 &dir, double dist) {
    return v + trans(dir, dist);
}

Vector2 rotate(const Vector2 &v, double a) { // a rad
    return Vector2{(float)(v.x*cos(a) - v.y*sin(a)), (float)(v.y*cos(a) + v.x*sin(a))};
}
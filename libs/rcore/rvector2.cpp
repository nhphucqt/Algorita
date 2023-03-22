#include "rvector2.h"

raylib::Vector2 revVector(const raylib::Vector2 &v) {
    return raylib::Vector2{-v.x, -v.y};
}

raylib::Vector2 resizeVector(const raylib::Vector2 &v, double k) {
    return v / veclen(v) * k;
}

raylib::Vector2 unitVector(const raylib::Vector2 &v) {
    return v / veclen(v);
}

raylib::Vector2 normVector(const raylib::Vector2 &v) { // Counter-clockwise
    return raylib::Vector2{-v.y, v.x} / veclen(v);
}

raylib::Vector2 operator - (const raylib::Vector2 &a, const raylib::Vector2 &b) {
    return raylib::Vector2{a.x-b.x, a.y-b.y};
}

raylib::Vector2 operator + (const raylib::Vector2 &a, const raylib::Vector2 &b) {
    return raylib::Vector2{a.x+b.x, a.y+b.y};
}

raylib::Vector2 operator * (const raylib::Vector2 &v, double k) {
    return raylib::Vector2{(float)(v.x * k), (float)(v.y * k)};
}

raylib::Vector2 operator / (const raylib::Vector2 &v, double k) {
    return raylib::Vector2{(float)(v.x / k), (float)(v.y / k)};
}

double vsqrlen(const raylib::Vector2 &v) {
    return v.x * v.x + v.y * v.y;
}

double veclen(const raylib::Vector2 &v) {
    return sqrt(vsqrlen(v));
}

double dist(const raylib::Vector2 &a, const raylib::Vector2 &b) {
    return veclen(a - b);
}

double operator % (const raylib::Vector2 &a, const raylib::Vector2 &b) {
    return a.x * b.y - a.y * b.x;
}
double operator * (const raylib::Vector2 &a, const raylib::Vector2 &b) {
    return a.x * b.x + a.y * b.y;
}

double angle2(const raylib::Vector2 &a, const raylib::Vector2 &b) { // radian
    return atan2(a % b, a * b);
}

double angle(const raylib::Vector2 &a, const raylib::Vector2 &b) { // radian
    return fabs(angle2(a, b));
}

bool CCW(const raylib::Vector2 &a, const raylib::Vector2 &b, const raylib::Vector2 &c) {
    return (b - a) % (c - b) > 0;
}

bool CW(const raylib::Vector2 &a, const raylib::Vector2 &b, const raylib::Vector2 &c) {
    return (b - a) % (c - b) < 0;
}


raylib::Vector2 trans(const raylib::Vector2 &dir, double dist) {
    return resizeVector(dir, dist);
}

raylib::Vector2 trans(const raylib::Vector2 &v, const raylib::Vector2 &dir, double dist) {
    return v + trans(dir, dist);
}

raylib::Vector2 rotate(const raylib::Vector2 &v, double a) { // a rad
    return raylib::Vector2{(float)(v.x*cos(a) - v.y*sin(a)), (float)(v.y*cos(a) + v.x*sin(a))};
}
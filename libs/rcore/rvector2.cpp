#include "rvector2.h"

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

raylib::Vector2 trans(const raylib::Vector2 &v, double dist) {
    // std::cerr << " >> " << veclen(v)  << '\n';
    return (v / veclen(v)) * dist;
}
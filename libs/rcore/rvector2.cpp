#include "rvector2.h"

raylib::Vector2 operator - (const raylib::Vector2 &a, const raylib::Vector2 &b) {
    return raylib::Vector2{a.x-b.x, a.y-b.y};
}

raylib::Vector2 operator + (const raylib::Vector2 &a, const raylib::Vector2 &b) {
    return raylib::Vector2{a.x+b.x, a.y+b.y};
}

raylib::Vector2 operator - (const TrVector &tv, const raylib::Vector2 &v) {
    return raylib::Vector2{(float)(*tv.x - v.x), (float)(*tv.y - v.y)};
}
raylib::Vector2 operator + (const TrVector &tv, const raylib::Vector2 &v) {
    return raylib::Vector2{(float)(*tv.x + v.x), (float)(*tv.y + v.y)};
}

float getDist(const raylib::Vector2 &v1, const raylib::Vector2 &v2) {
    return sqrt((v1.x-v2.x)*(v1.x-v2.x) + (v1.y-v2.y)*(v1.y-v2.y));
}
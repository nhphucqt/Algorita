#include "ccppclass.h"

TrVector::TrVector() {}

TrVector::TrVector(float* _x, float* _y) {
    x = _x; y = _y;
}

raylib::Vector2 TrVector::tv2() const {
    return raylib::Vector2{*x, *y};
}

raylib::Vector2 TrVector::operator - (const TrVector &v) const {
    return tv2() - v.tv2();
}

raylib::Vector2 TrVector::operator - (const raylib::Vector2 &v) const {
    return tv2() - v;
}

raylib::Vector2 TrVector::operator + (const raylib::Vector2 &v) const {
    return tv2() + v;
}
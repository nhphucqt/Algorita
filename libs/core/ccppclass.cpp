#include "ccppclass.h"

TrVector::TrVector() {}

TrVector::TrVector(float* _x, float* _y) {
    x = _x; y = _y;
}

Vector2 TrVector::tv2() const {
    return Vector2{*x, *y};
}

Vector2 TrVector::operator - (const TrVector &v) const {
    return tv2() - v.tv2();
}

Vector2 TrVector::operator - (const Vector2 &v) const {
    return tv2() - v;
}

Vector2 TrVector::operator + (const Vector2 &v) const {
    return tv2() + v;
}
#ifndef CCPPCLASS_H
#define CCPPCLASS_H

// DO NOT INCLUDE ANYTHING EXCEPT C++ lib and raylib.h and rcore

#include "../conf_raylib.h"
#include "../rcore/rvector2.h"

class TrVector { // Tracking vector | DO NOT USE 'new' operation, JUST FOR TRACKING
public:
    float* x;
    float* y;
    TrVector();
    TrVector(float* _x, float* _y);
    raylib::Vector2 tv2() const;
    raylib::Vector2 operator - (const TrVector &v) const;
    raylib::Vector2 operator - (const raylib::Vector2 &v) const;
    raylib::Vector2 operator + (const raylib::Vector2 &v) const;
};

#endif
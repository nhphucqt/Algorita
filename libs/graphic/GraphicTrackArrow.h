#ifndef GRAPHIC_TRACK_ARROW_H
#define GRAPHIC_TRACK_ARROW_H

#include <vector>

namespace raylib {
    #include "raylib.h"
}
#include "../global.h"
#include "../core/ccppclass.h"
#include "../rcore/rvector2.h"

class GraphicTrackArrow {
public:
    int lineWidth, headSize;
    raylib::Color lineColor, headColor;
    TrVector pA, pB;
    raylib::Vector2 tranA;
    raylib::Vector2 tranB;
    float transparent;
    bool isTrack;
    GraphicTrackArrow();
    GraphicTrackArrow(const TrVector &A, const TrVector &B, const raylib::Vector2 &tA, const raylib::Vector2 &tB);
    GraphicTrackArrow(float* Ax, float* Ay, float* Bx, float* By, const raylib::Vector2 &tA, const raylib::Vector2 &tB);
    GraphicTrackArrow(float* Ax, float* Ay, float* Bx, float* By, float tAx, float tAy, float tBx, float tBy);
    GraphicTrackArrow(float* Ax, float* Ay, float* Bx, float* By);
    void draw();
};

#endif

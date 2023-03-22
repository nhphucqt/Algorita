#ifndef GRAPHIC_TRACK_ARROW_H
#define GRAPHIC_TRACK_ARROW_H

#include <vector>
#include <functional>
#include <iostream>

#include "../conf_raylib.h"
#include "../global.h"
#include "../core/ccppclass.h"
#include "../core/ccppfunc.h"
#include "../rcore/rvector2.h"
#include "../rcore/rcolor.h"


class GraphicTrackArrow {
public:
    float lineWidth, headLength, headWidth;
    raylib::Color lineColor[2], headColor[2];
    TrVector pA, pB;
    float *sA, *sB;
    std::function<raylib::Vector2(raylib::Vector2)> ftA, ftB;
    float transparent;
    bool isTrack, isFocus;

    GraphicTrackArrow();
    GraphicTrackArrow(const TrVector &A, const TrVector &B, float* _sA, float* _sB, const std::function<raylib::Vector2(raylib::Vector2)> &_ftA, const std::function<raylib::Vector2(raylib::Vector2)> &_ftB);
    GraphicTrackArrow(float* Ax, float* Ay, float* Bx, float* By, float* _sA, float* _sB, const std::function<raylib::Vector2(raylib::Vector2)> &_ftA, const std::function<raylib::Vector2(raylib::Vector2)> &_ftB);
    GraphicTrackArrow(float* Ax, float* Ay, float* Bx, float* By, float* _sA, float* _sB);

    void vanish();
    void appear();
    void draw();
};

#endif

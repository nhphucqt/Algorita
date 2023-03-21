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


class GraphicTrackArrow {
public:
    int lineWidth, headSize;
    raylib::Color lineColor, headColor;
    TrVector pA, pB;
    float *sA, *sB;
    std::function<double(raylib::Vector2)> ftA, ftB;
    float transparent;
    bool isTrack;
    GraphicTrackArrow();
    GraphicTrackArrow(const TrVector &A, const TrVector &B, float* _sA, float* _sB, const std::function<double(raylib::Vector2)> &_ftA, const std::function<double(raylib::Vector2)> &_ftB);
    GraphicTrackArrow(float* Ax, float* Ay, float* Bx, float* By, float* _sA, float* _sB, const std::function<double(raylib::Vector2)> &_ftA, const std::function<double(raylib::Vector2)> &_ftB);
    GraphicTrackArrow(float* Ax, float* Ay, float* Bx, float* By, float* _sA, float* _sB);
    void draw();
};

#endif

#ifndef GRAPHIC_TRACK_ARROW_H
#define GRAPHIC_TRACK_ARROW_H

#include <vector>
#include <functional>
#include <iostream>

#include "../../conf_raylib.h"
#include "../../global.h"
#include "../../core/ccppclass.h"
#include "../../core/ccppfunc.h"
#include "../../rcore/rVector2.h"
#include "../../rcore/rColor.h"


class GraphicTrackArrow {
public:
    float lineWidth, headLength, headWidth;
    Color lineColor[2], headColor[2];
    TrVector pA, pB;
    Vector2 transA, transB;
    float *sA, *sB;
    std::function<Vector2(Vector2)> ftA, ftB;
    float transparent;
    float percent;
    float focusPercent;
    bool isTrack, isFocus;

    GraphicTrackArrow();
    GraphicTrackArrow(const TrVector &A, const TrVector &B, float* _sA, float* _sB, const std::function<Vector2(Vector2)> &_ftA, const std::function<Vector2(Vector2)> &_ftB);
    GraphicTrackArrow(float* Ax, float* Ay, float* Bx, float* By, float* _sA, float* _sB, const std::function<Vector2(Vector2)> &_ftA, const std::function<Vector2(Vector2)> &_ftB);
    GraphicTrackArrow(float* Ax, float* Ay, float* Bx, float* By, float* _sA, float* _sB);

    void vanish();
    void appear();
    void setTransparent(float _t);
    
    void focus();
    void unfocus();

    void minimize();
    void maximize();
    void setPercent(float _p);

    void draw();
};

#endif

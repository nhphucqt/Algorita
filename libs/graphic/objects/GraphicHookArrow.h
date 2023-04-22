#ifndef GRAPHIC_HOOK_ARROW_H
#define GRAPHIC_HOOK_ARROW_H

#include "../../conf_raylib.h"
#include "../../global.h"
#include "../../core/ccppclass.h"
#include "../../core/ccppfunc.h"
#include "../../rcore/rVector2.h"
#include "../../rcore/rColor.h"

class GraphicHookArrow {
public:
    Color slideColor, lineColor, headColor;
    Color *pSlideColor, *pLineColor, *pHeadColor;
    Vector2 p[Graphic::ARROW_NUM_JOIN];
    float transparent;
    float percent, slidePercent;
    bool isTrack, isAppear;

    GraphicHookArrow();
    GraphicHookArrow(float Ax, float Ay, float Bx, float By, float _sA, float _sB, const std::function<Vector2(Vector2)> &_ftA, const std::function<Vector2(Vector2)> &_ftB);

    void vanish();
    void appear();
    void setTransparent(float _t);

    std::pair<int, double> getPercent(double _percent);

    void minimize();
    void maximize();
    void setPercent(float _p);

    void resetColor();

    void draw();
};

#endif

#ifndef GRAPHIC_ARROW_H
#define GRAPHIC_ARROW_H

#include <vector>
#include <functional>
#include <iostream>

#include "../../conf_raylib.h"
#include "../../global.h"
#include "../../core/ccppclass.h"
#include "../../core/ccppfunc.h"
#include "../../rcore/rVector2.h"
#include "../../rcore/rColor.h"
#include "GraphicNode.h"


class GraphicArrow {
public:
    float lineWidth;
    Color slideColor, lineColor;
    Color *pSlideColor, *pLineColor;
    Vector2 pA, pB;
    Vector2 curA, curB;
    Vector2 transA, transB;
    float transparent;
    float percent, slidePercent;
    bool isAppear;

    GraphicArrow();
    GraphicArrow(float _lineWidth, Vector2 _pA, Vector2 _pB);
    GraphicArrow(Vector2 _pA, Vector2 _pB);
    GraphicArrow(float Ax, float Ay, float Bx, float By);

    void vanish();
    void appear();
    void setTransparent(float _t);

    void minimize();
    void maximize();
    void setPercent(float _p);

    void resetCurAB();

    bool isTransA();
    bool isTransB();

    void addTransA(Vector2 trans);
    void addTransB(Vector2 trans);

    void updateTransFromPos(std::pair<Vector2, Vector2> pp);

    void applyTransA();
    void applyTransB();
    void applyTransAB();

    void resetTransA();
    void resetTransB();
    void resetTrans();

    void resetColor();

    void draw();
};

#endif

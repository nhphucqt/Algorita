#include "GraphicHookArrow.h"

GraphicHookArrow::GraphicHookArrow() {
    resetColor();
    transparent = 0.0;
    percent = 0.0;
    slidePercent = 0.0;
    isTrack = isAppear = false;
}

GraphicHookArrow::GraphicHookArrow(float Ax, float Ay, float Bx, float By, float sA, float sB, const std::function<Vector2(Vector2)> &ftA, const std::function<Vector2(Vector2)> &ftB) : GraphicHookArrow() {
    Vector2 cA = toVector2(Ax, Ay) + toSqrVector2(sA/2);
    Vector2 cB = toVector2(Bx, By) + toSqrVector2(sB/2);

    Vector2 AB = cB - cA;
    Vector2 BA = cA - cB;

    if (fabs(dist(cA, cB)) < Geo::EPS) {
        AB = toVector2(1, 0);
        BA = toVector2(-1, 0);
    }

    p[1] = trans(cB, AB, Graphic::ARROW_SIDE_LENGTH);
    p[2] = trans(p[1], normVector(AB), Graphic::ARROW_VERT_LENGTH);
    p[4] = trans(cA, BA, Graphic::ARROW_SIDE_LENGTH);
    p[3] = trans(p[4], normVector(AB), Graphic::ARROW_VERT_LENGTH);

    p[0] = cB + ftB(AB);
    p[5] = trans(cA + ftA(BA), BA, Graphic::ARROW_HEAD_LENGTH);

    isTrack = true;
}

void GraphicHookArrow::vanish() {
    transparent = 0.0;
    isAppear = false;
}

void GraphicHookArrow::appear() {
    transparent = 1.0;
    isAppear = true;
}

void GraphicHookArrow::setTransparent(float _t) {
    transparent = _t;
}

std::pair<int, double> GraphicHookArrow::getPercent(double _percent) {
    double sum = 0;
    for (int i = 0; i < Graphic::ARROW_NUM_JOIN-1; ++i) {
        sum += dist(p[i], p[i+1]);
    }

    double pSum = sum * _percent;

    int pos = 0;
    for (; pos < Graphic::ARROW_NUM_JOIN-2; ++pos) {
        if (pSum < dist(p[pos], p[pos+1]) + Geo::EPS) {
            break;
        } else {
            pSum -= dist(p[pos], p[pos+1]);
        }
    }
    return std::make_pair(pos, pSum);
}

void GraphicHookArrow::minimize() {
    percent = 0.0;
}

void GraphicHookArrow::maximize() {
    percent = 1.0;
}

void GraphicHookArrow::setPercent(float _p) {
    percent = _p;
}

void GraphicHookArrow::resetColor() {
    pLineColor = &Theme::currTheme.ARROW_LINE;
    pSlideColor = &Theme::currTheme.ARROW_LINE;
    pHeadColor = &Theme::currTheme.ARROW_HEAD;
    slidePercent = 0.0;
}

void GraphicHookArrow::draw() {
    if (!isTrack || !isAppear || percent == 0.0) {
        return;
    }

    int pos;
    double pSum;
    std::tie(pos, pSum) = getPercent(percent);

    Vector2 pCentr = trans(p[pos], p[pos+1]-p[pos], pSum);
    Vector2 aHead = trans(pCentr, p[pos+1]-p[pos], Graphic::ARROW_HEAD_LENGTH);
    Vector2 pLeft = trans(pCentr, normVector(p[pos+1]-p[pos]), Graphic::ARROW_HEAD_WIDTH / 2);
    Vector2 pRight = trans(pCentr, normVector(p[pos]-p[pos+1]), Graphic::ARROW_HEAD_WIDTH / 2);

    assert(CCW(pLeft, pRight, aHead));

    Color line = TRNSP(pLineColor == nullptr ? lineColor : *pLineColor, transparent);
    Color slide = TRNSP(pSlideColor == nullptr ? slideColor : *pSlideColor, transparent);

    for (int i = 0; i < pos; ++i) {
        DrawLineEx(p[i], trans(p[i+1], p[i+1]-p[i], Graphic::ARROW_LINE_WIDTH / 2), Graphic::ARROW_LINE_WIDTH, line);
    }
    DrawLineEx(p[pos], pCentr, Graphic::ARROW_LINE_WIDTH, line);


    std::tie(pos, pSum) = getPercent(slidePercent);
    for (int i = 0; i < pos; ++i) {
        DrawLineEx(p[i], trans(p[i+1], p[i+1]-p[i], Graphic::ARROW_LINE_WIDTH / 2), Graphic::ARROW_LINE_WIDTH, slide);
    }
    DrawLineEx(p[pos], trans(p[pos], p[pos+1]-p[pos], pSum), Graphic::ARROW_LINE_WIDTH, slide);

    DrawTriangle(pRight, pLeft, aHead, TRNSP(pHeadColor == nullptr ? headColor : *pHeadColor, transparent));
}
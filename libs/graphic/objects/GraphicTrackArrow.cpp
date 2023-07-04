#include "GraphicTrackArrow.h"

GraphicTrackArrow::GraphicTrackArrow() {
    resetColor();
    transparent = 0.0; // vanish at first
    percent = 0.0;
    slidePercent = 0.0;
    isTrack = isAppear = false;
}

GraphicTrackArrow::GraphicTrackArrow(float _lineWidth, float _headWidth, float _headLength, const TrVector &A, const TrVector &B, float* _sA, float* _sB, const std::function<Vector2(Vector2)> &_ftA, const std::function<Vector2(Vector2)> &_ftB): GraphicTrackArrow() {
    lineWidth = _lineWidth;
    headWidth = _headWidth;
    headLength = _headLength;
    pA = A; pB = B;
    sA = _sA; sB = _sB;
    ftA = _ftA;
    ftB = _ftB;
    isTrack = true;
}

GraphicTrackArrow::GraphicTrackArrow(float _lineWidth, float _headWidth, float _headLength, float* Ax, float* Ay, float* Bx, float* By, float* _sA, float* _sB, const std::function<Vector2(Vector2)> &_ftA, const std::function<Vector2(Vector2)> &_ftB)
: GraphicTrackArrow(_lineWidth, _headWidth, _headLength, TrVector(Ax,Ay), TrVector(Bx,By), _sA, _sB, _ftA, _ftB) {}

GraphicTrackArrow::GraphicTrackArrow(const TrVector &A, const TrVector &B, float* _sA, float* _sB, const std::function<Vector2(Vector2)> &_ftA, const std::function<Vector2(Vector2)> &_ftB)
: GraphicTrackArrow(Graphic::ARROW_LINE_WIDTH, Graphic::ARROW_HEAD_WIDTH, Graphic::ARROW_HEAD_LENGTH, A, B, _sA, _sB, _ftA, _ftB) {}

GraphicTrackArrow::GraphicTrackArrow(float* Ax, float* Ay, float* Bx, float* By, float* _sA, float* _sB, const std::function<Vector2(Vector2)> &_ftA, const std::function<Vector2(Vector2)> &_ftB)
: GraphicTrackArrow(TrVector(Ax,Ay), TrVector(Bx,By), _sA, _sB, _ftA, _ftB) {}

GraphicTrackArrow::GraphicTrackArrow(float* Ax, float* Ay, float* Bx, float* By, float* _sA, float* _sB) 
: GraphicTrackArrow(Ax, Ay, Bx, By, _sA, _sB, cf::outerNull, cf::outerNull) {}

void GraphicTrackArrow::vanish() {
    transparent = 0.0;
    isAppear = false;
}

void GraphicTrackArrow::appear() {
    transparent = 1.0;
    isAppear = true;
}

void GraphicTrackArrow::setTransparent(float _t) {
    transparent = _t;
}

void GraphicTrackArrow::minimize() {
    percent = 0.0;
}

void GraphicTrackArrow::maximize() {
    percent = 1.0;
}

void GraphicTrackArrow::setPercent(float _p) {
    percent = _p;
}

void GraphicTrackArrow::copyAttributes(GraphicTrackArrow* arrow) {
    slideColor = arrow->slideColor;
    lineColor = arrow->lineColor;
    headColor = arrow->headColor;
    pSlideColor = arrow->pSlideColor;
    pLineColor = arrow->pLineColor;
    pHeadColor = arrow->pHeadColor;
    transparent = arrow->transparent;
    percent = arrow->percent;
    slidePercent = arrow->slidePercent;
    isTrack = arrow->isTrack;
    isAppear = arrow->isAppear;
}

void GraphicTrackArrow::resetColor() {
    pLineColor = &Theme::currTheme.ARROW_LINE;
    pSlideColor = &Theme::currTheme.ARROW_LINE;
    pHeadColor = &Theme::currTheme.ARROW_HEAD;
    slidePercent = 0.0;
}

void GraphicTrackArrow::draw() {
    if (!isTrack || transparent == 0.0 || percent == 0.0) {
        return;
    }
    Vector2 cA = pA + toVector2(*sA/2, *sA/2);
    Vector2 cB = pB + toVector2(*sB/2, *sB/2);
    if (dist(cA, cB) <= *sA/2 + *sB/2) {
        return;
    }
    Vector2 AB = cB - cA;
    Vector2 BA = cA - cB;
    Vector2 newA = cA + ftA(AB);
    Vector2 newB = cB + ftB(BA);
    // transform newA & newB
    newA = newA + transA;
    newB = newB + transB;
    // update AB & BA
    AB = newB - newA;
    BA = newA - newB;

    newB = trans(newA, AB, percent * dist(newA, newB));

    // create arrow head
    Vector2 pCentr = trans(newB, BA, headLength);
    Vector2 pLeft = trans(pCentr, normVector(AB), headWidth / 2);
    Vector2 pRight = trans(pCentr, normVector(BA), headWidth / 2);

    assert(CCW(pLeft, pRight, newB));

    DrawLineEx(newA, pCentr, lineWidth, TRNSP(pLineColor == nullptr ? lineColor : *pLineColor, transparent));
    DrawLineEx(newA, newA + ((pCentr - newA) * slidePercent), lineWidth, TRNSP(pSlideColor == nullptr ? slideColor : *pSlideColor, transparent));
    DrawTriangle(pRight, pLeft, newB, TRNSP(pHeadColor == nullptr ? headColor : *pHeadColor, transparent));
}


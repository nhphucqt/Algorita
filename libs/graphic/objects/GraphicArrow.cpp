#include "GraphicArrow.h"

GraphicArrow::GraphicArrow() {
    resetColor();
    transparent = 0.0; // vanish at first
    percent = 0.0;
    slidePercent = 0.0;
    pA = pB = Z_VECT;
    curA = curB = Z_VECT;
    isAppear = false;
}

GraphicArrow::GraphicArrow(float _lineWidth, Vector2 _pA, Vector2 _pB): GraphicArrow() {
    lineWidth = _lineWidth;
    pA = curA = _pA; 
    pB = curB = _pB;
}

GraphicArrow::GraphicArrow(Vector2 _pA, Vector2 _pB)
: GraphicArrow(Graphic::ARROW_LINE_WIDTH, _pA, _pB) {}

GraphicArrow::GraphicArrow(float Ax, float Ay, float Bx, float By)
: GraphicArrow(Vector2{Ax, Ay}, Vector2{Bx, By}) {}

void GraphicArrow::vanish() {
    transparent = 0.0;
    isAppear = false;
}

void GraphicArrow::appear() {
    transparent = 1.0;
    isAppear = true;
}

void GraphicArrow::setTransparent(float _t) {
    transparent = _t;
}

void GraphicArrow::minimize() {
    percent = 0.0;
}

void GraphicArrow::maximize() {
    percent = 1.0;
}

void GraphicArrow::setPercent(float _p) {
    percent = _p;
}

void GraphicArrow::resetCurAB() {
    curA = pA;
    curB = pB;
}

bool GraphicArrow::isTransA() {
    return fabs(transA.x) > Geo::EPS || fabs(transA.y) > Geo::EPS;
}

bool GraphicArrow::isTransB() {
    return fabs(transB.x) > Geo::EPS || fabs(transB.y) > Geo::EPS;
}

void GraphicArrow::addTransA(Vector2 trans) {
    transA += trans;
}
void GraphicArrow::addTransB(Vector2 trans) {
    transB += trans;
}

void GraphicArrow::updateTransFromPos(std::pair<Vector2, Vector2> pp) {
    transA = pp.first - curA;
    transB = pp.second - curB;
}

void GraphicArrow::applyTransA() {
    curA += transA;
}

void GraphicArrow::applyTransB() {
    curB += transB;
}

void GraphicArrow::applyTransAB() {
    applyTransA();
    applyTransB();
}


void GraphicArrow::resetTransA() {
    transA = Z_VECT;
}

void GraphicArrow::resetTransB() {
    transB = Z_VECT;
}

void GraphicArrow::resetTrans() {
    resetTransA();
    resetTransB();
}

void GraphicArrow::copyAttributes(GraphicArrow* arrow) {
    lineWidth = arrow->lineWidth;
    slideColor = arrow->slideColor;
    lineColor = arrow->lineColor;
    pSlideColor = arrow->pSlideColor;
    pLineColor = arrow->pLineColor;
    transparent = arrow->transparent;
    percent = arrow->percent;
    slidePercent = arrow->slidePercent;
    isAppear = arrow->isAppear;
}

void GraphicArrow::resetColor() {
    pLineColor = &Theme::currTheme.ARROW_LINE;
    pSlideColor = &Theme::currTheme.ARROW_LINE;
    slidePercent = 0.0;
}

void GraphicArrow::draw() {
    if (transparent == 0.0 || percent == 0.0) {
        return;
    }

    Vector2 AB = pB - pA;
    Vector2 BA = pA - pB;

    Vector2 aHead = pA + ((pB - pA) * percent);

    // create arrow head

    DrawLineEx(pA, aHead, lineWidth, TRNSP(pLineColor == nullptr ? lineColor : *pLineColor, transparent));
    DrawLineEx(pA, pA + ((aHead - pA) * slidePercent), lineWidth, TRNSP(pSlideColor == nullptr ? slideColor : *pSlideColor, transparent));
}


#include "GraphicTrackArrow.h"

GraphicTrackArrow::GraphicTrackArrow() {
    lineWidth = Graphic::ARROW_LINE_WIDTH;
    headLength = Graphic::ARROW_HEAD_LENGTH;
    headWidth = Graphic::ARROW_HEAD_WIDTH;
    lineColor[0] = Color::ARROW_LINE;
    lineColor[1] = Color::ARROW_LINE_FOCUS;
    headColor[0] = Color::ARROW_HEAD;
    headColor[1] = Color::ARROW_HEAD_FOCUS;
    pA = pB = TrVector(nullptr, nullptr);
    sA = sB = 0;
    isTrack = false;
    isFocus = false;
    transparent = 0.0; // vanish at first
}

GraphicTrackArrow::GraphicTrackArrow(const TrVector &A, const TrVector &B, float* _sA, float* _sB, const std::function<raylib::Vector2(raylib::Vector2)> &_ftA, const std::function<raylib::Vector2(raylib::Vector2)> &_ftB) : GraphicTrackArrow() {
    pA = A; pB = B;
    sA = _sA; sB = _sB;
    ftA = _ftA;
    ftB = _ftB;
    isTrack = true;
}

GraphicTrackArrow::GraphicTrackArrow(float* Ax, float* Ay, float* Bx, float* By, float* _sA, float* _sB, const std::function<raylib::Vector2(raylib::Vector2)> &_ftA, const std::function<raylib::Vector2(raylib::Vector2)> &_ftB)
: GraphicTrackArrow(TrVector(Ax,Ay), TrVector(Bx,By), _sA, _sB, _ftA, _ftB) {}

GraphicTrackArrow::GraphicTrackArrow(float* Ax, float* Ay, float* Bx, float* By, float* _sA, float* _sB) 
: GraphicTrackArrow(Ax, Ay, Bx, By, _sA, _sB, cf::outerNull, cf::outerNull) {}

void GraphicTrackArrow::vanish() {
    transparent = 0.0;
}

void GraphicTrackArrow::appear() {
    transparent = 1.0;
}

void GraphicTrackArrow::draw() {
    if (transparent == 0.0) {
        return;
    }
    if (isTrack) {
        raylib::Vector2 cA = pA + toVector2(*sA/2, *sA/2);
        raylib::Vector2 cB = pB + toVector2(*sB/2, *sB/2);
        if (dist(cA, cB) <= *sA/2 + *sB/2) {
            return;
        }
        // if (fabs(dist(cA, cB)) < Geo::EPS) {
        //     return;
        // }
        raylib::Vector2 AB = cB - cA;
        raylib::Vector2 BA = cA - cB;

        raylib::Vector2 newA = cA + ftA(AB);
        raylib::Vector2 newB = cB + ftB(BA);

        raylib::Vector2 pCentr = trans(newB, BA, headLength);
        raylib::Vector2 pLeft = trans(pCentr, normVector(AB), headWidth/2);
        raylib::Vector2 pRight = trans(pCentr, normVector(BA), headWidth/2);

        assert(CCW(pLeft, pRight, newB));
        raylib::DrawLineEx(newA, pCentr, lineWidth, TRNSP(lineColor[isFocus], transparent));
        raylib::DrawTriangle(pRight, pLeft, newB, TRNSP(headColor[isFocus], transparent));
    }
}
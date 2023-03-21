#include "GraphicTrackArrow.h"

GraphicTrackArrow::GraphicTrackArrow() {
    lineWidth = Graphic::ARROW_LINE_WIDTH;
    headLength = Graphic::ARROW_HEAD_LENGTH;
    headWidth = Graphic::ARROW_HEAD_WIDTH;
    lineColor = Color::ARROW_LINE;
    headColor = Color::ARROW_HEAD;
    pA = pB = TrVector(nullptr, nullptr);
    sA = sB = 0;
    isTrack = false;
    transparent = 1.0;
}

GraphicTrackArrow::GraphicTrackArrow(const TrVector &A, const TrVector &B, float* _sA, float* _sB, const std::function<double(raylib::Vector2)> &_ftA, const std::function<double(raylib::Vector2)> &_ftB) : GraphicTrackArrow() {
    pA = A; pB = B;
    sA = _sA; sB = _sB;
    ftA = _ftA;
    ftB = _ftB;
    isTrack = true;
}

GraphicTrackArrow::GraphicTrackArrow(float* Ax, float* Ay, float* Bx, float* By, float* _sA, float* _sB, const std::function<double(raylib::Vector2)> &_ftA, const std::function<double(raylib::Vector2)> &_ftB)
: GraphicTrackArrow(TrVector(Ax,Ay), TrVector(Bx,By), _sA, _sB, _ftA, _ftB) {}

GraphicTrackArrow::GraphicTrackArrow(float* Ax, float* Ay, float* Bx, float* By, float* _sA, float* _sB) 
: GraphicTrackArrow(Ax, Ay, Bx, By, _sA, _sB, cf::outerNull, cf::outerNull) {}

void GraphicTrackArrow::draw() {
    if (isTrack) {
        // A -> B
        // AB = B - A -> A + trans(AB, ftA) 
        // BA = A - B -> B + trans(BA, ftB)
        // std::cerr << " >> " << ftA(pB - pA) << '\n';
        raylib::Vector2 cA = pA + toVector2(*sA/2, *sA/2);
        raylib::Vector2 cB = pB + toVector2(*sB/2, *sB/2);
        if (dist(cA, cB) <= *sA/2 + *sB/2) {
            return;
        }

        raylib::Vector2 AB = cB - cA;
        raylib::Vector2 BA = cA - cB;

        raylib::Vector2 newA = trans(cA, AB, ftA(AB));
        raylib::Vector2 newB = trans(cB, BA, ftB(BA));

        raylib::Vector2 pCentr = trans(newB, BA, headLength);
        raylib::Vector2 pLeft = trans(pCentr, normVector(AB), headWidth/2);
        raylib::Vector2 pRight = trans(pCentr, normVector(BA), headWidth/2);

        // std::cerr << "(" << pLeft.x << ',' << pLeft.y << ") (" << pRight.x << "," << pRight.y << ") (" << pCentr.x << "," << pCentr.y << ")" << '\n';

        assert(CCW(pLeft, pRight, newB));

        // std::cerr << newA.x << ' ' << newA.y << ' ' << *pA.x << ' ' << *pA.y << ' ' << dist(newA, pA.tv2()) << '\n';
        raylib::DrawLineEx(newA, newB, lineWidth, lineColor);
        // raylib::DrawTriangle(pLeft, pRight, pCentr, headColor);
        raylib::DrawTriangle(pRight, pLeft, newB, headColor);

    }
}
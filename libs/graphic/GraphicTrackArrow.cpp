#include "GraphicTrackArrow.h"

GraphicTrackArrow::GraphicTrackArrow() {
    lineWidth = Graphic::ARROW_LINE_WIDTH;
    headSize = Graphic::ARROW_HEAD_SIZE;
    lineColor = Color::ARROW_LINE;
    headColor = Color::ARROW_HEAD;
    pA = pB = TrVector(nullptr, nullptr);
    sA = sB = 0;
    isTrack = false;
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
        std::cerr << " >> " << ftA(pB - pA) << '\n';
        raylib::Vector2 cA = pA + toVector2(*sA/2, *sA/2);
        raylib::Vector2 cB = pB + toVector2(*sB/2, *sB/2);
        if (dist(cA, cB) <= *sA/2 + *sB/2) {
            return;
        }
        raylib::Vector2 newA = cA + trans(cB - cA, ftA(cB - cA));
        raylib::Vector2 newB = cB + trans(cA - cB, ftB(cA - cB));
        std::cerr << newA.x << ' ' << newA.y << ' ' << *pA.x << ' ' << *pA.y << ' ' << dist(newA, pA.tv2()) << '\n';
        raylib::DrawLineEx(newA, newB, lineWidth, lineColor);
    }
}
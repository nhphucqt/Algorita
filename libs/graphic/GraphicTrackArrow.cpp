#include "GraphicTrackArrow.h"

GraphicTrackArrow::GraphicTrackArrow() {
    lineWidth = Graphic::ARROW_LINE_WIDTH;
    headSize = Graphic::ARROW_HEAD_SIZE;
    lineColor = Color::ARROW_LINE;
    headColor = Color::ARROW_HEAD;
    pA = pB = TrVector(nullptr, nullptr);
    isTrack = false;
}

GraphicTrackArrow::GraphicTrackArrow(const TrVector &A, const TrVector &B, const raylib::Vector2 &tA, const raylib::Vector2 &tB) : GraphicTrackArrow() {
    pA = A; pB = B;
    tranA = tA;
    tranB = tB;
    isTrack = true;
}

GraphicTrackArrow::GraphicTrackArrow(float* Ax, float* Ay, float* Bx, float* By, const raylib::Vector2 &tA, const raylib::Vector2 &tB) 
: GraphicTrackArrow(TrVector(Ax,Ay), TrVector(Bx,By), tA, tB) {}

GraphicTrackArrow::GraphicTrackArrow(float* Ax, float* Ay, float* Bx, float* By, float tAx, float tAy, float tBx, float tBy) 
: GraphicTrackArrow(Ax, Ay, Bx, By, raylib::Vector2{tAx,tAy}, raylib::Vector2{tBx,tBy}) {}

GraphicTrackArrow::GraphicTrackArrow(float* Ax, float* Ay, float* Bx, float* By) 
: GraphicTrackArrow(Ax, Ay, Bx, By, 0, 0, 0, 0) {}

void GraphicTrackArrow::draw() {
    if (isTrack) {
        raylib::DrawLineEx(pA + tranA, pB + tranB, lineWidth, lineColor);
    }
}
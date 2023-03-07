#include "nodelib.h"

#include "nodelib.h"

GraphicNode::GraphicNode() {}

GraphicNode::GraphicNode(double _x, double _y, int _s, raylib::Color _cc, raylib::Color _tc, bool _sqr) {
    lx = x = _x; ly = y = _y; size = _s;
    currColor = _cc;
    trueColor = _tc;
    isSqr = _sqr;
}

void GraphicNode::draw() {
    if (isSqr) {
        raylib::DrawRectangle(x, y, size, size, currColor);
    } else {
        double radius = (double) size / 2.0;
        raylib::DrawCircleV(raylib::Vector2{(float)(x+radius),(float)(y+radius)}, radius, currColor);
    }
}
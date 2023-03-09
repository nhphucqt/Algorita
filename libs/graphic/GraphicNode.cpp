#include "GraphicNode.h"

GraphicNode::GraphicNode() {}

GraphicNode::GraphicNode(double _x, double _y, int _s, bool _sqr, int _v) {
    lx = x = _x; ly = y = _y; size = _s;
    bsize = Graphic::NODE_BORDER_WIDTH;
    backColor[0] = Color::NODE_BACKGROUND;
    backColor[1] = Color::NODE_BACKGROUND_FOCUS;
    foreColor[0] = Color::NODE_FOREGROUND;
    foreColor[1] = Color::NODE_FOREGROUND_FOCUS;
    bordColor[0] = Color::NODE_BORDER;
    bordColor[1] = Color::NODE_BORDER_FOCUS;
    isSqr = _sqr;
    isFocus = false;
    val = _v;
    assert(Core::NODE_MIN_VALUE <= val && val <= Core::NODE_MAX_VALUE);
    text = StyledText(val, &Font::jb_mono_med_36);
}

void GraphicNode::draw() {
    if (isSqr) {
        raylib::DrawRectangle(x, y, size, size, TRNSP(backColor[isFocus], transparent));
        raylib::DrawRectangleLinesEx(raylib::Rectangle{(float)x,(float)y,(float)size,(float)size}, bsize, TRNSP(bordColor[isFocus], transparent));
    } else {
        double radius = (double) size / 2.0;
        raylib::Vector2 center = raylib::Vector2{(float)(x+radius),(float)(y+radius)};
        // raylib::DrawCircleV(center, radius, TRNSP(bordColor[isFocus], transparent));
        raylib::DrawCircleV(center, radius, TRNSP(backColor[isFocus], transparent));
        for (double r = radius; r > radius-bsize; r-=0.5) {
            raylib::DrawCircleLines(center.x, center.y, r, TRNSP(bordColor[isFocus], transparent));
        }
    }
    text.draw(toVector(x+(size-text.dim.x)/2, y+(size-text.dim.y)/2), TRNSP(foreColor[isFocus], transparent));
}


#include "GraphicNode.h"

GraphicNode::GraphicNode() {
    bsize = Graphic::NODE_BORDER_WIDTH;
    backColor[0] = Color::NODE_BACKGROUND;
    backColor[1] = Color::NODE_BACKGROUND_FOCUS;
    foreColor[0] = Color::NODE_FOREGROUND;
    foreColor[1] = Color::NODE_FOREGROUND_FOCUS;
    bordColor[0] = Color::NODE_BORDER;
    bordColor[1] = Color::NODE_BORDER_FOCUS;
    isFocus = false;
    outerShapeIn = outerShapeOut = cf::outerNull;
    transparent = 1.0;
}

GraphicNode::GraphicNode(float _x, float _y, float _s, bool _sqr, int _v) : GraphicNode() {
    lx = x = _x; 
    ly = y = _y; 
    size = _s;
    isSqr = _sqr;
    val = _v;
    assert(Core::NODE_MIN_VALUE <= val && val <= Core::NODE_MAX_VALUE);
    text = StyledText(val, Font::defaultFont);
}

raylib::Vector2 GraphicNode::getCenter() const {
    return raylib::Vector2{x+size/2, y+size/2};
}

void GraphicNode::vanish() {
    transparent = 0.0;
}

void GraphicNode::appear() {
    transparent = 1.0;
}

void GraphicNode::setValue(int x) {
    assert(Core::NODE_MIN_VALUE <= val && val <= Core::NODE_MAX_VALUE);
    val = x;
    text = StyledText(val, Font::defaultFont);
}

void GraphicNode::draw() {
    if (isSqr) {
        raylib::DrawRectangle(x, y, size, size, TRNSP(backColor[isFocus], transparent));
        raylib::DrawRectangleLinesEx(raylib::Rectangle{x,y,size,size}, bsize, TRNSP(bordColor[isFocus], transparent));
    } else {
        float radius = size / 2.0;
        raylib::Vector2 center = raylib::Vector2{(float)(x+radius),(float)(y+radius)};
        raylib::DrawCircleV(center, radius, TRNSP(backColor[isFocus], transparent));
        raylib::DrawRing(center, radius-bsize, radius, 0, 360, 36, TRNSP(bordColor[isFocus], transparent));
    }
    text.draw(toVector2(x+(size-text.dim.x)/2, y+(size-text.dim.y)/2), TRNSP(foreColor[isFocus], transparent));
}


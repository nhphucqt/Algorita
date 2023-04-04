#include "GraphicNode.h"

GraphicNode::GraphicNode() {
    bsize = Graphic::NODE_BORDER_WIDTH;
    backColor[0] = Gcolor::NODE_BACKGROUND;
    backColor[1] = Gcolor::NODE_BACKGROUND_FOCUS;
    foreColor[0] = Gcolor::NODE_FOREGROUND;
    foreColor[1] = Gcolor::NODE_FOREGROUND_FOCUS;
    bordColor[0] = Gcolor::NODE_BORDER;
    bordColor[1] = Gcolor::NODE_BORDER_FOCUS;
    isFocus = false;
    isFocusBorder = false;
    outerShapeIn = outerShapeOut = cf::outerNull;
    transparent = 0.0; // vanish at first
    focusPercent = 0.0; // unfocus at first
    focusBorderPercent = 0.0; // unfocus at first
}

GraphicNode::GraphicNode(float _x, float _y, float _s, bool _sqr, int _v) : GraphicNode() {
    lx = x = _x;
    ly = y = _y;
    size = _s;
    isSqr = _sqr;
    assert(Core::NODE_MIN_VALUE <= _v && _v <= Core::NODE_MAX_VALUE);
    nVal = _v;
    val = StyledText(_v, Gfont::defaultFont);
}

Vector2 GraphicNode::getCenter() const {
    return Vector2{x+size/2, y+size/2};
}

void GraphicNode::vanish() {
    transparent = 0.0;
}

void GraphicNode::appear() {
    transparent = 1.0;
}

void GraphicNode::focus() {
    focusPercent = 1.0;
    isFocus = true;
}

void GraphicNode::unfocus() {
    focusPercent = 0.0;
    isFocus = false;
}

void GraphicNode::focusBorder() {
    focusBorderPercent = 1.0;
    isFocusBorder = true;
}

void GraphicNode::unfocusBorder() {
    focusBorderPercent = 0.0;
    isFocusBorder = false;
}

void GraphicNode::setValue(int x) {
    assert(Core::NODE_MIN_VALUE <= x && x <= Core::NODE_MAX_VALUE);
    val = StyledText(x, Gfont::defaultFont);
}

void GraphicNode::draw() {
    if (transparent == 0.0) {
        return;
    }
    Color background = TRNSP(TRANSCOLOR(backColor[0], backColor[1], focusPercent), transparent);
    Color foreground = TRNSP(TRANSCOLOR(foreColor[0], foreColor[1], focusPercent), transparent);
    Color border = TRNSP(TRANSCOLOR(bordColor[0], bordColor[1], focusBorderPercent), transparent);
    if (isSqr) {
        DrawRectangle(x, y, size, size, background);
        DrawRectangleLinesEx(Rectangle{x,y,size,size}, bsize, border);
    } else {
        float radius = size / 2.0;
        Vector2 center = Vector2{(float)(x+radius),(float)(y+radius)};
        DrawCircleV(center, radius, background);
        DrawRing(center, radius-bsize, radius, 0, 360, 36, border);
    }
    val.draw(toVector2(x+(size-val.dim.x)/2, y+(size-val.dim.y)/2), foreground);
}


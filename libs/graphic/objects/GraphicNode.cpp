#include "GraphicNode.h"

GraphicNode::GraphicNode() {
    bsize = Graphic::NODE_BORDER_WIDTH;
    resetColor();
    isAppear = false;
    outerShapeIn = outerShapeOut = cf::outerNull;
    transparent = 0.0; // vanish at first
    sub = StyledText("", Gfont::defaultFont, Graphic::NODE_SUBTEXT_PADDING);
}

GraphicNode::GraphicNode(float _x, float _y, float _s, bool _sqr, int _v, const std::string &_subtext) : GraphicNode() {
    lx = x = _x;
    ly = y = _y;
    size = _s;
    isSqr = _sqr;
    assert(Core::NODE_MIN_VALUE <= _v && _v <= Core::NODE_MAX_VALUE);
    nVal = _v;
    val = StyledText(_v, Gfont::defaultFont);
    sub.assign(_subtext);
}

GraphicNode::GraphicNode(float _x, float _y, float _s, bool _sqr, int _v) : GraphicNode(_x, _y, _s, _sqr, _v, "") {}

Vector2 GraphicNode::getCenter() const {
    return Vector2{x+size/2, y+size/2};
}

void GraphicNode::vanish() {
    transparent = 0.0;
    isAppear = false;
}

void GraphicNode::appear() {
    transparent = 1.0;
    isAppear = true;
}

void GraphicNode::transform(int Tx, int Ty) {
    lx = (x += Tx);
    ly = (y += Ty);
}

void GraphicNode::displace(int Dx, int Dy) {
    lx = x = Dx;
    ly = y = Dy;
}

void GraphicNode::setValue(int x) {
    assert(Core::NODE_MIN_VALUE <= x && x <= Core::NODE_MAX_VALUE);
    val = StyledText(x, Gfont::defaultFont);
}

void GraphicNode::setSubText(const std::string &_subtext) {
    sub.assign(_subtext);
}

void GraphicNode::resetColor() {
    pBackColor = &Gcolor::NODE_BACKGROUND;
    pForeColor = &Gcolor::NODE_FOREGROUND;
    pBordColor = &Gcolor::NODE_BORDER;
}

void GraphicNode::draw() {
    if (transparent == 0.0) {
        return;
    }
    Color background = pBackColor == nullptr ? TRNSP(backColor, transparent) : TRNSP(*pBackColor, transparent);
    Color foreground = pForeColor == nullptr ? TRNSP(foreColor, transparent) : TRNSP(*pForeColor, transparent);
    Color border = pBordColor == nullptr ? TRNSP(bordColor, transparent) : TRNSP(*pBordColor, transparent);
    Color subtext = TRNSP(Gcolor::NODE_SUBTEXT, transparent);
    if (isSqr) {
        DrawRectangle(x, y, size, size, background);
        DrawRectangleLinesEx(Rectangle{x,y,size,size}, bsize, border);
    } else {
        float radius = size / 2.0;
        Vector2 center = Vector2{(float)(x+radius),(float)(y+radius)};
        DrawCircleV(center, radius, background);
        DrawRing(center, radius-bsize, radius, 0, 360, 36, border);
    }
    // DrawRectangle(x+(size-val.dim.x)/2, y+(size-val.dim.y)/2, val.dim.x, val.dim.y, YELLOW);
    val.draw(toVector2(x+(size-val.dim.x)/2, y+(size-val.dim.y)/2), foreground);
    sub.draw(toVector2(x + size / 2 - sub.dim.x / 2, y + size + Graphic::NODE_SUBTEXT_MARGIN_TOP), subtext);
}


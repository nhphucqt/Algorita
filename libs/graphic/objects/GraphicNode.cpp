#include "GraphicNode.h"

GraphicNode::GraphicNode() {
    bsize = Graphic::NODE_BORDER_WIDTH;
    resetColor();
    isAppear = false;
    outerShapeIn = outerShapeOut = cf::outerNull;
    transparent = 0.0; // vanish at first
    sub = StyledText("", Gfont::defaultFont, Graphic::NODE_SUBTEXT_PADDING);
    super = StyledText("", Gfont::defaultFont, Graphic::NODE_SUBTEXT_PADDING);
}

GraphicNode::GraphicNode(float _x, float _y, float _s, bool _sqr, int _v, const std::string &_subtext) : GraphicNode() {
    x = _x;
    y = _y;
    size = _s;
    isSqr = _sqr;
    // isSqr = true;
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
    x += Tx;
    y += Ty;
}

void GraphicNode::displace(int Dx, int Dy) {
    x = Dx;
    y = Dy;
}

void GraphicNode::setValue(int x) {
    assert(Core::NODE_MIN_VALUE <= x && x <= Core::NODE_MAX_VALUE);
    val = StyledText(x, Gfont::defaultFont);
    nVal = x;
}

void GraphicNode::setSubText(const std::string &_subtext) {
    sub.assign(_subtext);
}

void GraphicNode::setSuperText(const std::string &_supertext) {
    super.assign(_supertext);
}

void GraphicNode::resetColor() {
    pBackColor = &Theme::currTheme.NODE_BACKGROUND;
    pForeColor = &Theme::currTheme.NODE_FOREGROUND;
    pBordColor = &Theme::currTheme.NODE_BORDER;
}

void GraphicNode::setDisabledColor() {
    pBackColor = &Theme::currTheme.NODE_BACKGROUND_DISABLED;
    pForeColor = &Theme::currTheme.NODE_FOREGROUND_DISABLED;
    pBordColor = &Theme::currTheme.NODE_BORDER_DISABLED;
}

void GraphicNode::draw() {
    if (transparent == 0.0) {
        return;
    }
    Color background = TRNSP(pBackColor == nullptr ? backColor : *pBackColor, transparent);
    Color foreground = TRNSP(pForeColor == nullptr ? foreColor : *pForeColor, transparent);
    Color border = pBordColor == nullptr ? TRNSP(bordColor, transparent) : TRNSP(*pBordColor, transparent);
    Color subtext = TRNSP(Theme::currTheme.NODE_SUBTEXT, transparent);
    Color supertext = TRNSP(Theme::currTheme.NODE_SUPERTEXT, transparent);
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
    super.draw(toVector2(x + size / 2 - super.dim.x / 2, y - super.dim.y - Graphic::NODE_SUBTEXT_MARGIN_TOP), supertext);
    sub.draw(toVector2(x + size / 2 - sub.dim.x / 2, y + size + Graphic::NODE_SUBTEXT_MARGIN_TOP), subtext);
}


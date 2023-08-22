#include "GraphicTransNode.h"

GraphicTransNode::GraphicTransNode() 
: GraphicNode() {

}

GraphicTransNode::GraphicTransNode(float _x, float _y, float _s, float _bs, bool _sqr, Font* font, int _v, const std::string &_subtext) 
: GraphicNode(_x, _y, _s, _bs, _sqr, font, _v, _subtext) {
    curPos = Vector2{_x,_y};
    trans = Z_VECT;
}

GraphicTransNode::GraphicTransNode(float _x, float _y, float _s, float _bs, bool _sqr, Font* font, std::string str, const std::string &_subtext)
: GraphicNode(_x, _y, _s, _bs, _sqr, font, str, _subtext) {
    curPos = Vector2{_x,_y};
    trans = Z_VECT;
}


GraphicTransNode::GraphicTransNode(float _x, float _y, float _s, bool _sqr, int _v, const std::string &_subtext) 
: GraphicTransNode(_x, _y, _s, Graphic::NODE_BORDER_WIDTH, _sqr, Gfont::defaultFont, _v, _subtext) {}

GraphicTransNode::GraphicTransNode(float _x, float _y, float _s, bool _sqr, int _v)
: GraphicTransNode(_x, _y, _s, Graphic::NODE_BORDER_WIDTH, _sqr, Gfont::defaultFont, _v, "") {}

Vector2 GraphicTransNode::getCurPos() {
    return curPos;
}

void GraphicTransNode::resetCurPos() {
    curPos = Vector2{x, y};
}

bool GraphicTransNode::isTrans() {
    return fabs(trans.x) > Geo::EPS || fabs(trans.y) > Geo::EPS;
}

Vector2 GraphicTransNode::getTrans() {
    return trans;
}

Vector2 GraphicTransNode::getNewTransPos() {
    return curPos + trans;
}


void GraphicTransNode::addTrans(Vector2 v) {
    trans += v;
}

void GraphicTransNode::addTrans(float x, float y) {
    trans += Vector2{x, y};
}

void GraphicTransNode::updateTransFromPos(Vector2 p) {
    trans = p - curPos;
}

void GraphicTransNode::applyTrans() {
    curPos += trans;
}

void GraphicTransNode::resetTrans() {
    trans = Z_VECT;
}

void GraphicTransNode::draw() {
    GraphicNode::draw();
}
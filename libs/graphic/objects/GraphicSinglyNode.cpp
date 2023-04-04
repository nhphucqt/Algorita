#include "GraphicSinglyNode.h"

GraphicSinglyNode::GraphicSinglyNode() : GraphicNode::GraphicNode() {
    pNext = nullptr;
    aNext = GraphicTrackArrow();
}

GraphicSinglyNode::GraphicSinglyNode(float _x, float _y, float _s, bool _sqr, int _v) : GraphicNode::GraphicNode(_x, _y, _s, _sqr, _v) {
    pNext = nullptr;
    if (isSqr) {
        outerShapeIn = std::bind(&cf::outerSqur, &size, std::placeholders::_1);
        outerShapeOut = std::bind(&cf::outerSqur, &size, std::placeholders::_1);
    } else { // circle
        outerShapeIn = std::bind(&cf::outerCirc, &size, std::placeholders::_1);
        outerShapeOut = std::bind(&cf::outerCirc, &size, std::placeholders::_1);
    }
}

GraphicSinglyNode::GraphicSinglyNode(float _x, float _y, float _s, bool _sqr, int _v, GraphicSinglyNode* newNext) : GraphicSinglyNode(_x, _y, _s, _sqr, _v) {
    setNext(newNext);
}

GraphicSinglyNode::GraphicSinglyNode(float _x, float _y, float _s, bool _sqr) : GraphicSinglyNode(_x, _y, _s, _sqr, 0) {}

GraphicSinglyNode::GraphicSinglyNode(float _x, float _y, float _s, bool _sqr, GraphicSinglyNode* newNext) : GraphicSinglyNode(_x, _y, _s, _sqr, 0, newNext) {}

void GraphicSinglyNode::setNext(GraphicSinglyNode* pNode) {
    pNext = pNode;
    aNext = GraphicTrackArrow(&x, &y, &pNode->x, &pNode->y, &size, &pNode->size, outerShapeOut, pNode->outerShapeIn);
}

void GraphicSinglyNode::updateNext(GraphicSinglyNode* pNode) { 
    pNext = pNode;
    aNext.pB = TrVector(&pNode->x, &pNode->y);
    aNext.sB = &pNode->size;
    aNext.ftB = pNode->outerShapeIn;
    aNext.transA = Z_VECT;
    aNext.transB = Z_VECT;
}

void GraphicSinglyNode::unSetNext() {
    pNext = nullptr;
    aNext.isTrack = false;
}

void GraphicSinglyNode::makeCopy(const GraphicSinglyNode &src) { // no change in pNext, aNext
    x = src.x;
    y = src.y;
    lx = src.lx;
    ly = src.ly;

    size = src.size;
    bsize = src.bsize;

    isSqr = src.isSqr;

    for (int i = 0; i < 2; ++i) {
        backColor[i] = src.backColor[i];
        foreColor[i] = src.foreColor[i];
        bordColor[i] = src.bordColor[i];
    }

    transparent = src.transparent;
    focusPercent = src.focusPercent;
    focusBorderPercent = src.focusBorderPercent;

    nVal = src.nVal;
    val = src.val;

    isFocus = src.isFocus;
    isFocusBorder = src.isFocusBorder;

    if (isSqr) {
        outerShapeIn = std::bind(&cf::outerSqur, &size, std::placeholders::_1);
        outerShapeOut = std::bind(&cf::outerSqur, &size, std::placeholders::_1);
    } else { // circle
        outerShapeIn = std::bind(&cf::outerCirc, &size, std::placeholders::_1);
        outerShapeOut = std::bind(&cf::outerCirc, &size, std::placeholders::_1);
    }
}

void GraphicSinglyNode::draw() {
    aNext.draw();
    GraphicNode::draw();
}
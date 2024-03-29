#include "GraphicSinglyNode.h"

GraphicSinglyNode::GraphicSinglyNode(float _x, float _y, float _s, float _bs, bool _sqr, Font* font, int _v, GraphicSinglyNode* newNext) 
: GraphicNode(_x, _y, _s, _bs, _sqr, font, _v, "") {
    if (isSqr) {
        outerShapeIn = std::bind(&cf::outerSqur, &size, std::placeholders::_1);
        outerShapeOut = std::bind(&cf::outerSqur, &size, std::placeholders::_1);
    } else { // circle
        outerShapeIn = std::bind(&cf::outerCirc, &size, std::placeholders::_1);
        outerShapeOut = std::bind(&cf::outerCirc, &size, std::placeholders::_1);
    }
    setNext(newNext);
}

GraphicSinglyNode::GraphicSinglyNode(float _x, float _y, float _s, bool _sqr, int _v) 
: GraphicSinglyNode(_x, _y, _s, Graphic::NODE_BORDER_WIDTH, _sqr, Gfont::defaultFont, _v, nullptr) {}

GraphicSinglyNode::GraphicSinglyNode(float _x, float _y, float _s, bool _sqr, int _v, GraphicSinglyNode* newNext) 
: GraphicSinglyNode(_x, _y, _s, Graphic::NODE_BORDER_WIDTH, _sqr, Gfont::defaultFont, _v, newNext) {}

GraphicSinglyNode::GraphicSinglyNode(float _x, float _y, float _s, bool _sqr) 
: GraphicSinglyNode(_x, _y, _s, _sqr, 0) {}

GraphicSinglyNode::GraphicSinglyNode(float _x, float _y, float _s, bool _sqr, GraphicSinglyNode* newNext)
: GraphicSinglyNode(_x, _y, _s, _sqr, 0, newNext) {}

void GraphicSinglyNode::setNext(GraphicSinglyNode* pNode) {
    pNext = pNode;
    if (pNode != nullptr) {
        aNext = GraphicTrackArrow(&x, &y, &pNode->x, &pNode->y, &size, &pNode->size, outerShapeOut, pNode->outerShapeIn);
    } else {
        aNext = GraphicTrackArrow();
    }
}

void GraphicSinglyNode::setNext(GraphicSinglyNode* pNode, float lineWidth, float headWidth, float headLength) {
    pNext = pNode;
    if (pNode != nullptr) {
        aNext = GraphicTrackArrow(lineWidth, headWidth, headLength, &x, &y, &pNode->x, &pNode->y, &size, &pNode->size, outerShapeOut, pNode->outerShapeIn);
    } else {
        aNext = GraphicTrackArrow();
    }
}

void GraphicSinglyNode::updateNext(GraphicSinglyNode* pNode) { 
    pNext = pNode;
    aNext.pB = TrVector(&pNode->x, &pNode->y);
    aNext.sB = &pNode->size;
    aNext.ftB = pNode->outerShapeIn;
    aNext.transA = Z_VECT;
    aNext.transB = Z_VECT;
}

void GraphicSinglyNode::setNextArrowTrans(GraphicSinglyNode* node) {
    Vector2 cA = aNext.pA + toSqrVector2(*aNext.sA / 2);
    Vector2 cB = aNext.pB + toSqrVector2(*aNext.sB / 2);
    Vector2 cC = toVector2(node->x, node->y) + toSqrVector2(node->size / 2);

    Vector2 AB = cB - cA;
    Vector2 BA = cA - cB;
    Vector2 CA = cA - cC;
    Vector2 AC = cC - cA;

    Vector2 newB = cB + aNext.ftB(BA);
    Vector2 newC = cC + node->outerShapeIn(CA);

    Vector2 BC = newC - newB;

    aNext.transA = outerShapeOut(AC) - outerShapeOut(AB);
    aNext.transB = BC;
}

void GraphicSinglyNode::draw() {
    aNext.draw();
    GraphicNode::draw();
}
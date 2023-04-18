#include "GraphicDoublyNode.h"

GraphicDoublyNode::GraphicDoublyNode() : GraphicNode::GraphicNode() {
    pNext = pPrev = nullptr;
}

GraphicDoublyNode::GraphicDoublyNode(float _x, float _y, float _s, bool _sqr, int _v) : GraphicNode::GraphicNode(_x, _y, _s, _sqr, _v) {
    pNext = pPrev = nullptr;
    if (isSqr) {
        outerShapeIn = std::bind(&cf::outerSqurLeft, &size, std::placeholders::_1);
        outerShapeOut = std::bind(&cf::outerSqurRight, &size, std::placeholders::_1);
    } else { // circle
        outerShapeIn = std::bind(&cf::outerCircLeft, &size, std::placeholders::_1);
        outerShapeOut = std::bind(&cf::outerCircRight, &size, std::placeholders::_1);
    }
}

GraphicDoublyNode::GraphicDoublyNode(float _x, float _y, float _s, bool _sqr) : GraphicDoublyNode(_x, _y, _s, _sqr, 0) {
    pNext = pPrev = nullptr;
}

void GraphicDoublyNode::setNext(GraphicDoublyNode* pNode) {
    pNext = pNode;
    aNext = GraphicTrackArrow(&x, &y, &pNode->x, &pNode->y, &size, &pNode->size, outerShapeOut, pNode->outerShapeIn);
}

void GraphicDoublyNode::setPrev(GraphicDoublyNode* pNode) {
    pPrev = pNode;
    aPrev = GraphicTrackArrow(&x, &y, &pNode->x, &pNode->y, &size, &pNode->size, outerShapeOut, pNode->outerShapeIn); 
}

void GraphicDoublyNode::setRevPrev(GraphicDoublyNode* pNode) {
    pPrev = pNode;
    aPrev = GraphicTrackArrow(&pNode->x, &pNode->y, &x, &y, &pNode->size, &size, pNode->outerShapeOut, outerShapeIn); 
}

void GraphicDoublyNode::updateNext(GraphicDoublyNode* pNode) {
    pNext = pNode;
    aNext.pB = TrVector(&pNode->x, &pNode->y);
    aNext.sB = &pNode->size;
    aNext.ftB = pNode->outerShapeIn;
    aNext.transA = Z_VECT;
    aNext.transB = Z_VECT;
}

void GraphicDoublyNode::updatePrev(GraphicDoublyNode* pNode) {
    pPrev = pNode;
    aPrev.pB = TrVector(&pNode->x, &pNode->y);
    aPrev.sB = &pNode->size;
    aPrev.ftB = pNode->outerShapeIn;
    aPrev.transA = Z_VECT;
    aPrev.transB = Z_VECT;
}



void GraphicDoublyNode::setArrowHeadTrans(GraphicTrackArrow* arrow, GraphicDoublyNode* node) {
    Vector2 cA = arrow->pA + toSqrVector2(*arrow->sA / 2);
    Vector2 cB = arrow->pB + toSqrVector2(*arrow->sB / 2);
    Vector2 cC = toVector2(node->x, node->y) + toSqrVector2(node->size / 2);

    Vector2 AB = cB - cA;
    Vector2 BA = cA - cB;
    Vector2 CA = cA - cC;
    Vector2 AC = cC - cA;

    Vector2 newB = cB + arrow->ftB(BA);
    Vector2 newC = cC + node->outerShapeIn(CA);

    Vector2 BC = newC - newB;

    arrow->transA = outerShapeOut(AC) - outerShapeOut(AB);
    arrow->transB = BC;
}

void GraphicDoublyNode::setArrowTailTrans(GraphicTrackArrow* arrow, GraphicDoublyNode* node) {
    Vector2 cA = arrow->pA + toSqrVector2(*arrow->sA / 2);
    Vector2 cB = arrow->pB + toSqrVector2(*arrow->sB / 2);
    Vector2 cC = toVector2(node->x, node->y) + toSqrVector2(node->size / 2);

    Vector2 AB = cB - cA;
    Vector2 BA = cA - cB;
    Vector2 CB = cB - cC;
    Vector2 BC = cC - cB;

    Vector2 newA = cA + arrow->ftA(AB);
    Vector2 newC = cC + node->outerShapeOut(CB);

    Vector2 AC = newC - newA;

    arrow->transA = AC;
    arrow->transB = arrow->ftB(BC) - arrow->ftB(BA);
}

void GraphicDoublyNode::draw() {
    aNext.draw();
    aPrev.draw();
    GraphicNode::draw();
}
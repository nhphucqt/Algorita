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
    pNode->pPrev = this;
    pNode->aPrev = GraphicTrackArrow(&pNode->x, &pNode->y, &x, &y, &pNode->size, &size, pNode->outerShapeOut, outerShapeIn);
}

void GraphicDoublyNode::setPrev(GraphicDoublyNode* pNode) {
    pPrev = pNode;
    aPrev = GraphicTrackArrow(&x, &y, &pNode->x, &pNode->y, &size, &pNode->size, outerShapeOut, pNode->outerShapeIn);
    pNode->pNext = this;
    pNode->aNext = GraphicTrackArrow(&pNode->x, &pNode->y, &x, &y, &pNode->size, &size, pNode->outerShapeOut, outerShapeIn);
}

void GraphicDoublyNode::draw() {
    aNext.draw();
    aPrev.draw();
    GraphicNode::draw();
}
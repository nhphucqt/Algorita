#include "GraphicSinglyNode.h"

GraphicSinglyNode::GraphicSinglyNode() : GraphicNode::GraphicNode() {
    pNext = nullptr;
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

void GraphicSinglyNode::unSetNext() {
    pNext = nullptr;
    aNext.isTrack = false;
}

void GraphicSinglyNode::draw() {
    aNext.draw();
    GraphicNode::draw();
}
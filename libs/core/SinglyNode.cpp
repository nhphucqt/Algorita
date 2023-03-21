#include "SinglyNode.h"

SinglyNode::SinglyNode() : GraphicNode::GraphicNode() {
    pNext = nullptr;
}

SinglyNode::SinglyNode(float _x, float _y, float _s, bool _sqr, int _v) : GraphicNode::GraphicNode(_x, _y, _s, _sqr, _v) {
    pNext = nullptr;
}

void SinglyNode::setNext(SinglyNode* pNode) {
    pNext = pNode;
    aNext = GraphicTrackArrow(&x, &y, &pNode->x, &pNode->y, &size, &pNode->size, outerShape, pNode->outerShape);
}

void SinglyNode::draw() {
    aNext.draw();
    GraphicNode::draw();
}
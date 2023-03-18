#include "SinglyNode.h"

SinglyNode::SinglyNode() : GraphicNode::GraphicNode() {
    pNext = nullptr;
}

SinglyNode::SinglyNode(float _x, float _y, float _s, bool _sqr, int _v) : GraphicNode::GraphicNode(_x, _y, _s, _sqr, _v) {
    pNext = nullptr;
}

void SinglyNode::setNext(SinglyNode* pNode) {
    pNext = pNode;
    aNext = GraphicTrackArrow(&x, &y, &pNode->x, &pNode->y, toVector2(size/2,size/2), toVector2(pNode->size/2,pNode->size/2));
}

void SinglyNode::draw() {
    aNext.draw();
    GraphicNode::draw();
}
#include "SinglyNode.h"

SinglyNode::SinglyNode() : GraphicNode::GraphicNode() {
    pNext = nullptr;
}

SinglyNode::SinglyNode(float _x, float _y, float _s, bool _sqr, int _v) : GraphicNode::GraphicNode(_x, _y, _s, _sqr, _v) {
    pNext = nullptr;
    if (isSqr) {
        outerShapeIn = std::bind(&cf::outerSqur, &size, std::placeholders::_1);
        outerShapeOut = std::bind(&cf::outerSqur, &size, std::placeholders::_1);
    } else { // circle
        outerShapeIn = std::bind(&cf::outerCirc, &size, std::placeholders::_1);
        outerShapeOut = std::bind(&cf::outerCirc, &size, std::placeholders::_1);
    }
}

SinglyNode::SinglyNode(float _x, float _y, float _s, bool _sqr, int _v, SinglyNode* newNext) : SinglyNode(_x, _y, _s, _sqr, _v) {
    setNext(newNext);
}

SinglyNode::SinglyNode(float _x, float _y, float _s, bool _sqr) : SinglyNode(_x, _y, _s, _sqr, 0) {}

SinglyNode::SinglyNode(float _x, float _y, float _s, bool _sqr, SinglyNode* newNext) : SinglyNode(_x, _y, _s, _sqr, 0, newNext) {}

void SinglyNode::setNext(SinglyNode* pNode) {
    pNext = pNode;
    aNext = GraphicTrackArrow(&x, &y, &pNode->x, &pNode->y, &size, &pNode->size, outerShapeOut, pNode->outerShapeIn);
}

void SinglyNode::draw() {
    aNext.draw();
    GraphicNode::draw();
}
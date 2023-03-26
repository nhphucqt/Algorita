#include "CoreSinglyNode.h"

CoreSinglyNode::CoreSinglyNode() {
    val = 0;
    pNext = nullptr;
}

CoreSinglyNode::CoreSinglyNode(int _v) : CoreSinglyNode() {
    val = _v;
}

CoreSinglyNode::CoreSinglyNode(int _v, CoreSinglyNode* pNode) : CoreSinglyNode(_v) {
    pNext = pNode;
}

CoreSinglyNode::CoreSinglyNode(CoreSinglyNode* pNode) : CoreSinglyNode(0, pNode) {}

void CoreSinglyNode::setNext(CoreSinglyNode* pNode) {
    pNext = pNode;
}
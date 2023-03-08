#ifndef SINGLY_NODE_H
#define SINGLY_NODE_H

#include "../graphic/GraphicNode.h"

class SinglyNode : public GraphicNode {
    int val;
    SinglyNode *pNext, *pPrev;
    SinglyNode();
    SinglyNode(double _x, double _y, int _s, bool _sqr, int _v);
};

#endif
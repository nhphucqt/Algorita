#ifndef SINGLY_NODE_H
#define SINGLY_NODE_H

#include <string>
#include "../global.h"
#include "../graphic/GraphicNode.h"

class SinglyNode : public GraphicNode {
public:
    SinglyNode *pNext;
    SinglyNode();
    SinglyNode(double _x, double _y, int _s, bool _sqr, int _v);
};

#endif
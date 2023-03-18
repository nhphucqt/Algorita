#ifndef SINGLY_NODE_H
#define SINGLY_NODE_H

#include <string>
#include "../global.h"
#include "../graphic/GraphicNode.h"
#include "../graphic/GraphicTrackArrow.h"

class SinglyNode : public GraphicNode {
public:
    SinglyNode *pNext;
    GraphicTrackArrow aNext;
    SinglyNode();
    SinglyNode(float _x, float _y, float _s, bool _sqr, int _v);
    void setNext(SinglyNode* pNode);
    void draw();
};

#endif
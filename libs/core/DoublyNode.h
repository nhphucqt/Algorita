#ifndef DOUBLY_NODE_H
#define DOUBLY_NODE_H

#include "../core/ccppfunc.h"
#include "../graphic/GraphicNode.h"
#include "../graphic/GraphicTrackArrow.h"

class DoublyNode : public GraphicNode {
public:
    DoublyNode *pNext, *pPrev;
    GraphicTrackArrow aPrev, aNext;
    DoublyNode();
    DoublyNode(float _x, float _y, float _s, bool _sqr);
    DoublyNode(float _x, float _y, float _s, bool _sqr, int _v);

    void setNext(DoublyNode* pNode);
    void setPrev(DoublyNode* pNode);

    void draw();
};

#endif
#ifndef GRAPHIC_DOUBLY_NODE_H
#define GRAPHIC_DOUBLY_NODE_H

#include "../core/ccppfunc.h"
#include "../graphic/GraphicNode.h"
#include "../graphic/GraphicTrackArrow.h"

class GraphicDoublyNode : public GraphicNode {
public:
    GraphicDoublyNode *pNext, *pPrev;
    GraphicTrackArrow aPrev, aNext;
    GraphicDoublyNode();
    GraphicDoublyNode(float _x, float _y, float _s, bool _sqr);
    GraphicDoublyNode(float _x, float _y, float _s, bool _sqr, int _v);

    void setNext(GraphicDoublyNode* pNode);
    void setPrev(GraphicDoublyNode* pNode);

    void draw();
};

#endif
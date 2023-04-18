#ifndef GRAPHIC_DOUBLY_NODE_H
#define GRAPHIC_DOUBLY_NODE_H

#include "../../core/ccppfunc.h"
#include "GraphicNode.h"
#include "GraphicTrackArrow.h"

class GraphicDoublyNode : public GraphicNode {
public:
    GraphicDoublyNode *pNext, *pPrev;
    GraphicTrackArrow aPrev, aNext;
    GraphicDoublyNode();
    GraphicDoublyNode(float _x, float _y, float _s, bool _sqr);
    GraphicDoublyNode(float _x, float _y, float _s, bool _sqr, int _v);

    void setNext(GraphicDoublyNode* pNode);
    void setPrev(GraphicDoublyNode* pNode);

    void setRevPrev(GraphicDoublyNode* pNode);

    void updateNext(GraphicDoublyNode* pNode);
    void updatePrev(GraphicDoublyNode* pNode);


    void setArrowHeadTrans(GraphicTrackArrow* arrow, GraphicDoublyNode* node);
    void setArrowTailTrans(GraphicTrackArrow* arrow, GraphicDoublyNode* node);


    void draw();
};

#endif
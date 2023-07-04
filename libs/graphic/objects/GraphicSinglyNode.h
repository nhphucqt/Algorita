#ifndef GRAPHIC_SINGLY_NODE_H
#define GRAPHIC_SINGLY_NODE_H

#include <string>
#include "../../global.h"
#include "GraphicNode.h"
#include "GraphicTrackArrow.h"

class GraphicSinglyNode : public GraphicNode {
public:
    GraphicSinglyNode* pNext;
    GraphicTrackArrow aNext;

    GraphicSinglyNode(float _x, float _y, float _s, float _bs, bool _sqr, Font* font, int _v, GraphicSinglyNode* newNext);
    GraphicSinglyNode(float _x, float _y, float _s, bool _sqr, int _v, GraphicSinglyNode* newNext);
    GraphicSinglyNode(float _x, float _y, float _s, bool _sqr, GraphicSinglyNode* newNext);
    GraphicSinglyNode(float _x, float _y, float _s, bool _sqr, int _v);
    GraphicSinglyNode(float _x, float _y, float _s, bool _sqr);

    void setNext(GraphicSinglyNode* pNode);
    void setNext(GraphicSinglyNode* pNode, float lineWidth, float headWidth, float headLength);
    void updateNext(GraphicSinglyNode* pNode);

    void setNextArrowTrans(GraphicSinglyNode* node);

    void draw();
};

#endif
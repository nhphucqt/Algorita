#ifndef GRAPHIC_SINGLY_LINKED_LIST_H
#define GRAPHIC_SINGLY_LINKED_LIST_H

#include <assert.h>

#include "../core/CoreSinglyLinkedList.h"
#include "GraphicSinglyNode.h"
#include "animation.h"

class GraphicSinglyLinkedList {
private:
    GraphicSinglyNode* pHead;
    CoreSinglyLinkedList core;
    std::list<GraphicSinglyNode*> separatedNodes;

    bool registerNode(GraphicSinglyNode* node);
    bool unRegisterNode(GraphicSinglyNode* node);
    bool unRegisterAndDeleteNode(GraphicSinglyNode* node);

    bool transformAllNodes(int Tx, int Ty);
    bool transformAllNodesFrom(int Tx, int Ty, GraphicSinglyNode* start);

    bool animatePushFront(int val);
    bool animatePushBack(int val);
    bool animatePushAtKth(int k, int val);

    bool animatePopFront();
    bool animatePopBack();
    bool animatePopAtKth(int k);

public:

    GraphicSinglyLinkedList();

    void pushFront(int val);
    void pushBack(int val);
    void pushAtKth(int k, int val);

    bool popFront();
    bool popBack();
    bool popAtKth(int val);

    void draw();

    void destroy();
};

#endif
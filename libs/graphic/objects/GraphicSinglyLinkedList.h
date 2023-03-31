#ifndef GRAPHIC_SINGLY_LINKED_LIST_H
#define GRAPHIC_SINGLY_LINKED_LIST_H

#include <assert.h>
#include <vector>

#include "../../core/objects/CoreSinglyLinkedList.h"
#include "GraphicSinglyNode.h"
#include "../animation.h"

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

    bool animateInitialize(std::vector<int> vals);

    bool animatePushFront(int val);
    bool animatePushBack(int val);
    bool animatePushAtKth(int k, int val);

    bool animatePopFront();
    bool animatePopBack();
    bool animatePopAtKth(int k);

    bool animateSearch(int val);

public:

    GraphicSinglyLinkedList();

    void initialize(int initSize); // Randomly initialize
    void initialize(std::vector<int> vals); // Initialize with given values

    void pushFront(int val);
    void pushBack(int val);
    void pushAtKth(int k, int val);

    bool popFront();
    bool popBack();
    bool popAtKth(int val);

    bool search(int val);

    void draw();

    void destroy();
};

#endif
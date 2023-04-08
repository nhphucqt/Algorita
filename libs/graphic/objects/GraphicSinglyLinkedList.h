#ifndef GRAPHIC_SINGLY_LINKED_LIST_H
#define GRAPHIC_SINGLY_LINKED_LIST_H

#include <assert.h>
#include <vector>

#include "GraphicSinglyNode.h"
#include "../../core/objects/CoreSinglyLinkedList.h"
#include "../../core/ccppfunc.h"
#include "../../core/ExitStatus.h"
#include "../../animation/animation.h"
#include "../../animation/OperationsGroups.h"
#include "../../animation/ListOfOperationsGroups.h"

class GraphicSinglyLinkedList {
// private:
public:
    GraphicSinglyNode* pHead;
    int size;

    std::list<GraphicSinglyNode*> nodes;
    std::list<GraphicTrackArrow*> arrows;

    void unfocusAllNodes();

    void appearAllNodes();
    void vanishAllNodes();

public:

    GraphicSinglyLinkedList();

    ExitStatus initialize(int initSize, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG); // Randomly initialize
    ExitStatus initialize(std::vector<int> vals, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG); // Initialize with given values

    ExitStatus searchFirst(int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG);

    ExitStatus pushFront(int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG);
    ExitStatus pushBack(int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG);
    ExitStatus pushAtKth(int k, int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG);
    
    ExitStatus popFront(ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG);
    ExitStatus popBack(ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG);

    void draw();

    void makeCopy(GraphicSinglyLinkedList* src);

    void reset();
    void clearSaparated();
    void clearArrows();
    void destroy();
};

#endif
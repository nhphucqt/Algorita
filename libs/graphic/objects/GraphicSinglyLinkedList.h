#ifndef GRAPHIC_SINGLY_LINKED_LIST_H
#define GRAPHIC_SINGLY_LINKED_LIST_H

#include <assert.h>
#include <vector>

#include "GraphicSinglyNode.h"
#include "../../core/ccppfunc.h"
#include "../../core/ExitStatus.h"
#include "../../animation/animation.h"
#include "../../animation/OperationsGroups.h"
#include "../../animation/ListOfOperationsGroups.h"
#include "../../core/userfunc.h"

class GraphicSinglyLinkedList {
private:
    GraphicSinglyNode* pHead;
    int _size;

    std::list<GraphicSinglyNode*> nodes;
    std::list<GraphicTrackArrow*> arrows;

    void resetColorAllNodes();
    void resetSubTextAllNodes();

    void appearAllNodes();
    void vanishAllNodes();

public:
    GraphicSinglyLinkedList();

    bool empty() const;
    int size() const;

    ExitStatus initialize(int initSize, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG); // Randomly initialize
    ExitStatus initialize(std::vector<int> vals, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG); // Initialize with given values
    ExitStatus initialize(std::string strVals, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG); // Initialize with given values

    ExitStatus searchFirst(int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG);

    ExitStatus updateHeadValue(int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG);
    ExitStatus updateValue(int k, int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG);

    ExitStatus peek(ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG);

    ExitStatus pushFront(int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG);
    ExitStatus pushBack(int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG);
    ExitStatus pushAtKth(int k, int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG);
    
    ExitStatus popFront(ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG);
    ExitStatus popBack(ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG);
    ExitStatus popAtKth(int k, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG);

    void draw();

    void reset();
    void clearSaparated();
    void clearArrows();
    void destroy();
};

#endif
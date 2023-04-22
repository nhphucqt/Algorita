#ifndef GRAPHIC_DOUBLY_LINKED_LIST_H
#define GRAPHIC_DOUBLY_LINKED_LIST_H

#include <assert.h>
#include <vector>

#include "GraphicDoublyNode.h"
#include "../../core/ccppfunc.h"
#include "../../core/ExitStatus.h"
#include "../../animation/animation.h"
#include "../../animation/OperationsGroups.h"
#include "../../animation/ListOfOperationsGroups.h"
#include "../../core/userfunc.h"


class GraphicDoublyLinkedList {
private:
    GraphicDoublyNode* pHead;
    int _size;

    std::list<GraphicDoublyNode*> nodes;
    std::list<GraphicTrackArrow*> arrows;

    void resetColorAllNodes();
    void resetSubTextAllNodes();

public:
    GraphicDoublyLinkedList();

    bool empty() const;
    int size() const;

    ExitStatus initialize(int initSize, ListOfOperationsGroups<GraphicDoublyLinkedList>* ALOG); // Randomly initialize
    ExitStatus initialize(std::vector<int> vals, ListOfOperationsGroups<GraphicDoublyLinkedList>* ALOG); // Initialize with given values
    ExitStatus initialize(std::string strVals, ListOfOperationsGroups<GraphicDoublyLinkedList>* ALOG); // Initialize with given values

    ExitStatus searchFirst(int val, ListOfOperationsGroups<GraphicDoublyLinkedList>* ALOG);

    ExitStatus updateValue(int k, int val, ListOfOperationsGroups<GraphicDoublyLinkedList>* ALOG);

    ExitStatus pushFront(int val, ListOfOperationsGroups<GraphicDoublyLinkedList>* ALOG);
    ExitStatus pushBack(int val, ListOfOperationsGroups<GraphicDoublyLinkedList>* ALOG);
    ExitStatus pushAtKth(int k, int val, ListOfOperationsGroups<GraphicDoublyLinkedList>* ALOG);
    
    ExitStatus popFront(ListOfOperationsGroups<GraphicDoublyLinkedList>* ALOG);
    ExitStatus popBack(ListOfOperationsGroups<GraphicDoublyLinkedList>* ALOG);
    ExitStatus popAtKth(int k, ListOfOperationsGroups<GraphicDoublyLinkedList>* ALOG);

    void draw();

    void reset();
    void clearSaparated();
    void clearArrows();
    void destroy();
};

#endif

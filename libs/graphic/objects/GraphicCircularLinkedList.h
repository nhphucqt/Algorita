#ifndef GRAPHIC_CIRCULAR_LINKED_LIST_H
#define GRAPHIC_CIRCULAR_LINKED_LIST_H

#include "GraphicSinglyNode.h"
#include "GraphicHookArrow.h"
#include "../../core/ccppfunc.h"
#include "../../core/ExitStatus.h"
#include "../../animation/animation.h"
#include "../../animation/OperationsGroups.h"
#include "../../animation/ListOfOperationsGroups.h"
#include "../../core/userfunc.h"

class GraphicCircularLinkedList {
private:
    GraphicSinglyNode* pHead;
    GraphicHookArrow harrow;
    int _size;

    std::list<GraphicSinglyNode*> nodes;
    std::list<GraphicTrackArrow*> arrows;

    void resetColorAllNodes();
    void resetSubTextAllNodes();

public:
    GraphicCircularLinkedList();

    bool empty() const;
    int size() const;

    ExitStatus initialize(int initSize, ListOfOperationsGroups* ALOG); // Randomly initialize
    ExitStatus initialize(std::vector<int> vals, ListOfOperationsGroups* ALOG); // Initialize with given values
    ExitStatus initialize(std::string strVals, ListOfOperationsGroups* ALOG); // Initialize with given values

    ExitStatus searchFirst(int val, ListOfOperationsGroups* ALOG);

    ExitStatus updateHeadValue(int val, ListOfOperationsGroups* ALOG);
    ExitStatus updateValue(int k, int val, ListOfOperationsGroups* ALOG);

    ExitStatus peek(ListOfOperationsGroups* ALOG);

    ExitStatus pushFront(int val, ListOfOperationsGroups* ALOG);
    ExitStatus pushBack(int val, ListOfOperationsGroups* ALOG);
    ExitStatus pushAtKth(int k, int val, ListOfOperationsGroups* ALOG);
    
    ExitStatus popFront(ListOfOperationsGroups* ALOG);
    ExitStatus popBack(ListOfOperationsGroups* ALOG);
    ExitStatus popAtKth(int k, ListOfOperationsGroups* ALOG);

    void draw();

    void reset();
    void clearSaparated();
    void clearArrows();
    void destroy();
};

#endif
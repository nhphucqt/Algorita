#ifndef GRAPHIC_QUEUE_H
#define GRAPHIC_QUEUE_H

#include <assert.h>
#include <vector>

#include "GraphicSinglyNode.h"
#include "../../core/ccppfunc.h"
#include "../../core/ExitStatus.h"
#include "../../animation/animation.h"
#include "../../animation/OperationsGroups.h"
#include "../../animation/ListOfOperationsGroups.h"
#include "../../core/userfunc.h"

#include "GraphicHookArrow.h"

class GraphicQueue {
private:
    GraphicSinglyNode* pHead;
    GraphicSinglyNode* pTail;
    int _size;

    std::list<GraphicSinglyNode*> nodes;

    void resetColorAllNodes();
    void resetSubTextAllNodes();

public:
    GraphicQueue();

    bool empty() const;
    int size() const;

    ExitStatus initialize(int initSize, ListOfOperationsGroups* ALOG); // Randomly initialize
    ExitStatus initialize(std::vector<int> vals, ListOfOperationsGroups* ALOG); // Initialize with given values
    ExitStatus initialize(std::string strVals, ListOfOperationsGroups* ALOG); // Initialize with given values

    ExitStatus peek(ListOfOperationsGroups* ALOG);
    ExitStatus update(int val, ListOfOperationsGroups* ALOG);
    ExitStatus push(int val, ListOfOperationsGroups* ALOG);
    ExitStatus pop(ListOfOperationsGroups* ALOG);
    ExitStatus clear(ListOfOperationsGroups* ALOG);

    void draw();

    void reset();
    void clearSaparated();
    void destroy();
};

#endif
#ifndef GRAPHIC_STACK_H
#define GRAPHIC_STACK_H

#include "GraphicSinglyLinkedList.h"

class GraphicStack : public GraphicSinglyLinkedList {
public:
    GraphicStack();

    ExitStatus peek(ListOfOperationsGroups* ALOG);

    ExitStatus update(int val, ListOfOperationsGroups* ALOG);

    ExitStatus clear(ListOfOperationsGroups* ALOG);
};

#endif
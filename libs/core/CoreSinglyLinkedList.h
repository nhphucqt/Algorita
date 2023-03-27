#ifndef CORE_SINGLY_LINKED_LIST_H
#define CORE_SINGLY_LINKED_LIST_H

#include <assert.h>

#include "CoreSinglyNode.h"

class CoreSinglyLinkedList {
private:
    int _size;
    CoreSinglyNode* pHead;

public:

    CoreSinglyLinkedList();

    bool empty() const;
    int size() const;

    void pushFront(int val);
    void pushBack(int val);
    void pushAtKth(int k, int val);

    bool popFront();
    bool popBack();
    bool popAtKth(int k);

    void destroy();
};

#endif
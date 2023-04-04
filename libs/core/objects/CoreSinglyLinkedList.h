#ifndef CORE_SINGLY_LINKED_LIST_H
#define CORE_SINGLY_LINKED_LIST_H

#include <assert.h>
#include <vector>

#include "CoreSinglyNode.h"

class CoreSinglyLinkedList {
private:
    int _size;
    CoreSinglyNode* pHead;

public:

    CoreSinglyLinkedList();

    bool empty() const;
    int size() const;

    void initialize(std::vector<int> vals);

    void pushFront(int val);
    void pushBack(int val);
    void pushAtKth(int k, int val);

    bool popFront();
    bool popBack();
    bool popAtKth(int k);

    bool search(int val);
    int searchAll(int val);

    CoreSinglyLinkedList copy() const;
    void makeCopy(const CoreSinglyLinkedList &src);

    void destroy();
};

#endif
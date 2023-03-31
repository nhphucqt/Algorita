#include "CoreSinglyLinkedList.h"

CoreSinglyLinkedList::CoreSinglyLinkedList() {
    _size = 0;
    pHead = nullptr;
}

bool CoreSinglyLinkedList::empty() const {
    return _size == 0;
}

int CoreSinglyLinkedList::size() const {
    return _size;
}

void CoreSinglyLinkedList::initialize(std::vector<int> vals) {
    destroy();
    for (int i = 0; i < (int)vals.size(); ++i) {
        pushBack(vals[i]);
    }
}

void CoreSinglyLinkedList::pushFront(int val) {
    ++_size;
    CoreSinglyNode* newNode = new CoreSinglyNode(val, pHead);
    pHead = newNode;
}

void CoreSinglyLinkedList::pushBack(int val) {
    ++_size;
    CoreSinglyNode* newNode = new CoreSinglyNode(val);
    if (pHead == nullptr) {
        pHead = newNode;
    } else {
        CoreSinglyNode* curr = pHead;
        for (; curr->pNext != nullptr; curr = curr->pNext);
        curr->pNext = newNode;
    }
}

void CoreSinglyLinkedList::pushAtKth(int k, int val) {
    assert(0 <= k && k <= _size);
    if (k == 0) {
        pushFront(val);
    } else {
        ++_size;
        CoreSinglyNode* curr = pHead;
        for (; --k; curr = curr->pNext);
        CoreSinglyNode* newNode = new CoreSinglyNode(val, curr->pNext);
        curr->pNext = newNode;
    }
}

bool CoreSinglyLinkedList::popFront() {
    if (pHead == nullptr) {
        return false;
    }
    --_size;
    CoreSinglyNode* tmp = pHead;
    pHead = pHead->pNext;
    delete tmp;
    return true;
}

bool CoreSinglyLinkedList::popBack() {
    if (pHead == nullptr) {
        return false;
    }
    if (pHead->pNext == nullptr) {
        return popFront();
    }
    --_size;
    CoreSinglyNode* curr = pHead;
    for (; curr->pNext->pNext != nullptr; curr = curr->pNext);
    delete curr->pNext;
    curr->pNext = nullptr;
    return true;
}

bool CoreSinglyLinkedList::popAtKth(int k) {
    if (k < 0 || k >= _size) {
        return false;
    }
    if (k == 0) {
        return popFront();
    }
    --_size;
    CoreSinglyNode* curr = pHead;
    for (; --k; curr = curr->pNext);
    CoreSinglyNode* tmp = curr->pNext;
    curr->pNext = tmp->pNext;
    delete tmp;
    return true;
}

bool CoreSinglyLinkedList::search(int val) {
    for (CoreSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        if (curr->val == val) {
            return true;
        }
    }
    return false;
}

int CoreSinglyLinkedList::searchAll(int val) {
    int cnt = 0;
    for (CoreSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        cnt += curr->val == val;
    }
    return cnt;
}

void CoreSinglyLinkedList::destroy() {
    while (pHead != nullptr) {
        CoreSinglyNode* tmp = pHead;
        pHead = pHead->pNext;
        delete tmp;
    }
    _size = 0;
}

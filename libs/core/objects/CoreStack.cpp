#include "CoreStack.h"

CoreStack::CoreStack() {
    pHead = nullptr;
}

CoreSinglyNode* CoreStack::begin() const {
    return pHead;
}

CoreSinglyNode* CoreStack::iter() const {
    return pIter;
}

CoreSinglyNode* CoreStack::next() {
    assert(pIter != nullptr);
    pIter = pIter->pNext;
    return pIter;
}

CoreSinglyNode* CoreStack::resetIter() {
    return pIter = pHead;
}

void CoreStack::push(int val) {
    CoreSinglyNode* newNode = new CoreSinglyNode(val, pHead);
    pHead = newNode;
}

bool CoreStack::pop() {
    if (pHead == nullptr) {
        return false;   
    } else {
        CoreSinglyNode* tmp = pHead;
        pHead = pHead->pNext;
        delete tmp;
        return true;
    }
}

void CoreStack::destroy() {
    while (pHead != nullptr) {
        CoreSinglyNode* tmp = pHead;
        pHead = pHead->pNext;
        delete tmp;
    }
}
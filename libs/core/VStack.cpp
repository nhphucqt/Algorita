#include "VStack.h"

VStack::VStack() {
    pHead = nullptr;
}

void VStack::transAllNodes(int tx, int ty) {
    Animate::queueOfScenes.addBlankScene();
    for (SinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        Animate::queueOfScenes.pushTransformToBackScene(curr, curr->cx + tx, curr->cy + ty);
    } 
}

void VStack::push(SinglyNode* pNode) {
    pNode->pNext = pHead;
    pHead = pNode;
}

void VStack::push(int val) {
    assert(Core::NODE_MIN_VALUE <= val && val <= Core::NODE_MAX_VALUE);
    if (pHead == nullptr) {
        pHead = new SinglyNode(Graphic::STACK_ORG_X, Graphic::STACK_ORG_Y, Graphic::NODE_SIZE, false, val);
        Animate::queueOfScenes.pushFadeInToNewScene(pHead);
    } else {
        transAllNodes(0, Graphic::STACK_NODE_DIST);
        SinglyNode* newNode = new SinglyNode(pHead->x, pHead->y, Graphic::NODE_SIZE, false, val, pHead);
        pHead = newNode;
        Animate::queueOfScenes.pushFadeInToNewScene(pHead);
        Animate::queueOfScenes.pushFadeInToNewScene(&pHead->aNext);
    }
}

bool VStack::pop() {
    if (pHead == nullptr) {
        return false;
    } else {
        SinglyNode* tmp = pHead;
        pHead = pHead->pNext;
        Animate::queueOfScenes.pushFadeOutToBackScene(&tmp->aNext);
        Animate::queueOfScenes.pushDeleteFadeOutToNewScene(tmp);
        transAllNodes(0, -Graphic::STACK_NODE_DIST);
        return true;
    }
}


void VStack::draw() {
    for (SinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        curr->draw();
    }
}

void VStack::destroy() {
        while (pHead != nullptr) {
        SinglyNode* tmp = pHead;
        pHead = pHead->pNext;
        delete tmp;
    }
}
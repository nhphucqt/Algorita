#include "GraphicStack.h"

GraphicStack::GraphicStack() : GraphicSinglyLinkedList() {}

ExitStatus GraphicStack::update(int val, ListOfOperationsGroups* ALOG) {
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }
    
    ALOG->clearGroup();
ALOG->loadCode(CPath::STACK_UPDATE);
    reset();

    if (pHead == nullptr) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateDelay();
    } else {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        ALOG->animateNodeFromNormalToFocus(pHead);
        ALOG->animateAssignValue(pHead, pHead->nVal, val);
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicStack::peek(ListOfOperationsGroups* ALOG) {
    ALOG->clearGroup();
    ALOG->loadCode(CPath::STACK_PEEK);
    reset();

    if (pHead == nullptr) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateDelay();
    } else {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        ALOG->animateNodeFromNormalToIter(pHead);
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicStack::clear(ListOfOperationsGroups* ALOG) {
    ALOG->clearGroup();
    ALOG->loadCode(CPath::STACK_CLEAR);
    reset();

    if (pHead == nullptr) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateDelay();
    } else {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateNodeFromNormalToIter(pHead);

        int cnt = 0;
        while (pHead != nullptr) {
            GraphicSinglyNode* tmp = pHead;
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({1});
            ALOG->animateNodeFromIterToRemove(tmp);
            ALOG->animateTransText(&tmp->sub, "head", "head/tmp");

            pHead = pHead->pNext;
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({2});
            ALOG->animateTransText(&tmp->sub, "head/tmp", "tmp");
            if (pHead != nullptr) {
                tmp->aNext.pSlideColor = &Theme::currTheme.ARROW_LINE_FOCUS_ITER;
                ALOG->animateSlideColorIn(&tmp->aNext);
                ALOG->animateNodeFromNormalToFocus(pHead);
                ALOG->animateTransText(&pHead->sub, "", "head");
            }

            nodes.push_back(tmp);
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({3});
            ALOG->animateFadeOut(tmp);
            if (pHead != nullptr) {
                ALOG->animateSlideOut(&tmp->aNext);
                ALOG->animateFadeOut(&tmp->aNext);
            }

            if (pHead != nullptr) {
                ALOG->addNewGroup();
                ALOG->backGroup()->setHighlightLines({0});
                ALOG->animateNodeFromFocusToIter(pHead);
                for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
                    ALOG->animateTransform(curr, curr->x - Graphic::NODE_DIST * cnt, curr->y, -Graphic::NODE_DIST, 0);
                }
                cnt++;
            }
        }

        _size = 0;
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}
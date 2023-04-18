#include "GraphicDoublyLinkedList.h"

GraphicDoublyLinkedList::GraphicDoublyLinkedList() {
    pHead = nullptr;
    _size = 0;
}

void GraphicDoublyLinkedList::resetColorAllNodes() {
    for (GraphicDoublyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        curr->resetColor();
        curr->aNext.resetColor();
    }
}

void GraphicDoublyLinkedList::resetSubTextAllNodes() {
    for (GraphicDoublyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        if (curr == pHead) {
            curr->setSubText("head");
        } else {
            curr->setSubText("");
        }
    }
}

void GraphicDoublyLinkedList::vanishAllNodes() {
    for (GraphicDoublyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        curr->vanish();
        curr->aNext.vanish();
    }
}

void GraphicDoublyLinkedList::appearAllNodes() {
    for (GraphicDoublyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        curr->appear();
        curr->aNext.appear();
    }
}

bool GraphicDoublyLinkedList::empty() const {
    return _size == 0;
}

int GraphicDoublyLinkedList::size() const {
    return _size;
}

ExitStatus GraphicDoublyLinkedList::initialize(int initSize, ListOfOperationsGroups<GraphicDoublyLinkedList>* ALOG) { // Randomly initialize
    if (initSize < 0 || initSize > Core::MAX_NUM_NODE_SLL) {
        return ExitMess::FAIL_LL_SIZE_OOB;
    }
    std::vector<int> vals;
    for (int i = 0; i < initSize; ++i) {
        vals.push_back(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
    }
    return initialize(vals, ALOG);
}

ExitStatus GraphicDoublyLinkedList::initialize(std::vector<int> vals, ListOfOperationsGroups<GraphicDoublyLinkedList>* ALOG) { // Initialize with given values
    if ((int)vals.size() > Core::MAX_NUM_NODE_SLL) {
        return ExitMess::FAIL_LL_SIZE_OOB;
    }
    for (int i = 0; i < (int)vals.size(); ++i) {
        if (vals[i] < Core::NODE_MIN_VALUE || vals[i] > Core::NODE_MAX_VALUE) {
            return ExitMess::FAIL_VALUE_OOB;
        }
    }

    ALOG->clearGroup();
    ALOG->resetCode();

    clearSaparated();
    destroy();

    // Initialize
    GraphicDoublyNode* curr = pHead;
    for (int i = 0; i < (int)vals.size(); ++i) {
        if (pHead == nullptr) {
            pHead = new GraphicDoublyNode(Graphic::SLL_ORG_X, Graphic::SLL_ORG_Y, Graphic::NODE_SIZE, false, vals[i]);
            pHead->setSubText("head");
            curr = pHead;
        } else {
            GraphicDoublyNode* newNode = new GraphicDoublyNode(curr->x + Graphic::SLL_NODE_DIST, curr->y, Graphic::NODE_SIZE, false, vals[i]);
            curr->setNext(newNode);
            newNode->setPrev(curr);
            curr = curr->pNext;
        }
    }
    _size = (int)vals.size();

    ALOG->addNewGroup();
    for (GraphicDoublyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        ALOG->animateFadeIn(curr);
        ALOG->animateFadeIn(&curr->aPrev);
        ALOG->animateFadeIn(&curr->aNext);
    }

    ALOG->addNewGroup();
    for (GraphicDoublyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        ALOG->animateSlideIn(&curr->aNext);
        ALOG->animateSlideIn(&curr->aPrev);
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicDoublyLinkedList::initialize(std::string strVals, ListOfOperationsGroups<GraphicDoublyLinkedList>* ALOG) {
    std::pair<ExitStatus, std::vector<int>> input = User::input2vector(strVals, Valid::DIGIT + " ,");
    if (input.first.success) {
        return initialize(input.second, ALOG);
    } else {
        return input.first;
    }
}

ExitStatus GraphicDoublyLinkedList::searchFirst(int val, ListOfOperationsGroups<GraphicDoublyLinkedList>* ALOG) {
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::DLL_SEARCH_FIRST);

    reset();

    if (pHead == nullptr) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateDelay();
        return ExitMess::SUCCESS;
    }

    int id = 0;
    GraphicDoublyNode* pre = nullptr;
    GraphicDoublyNode* curr = pHead;

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({1, 2});
    ALOG->animateNodeFromNormalToIter(pHead);
    ALOG->animateTransText(&pHead->sub, "head", "0/head/cur");

    while (curr->nVal != val) {
        pre = curr;
        curr = curr->pNext;
        id++; 

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({3});
        ALOG->animateNodeFromIterToNearIter(pre);

        if (curr != nullptr) {
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({4, 5});
            pre->aNext.pSlideColor = &Theme::currTheme.ARROW_LINE_FOCUS_ITER;
            if (pre == pHead) {
                ALOG->animateTransText(&pre->sub, "0/head/cur", "head");
            } else {
                ALOG->animateTransText(&pre->sub, cf::num2str(id-1) + "/cur", "");
            }
            ALOG->animateSlideColorIn(&pre->aNext);
            ALOG->animateNodeFromNormalToIter(curr);
            ALOG->animateTransText(&curr->sub, "", cf::num2str(id) + "/cur");
        }

        if (curr == nullptr) {
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({5, 6});
            if (pre == pHead) {
                ALOG->animateTransText(&pre->sub, "0/head/cur", "head");
            } else {
                ALOG->animateTransText(&pre->sub, cf::num2str(id-1) + "/cur", "");
            }
            return ExitMess::SUCCESS;
        }
    }

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({8});
    ALOG->animateDelay();

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicDoublyLinkedList::updateValue(int k, int val, ListOfOperationsGroups<GraphicDoublyLinkedList>* ALOG) {
    if (_size == 0) {
        return ExitMess::FAIL_LL_EMPTY;
    }
    if (k < 0 || k >= _size) {
        return ExitStatus(false, "i is out of bounds: Allow from 0 to " + cf::num2str(_size-1));
    } 
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::DLL_UPDATE);
    reset();

    GraphicDoublyNode* pre = nullptr;
    GraphicDoublyNode* curr = pHead;
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({0});
    ALOG->animateNodeFromNormalToIter(curr);
    
    for (int i = 0; i < k; ++i) {
        pre = curr;
        curr = curr->pNext;

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        ALOG->animateNodeFromIterToNearIter(pre);

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        pre->aNext.pSlideColor = &Theme::currTheme.ARROW_LINE_FOCUS_ITER;
        ALOG->animateSlideColorIn(&pre->aNext);
        ALOG->animateNodeFromNormalToIter(curr);
    }

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({4});
    ALOG->animateNodeFromIterToFocus(curr);
    ALOG->animateAssignValue(curr, curr->nVal, val);

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicDoublyLinkedList::pushFront(int val, ListOfOperationsGroups<GraphicDoublyLinkedList>* ALOG) {
    if (_size == Core::MAX_NUM_NODE_SLL) {
        return ExitMess::FAIL_LL_REACH_MAX_SIZE;
    }
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::DLL_INSERT_FORD);
    reset();

    _size++;

    if (pHead == nullptr) {
        // line number 0
        pHead = new GraphicDoublyNode(Graphic::SLL_ORG_X, Graphic::SLL_ORG_Y + Graphic::SLL_NODE_DIST, Graphic::NODE_SIZE, false, val);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateFadeIn(pHead);
        ALOG->animateNodeFromNormalToIter(pHead);
        ALOG->animateTransText(&pHead->sub, "", "node");
        // ---

        // line number 1
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1,2});
        ALOG->animateDelay();
        // ---

        // line number 2
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({4});
        ALOG->animateNodeFromIterToFocus(pHead);
        ALOG->animateTransText(&pHead->sub, "node", "head/node");
        // ---

        // transform
        ALOG->addNewGroup();
        ALOG->animateTransform(pHead, pHead->x, pHead->y, 0, -Graphic::SLL_NODE_DIST);
        // ---
    } else {
        // line number 0
        GraphicDoublyNode* newNode = new GraphicDoublyNode(Graphic::SLL_ORG_X, Graphic::SLL_ORG_Y + Graphic::SLL_NODE_DIST, Graphic::NODE_SIZE, false, val);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateFadeIn(newNode);
        ALOG->animateNodeFromNormalToIter(newNode);
        ALOG->animateTransText(&newNode->sub, "", "node");
        // ---

        // line number 1
        newNode->setNext(pHead);
        pHead->setPrev(newNode);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1,2,3});
        ALOG->animateFadeIn(&newNode->aNext);
        ALOG->animateArrowFromNormalToIter(&newNode->aNext);
        ALOG->animateSlideIn(&newNode->aNext);
        ALOG->animateFadeIn(&pHead->aPrev);
        ALOG->animateArrowFromNormalToIter(&pHead->aPrev);
        ALOG->animateSlideIn(&pHead->aPrev);
        // ---

        // line number 2
        pHead = newNode;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({4});
        ALOG->animateNodeFromIterToFocus(pHead);
        ALOG->animateArrowFromIterToNormal(&pHead->aNext);
        ALOG->animateArrowFromIterToNormal(&pHead->pNext->aPrev);
        ALOG->animateTransText(&pHead->pNext->sub, "head", "");
        ALOG->animateTransText(&pHead->sub, "node", "head/node");
        // ---

        // transform
        ALOG->addNewGroup();
        ALOG->animateTransform(pHead, pHead->x, pHead->y, 0, -Graphic::SLL_NODE_DIST);
        for (GraphicDoublyNode* curr = pHead->pNext; curr != nullptr; curr = curr->pNext) {
            ALOG->animateTransform(curr, curr->x, curr->y, Graphic::SLL_NODE_DIST, 0);
        }
    }

    ALOG->build();
    
    return ExitMess::SUCCESS;
}

ExitStatus GraphicDoublyLinkedList::pushBack(int val, ListOfOperationsGroups<GraphicDoublyLinkedList>* ALOG) {
        if (_size == Core::MAX_NUM_NODE_SLL) {
        return ExitMess::FAIL_LL_REACH_MAX_SIZE;
    }
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }

    if (_size == 0) {
        return pushFront(val, ALOG);
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::DLL_INSERT_BACK);
    reset();

    _size++;

    GraphicDoublyNode* pre = nullptr;
    GraphicDoublyNode* curr = pHead;    

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({0});
    ALOG->animateNodeFromNormalToIter(curr);
    ALOG->animateTransText(&curr->sub, "head", "head/cur");

    while (curr->pNext != nullptr) {
        pre = curr;
        curr = curr->pNext;

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        ALOG->animateNodeFromIterToNearIter(pre);

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        ALOG->animateNodeFromNormalToIter(curr);
        pre->aNext.pSlideColor = &Theme::currTheme.ARROW_LINE_FOCUS_ITER;
        ALOG->animateSlideColorIn(&pre->aNext);
        if (pre == pHead) {
            ALOG->animateTransText(&pre->sub, "head/cur", "head");
        } else {
            ALOG->animateTransText(&pre->sub, "cur", "");
        }
        ALOG->animateTransText(&curr->sub, "", "cur");
    }

    GraphicDoublyNode* newNode = new GraphicDoublyNode(curr->x + Graphic::SLL_NODE_DIST, Graphic::SLL_ORG_Y, Graphic::NODE_SIZE, false, val);
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({3});
    ALOG->animateFadeIn(newNode);
    ALOG->animateNodeFromNormalToFocus(newNode);
    ALOG->animateTransText(&newNode->sub, "", "node");
    
    curr->setNext(newNode);
    newNode->setPrev(curr);
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({4,5});
    ALOG->animateNodeFromIterToNearIter(curr);
    ALOG->animateFadeIn(&curr->aNext);
    ALOG->animateArrowFromNormalToFocus(&curr->aNext);
    ALOG->animateSlideIn(&curr->aNext);
    ALOG->animateFadeIn(&newNode->aPrev);
    ALOG->animateArrowFromNormalToFocus(&newNode->aPrev);
    ALOG->animateSlideIn(&newNode->aPrev);

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicDoublyLinkedList::pushAtKth(int k, int val, ListOfOperationsGroups<GraphicDoublyLinkedList>* ALOG) {
    if (_size == Core::MAX_NUM_NODE_SLL) {
        return ExitMess::FAIL_LL_REACH_MAX_SIZE;
    }
    if (k < 0 || k > _size) {
        return ExitStatus(false, "i is out of bounds: Allow from 0 to " + cf::num2str(_size));
    }
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }

    if (k == 0) {
        return pushFront(val, ALOG);
    }
    if (k == _size) {
        return pushBack(val, ALOG);
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::DLL_INSERT_KTH);

    reset();

    _size++;

    GraphicDoublyNode* prepre = nullptr;
    GraphicDoublyNode* pre = pHead;
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({0});
    ALOG->animateNodeFromNormalToIter(pre);
    ALOG->animateTransText(&pre->sub, "head", "0/head/pre");

    for (int i = 0; i < k-1; ++i) {
        prepre = pre;
        pre = pre->pNext;

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        ALOG->animateNodeFromIterToNearIter(prepre);
        prepre->aNext.pSlideColor = &Theme::currTheme.ARROW_LINE_FOCUS_ITER;
        ALOG->animateSlideColorIn(&prepre->aNext);

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        ALOG->animateNodeFromNormalToIter(pre);
        if (prepre == pHead) {
            ALOG->animateTransText(&prepre->sub, "0/head/pre", "head");
        } else {
            ALOG->animateTransText(&prepre->sub, cf::num2str(i) + "/pre", "");
        }
        ALOG->animateTransText(&pre->sub, "", cf::num2str(i+1) + "/pre");
    }

    GraphicDoublyNode* nxt = pre->pNext;
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({3});
    ALOG->animateNodeFromNormalToRefer(nxt);
    pre->aNext.pSlideColor = &Theme::currTheme.ARROW_LINE_FOCUS_ITER;
    ALOG->animateSlideColorIn(&pre->aNext);
    ALOG->animateTransText(&nxt->sub, "", cf::num2str(k) + "/nxt");

    GraphicDoublyNode* cur = new GraphicDoublyNode(nxt->x, Graphic::SLL_ORG_Y + Graphic::SLL_NODE_DIST, Graphic::NODE_SIZE, false, val);
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({4});
    ALOG->animateFadeIn(cur);
    ALOG->animateNodeFromNormalToFocus(cur);
    ALOG->animateTransText(&cur->sub, "", "cur");

    GraphicTrackArrow tmpArrow;
    tmpArrow.copyAttributes(&nxt->aPrev);

    cur->setNext(nxt);
    nxt->setPrev(cur);
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({5,6});
    ALOG->animateFadeIn(&cur->aNext);
    ALOG->animateArrowFromNormalToFocus(&cur->aNext);
    ALOG->animateSlideIn(&cur->aNext);
    ALOG->animateFadeIn(&nxt->aPrev);
    ALOG->animateArrowFromNormalToFocus(&nxt->aPrev);
    ALOG->animateSlideIn(&nxt->aPrev);

    pre->updateNext(cur);
    pre->setArrowHeadTrans(&pre->aNext, nxt);
    cur->setPrev(pre);
    cur->aPrev.copyAttributes(&tmpArrow);
    cur->setArrowTailTrans(&cur->aPrev, nxt);
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({7,8});
    ALOG->animateRedirectHead(pre, &pre->aNext, nxt);
    ALOG->animateRedirectTail(cur, &cur->aPrev, nxt);
    ALOG->animateTransText(&cur->sub, "cur", cf::num2str(k) + "/cur");
    ALOG->animateTransText(&nxt->sub, cf::num2str(k) + "/nxt", cf::num2str(k+1) + "/nxt");

    ALOG->addNewGroup();
    ALOG->animateTransform(cur, cur->x, cur->y, 0, -Graphic::SLL_NODE_DIST);
    ALOG->animateNodeFromIterToNormal(pre);
    ALOG->animateArrowSlideFromIterToNormal(&pre->aNext);
    ALOG->animateNodeFromReferToNormal(nxt);
    ALOG->animateArrowFromFocusToNormal(&cur->aNext);
    ALOG->animateArrowFromFocusToNormal(&nxt->aPrev);
    ALOG->animateTransText(&pre->sub, cf::num2str(k-1) + "/pre", "");
    ALOG->animateTransText(&nxt->sub, cf::num2str(k+1) + "/nxt", "");
    for (GraphicDoublyNode* iter = pHead; iter != pre; iter = iter->pNext) {
        ALOG->animateNodeFromNearIterToNormal(iter);
        ALOG->animateSlideColorOut(&iter->aNext);
    }
    for (; nxt != nullptr; nxt = nxt->pNext) {
        ALOG->animateTransform(nxt, nxt->x, nxt->y, Graphic::SLL_NODE_DIST, 0);
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicDoublyLinkedList::popFront(ListOfOperationsGroups<GraphicDoublyLinkedList>* ALOG) {
    ALOG->clearGroup();
    ALOG->loadCode(CPath::DLL_REMOVE_FORD);
    reset();

    if (pHead == nullptr) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateDelay();
    } else {
        _size--;
        GraphicDoublyNode* tmp = pHead;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        ALOG->animateNodeFromNormalToIter(tmp);
        ALOG->animateTransText(&tmp->sub, "head", "head/tmp");

        nodes.push_back(tmp);
        pHead = pHead->pNext;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        if (pHead != nullptr) {
            ALOG->animateNodeFromNormalToFocus(pHead);
            tmp->aNext.pSlideColor = &Theme::currTheme.ARROW_LINE_FOCUS_ITER;
            ALOG->animateSlideColorIn(&tmp->aNext);
            ALOG->animateTransText(&pHead->sub, "", "head");
        }
        ALOG->animateTransText(&tmp->sub, "head/tmp", "tmp");

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({3});
        ALOG->animateFadeOut(tmp);
        ALOG->animateFadeOut(&tmp->aNext);
        ALOG->animateSlideOut(&tmp->aNext);
        if (pHead != nullptr) {
            ALOG->animateSlideOut(&pHead->aPrev);
        }

        if (pHead != nullptr) {
            pHead->pPrev = nullptr;
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({4});
            for (GraphicDoublyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
                ALOG->animateTransform(curr, curr->x, curr->y, -Graphic::SLL_NODE_DIST, 0);
            }
        }
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicDoublyLinkedList::popBack(ListOfOperationsGroups<GraphicDoublyLinkedList>* ALOG) {
    if (_size == 1) {
        return popFront(ALOG);
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::DLL_REMOVE_BACK);
    reset();

    if (pHead == nullptr) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateDelay();
    } else {
        _size--;

        GraphicDoublyNode* tmp = pHead;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        ALOG->animateNodeFromNormalToIter(tmp);
        ALOG->animateTransText(&tmp->sub, "head", "head/tmp");

        while (true) {
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({2});
            ALOG->animateNodeFromIterToNearIter(tmp);

            if (tmp->pNext == nullptr) {
                break;
            }

            tmp = tmp->pNext;
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({3});
            ALOG->animateSlideColorIn(&tmp->pPrev->aNext);
            ALOG->animateArrowSlideFromNormalToIter(&tmp->pPrev->aNext);
            ALOG->animateNodeFromNormalToIter(tmp);
            if (tmp->pPrev == pHead) {
                ALOG->animateTransText(&tmp->pPrev->sub, "head/pre", "head");
            } else {
                ALOG->animateTransText(&tmp->pPrev->sub, "pre", "");
            }
            ALOG->animateTransText(&tmp->sub, "", "tmp");
        }

        nodes.push_back(tmp);
        arrows.push_back(&tmp->pPrev->aNext);
        tmp->pPrev->pNext = nullptr;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({4});
        ALOG->animateSlideOut(&tmp->pPrev->aNext);
        ALOG->animateSlideOut(&tmp->aPrev);

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({5});
        ALOG->animateFadeOut(tmp);
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicDoublyLinkedList::popAtKth(int k, ListOfOperationsGroups<GraphicDoublyLinkedList>* ALOG) {
    if (_size == 0) {
        return ExitMess::FAIL_LL_EMPTY;
    }
    if (k < 0 || k >= _size) {
        return ExitStatus(false, "i is out of bounds: Allow from 0 to " + cf::num2str(_size-1));
    }

    if (k == 0) {
        return popFront(ALOG);
    }
    if (k == _size-1) {
        return popBack(ALOG);
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::DLL_REMOVE_KTH);
    reset();

    _size--;

    GraphicDoublyNode* tmp = pHead;
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({1});
    ALOG->animateNodeFromNormalToIter(tmp);
    ALOG->animateTransText(&tmp->sub, "head", "0/head/tmp");

    for (int i = 0; i < k; ++i) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        ALOG->animateArrowSlideFromNormalToIter(&tmp->aNext);
        ALOG->animateSlideColorIn(&tmp->aNext);
        ALOG->animateNodeFromIterToNearIter(tmp);

        tmp = tmp->pNext;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({3});
        ALOG->animateNodeFromNormalToIter(tmp);
        if (tmp->pPrev == pHead) {
            ALOG->animateTransText(&tmp->pPrev->sub, "0/head/tmp", "head");
        } else {
            ALOG->animateTransText(&tmp->pPrev->sub, cf::num2str(i) + "/tmp", "");
        }
        ALOG->animateTransText(&tmp->sub, "", cf::num2str(i+1) + "/tmp");
    }

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({2});
    ALOG->animateDelay();

    GraphicDoublyNode* pre = tmp->pPrev;
    GraphicDoublyNode* nxt = tmp->pNext;
    pre->updateNext(nxt);
    nxt->updatePrev(pre);
    tmp->setRevPrev(nxt);
    tmp->aPrev.appear();
    tmp->aPrev.maximize();
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({4,5});
    ALOG->animateArrowSlideFromNormalToIter(&nxt->aPrev);
    ALOG->animateArrowSlideFromNormalToIter(&tmp->aNext);
    ALOG->animateSlideColorIn(&nxt->aPrev);
    ALOG->animateSlideColorIn(&tmp->aNext);
    ALOG->animateNodeFromIterToRemove(tmp);
    ALOG->animateNodeFromNearIterToIter(pre);
    ALOG->animateNodeFromNormalToFocus(nxt);
    ALOG->animateTransText(&pre->sub, "", cf::num2str(k-1) + "/pre");
    ALOG->animateTransText(&nxt->sub, "", cf::num2str(k+1) + "/nxt");

    nodes.push_back(tmp);
    pre->setArrowHeadTrans(&pre->aNext, tmp);
    nxt->setArrowTailTrans(&nxt->aPrev, tmp);
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({6,7});
    ALOG->animateTransform(tmp, tmp->x, tmp->y, 0, Graphic::SLL_NODE_DIST);
    ALOG->animateRedirectHead(pre, &pre->aNext, tmp);
    ALOG->animateRedirectTail(nxt, &nxt->aPrev, tmp);
    ALOG->animateTransText(&tmp->sub, cf::num2str(k) + "/tmp", "tmp");
    ALOG->animateTransText(&nxt->sub, cf::num2str(k+1) + "/nxt", cf::num2str(k) + "/nxt");
    
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({8});
    ALOG->animateFadeOut(tmp);
    ALOG->animateFadeOut(&tmp->aNext);
    ALOG->animateSlideOut(&tmp->aNext);
    ALOG->animateFadeOut(&tmp->aPrev);
    ALOG->animateSlideOut(&tmp->aPrev);

    ALOG->addNewGroup();
    for (GraphicDoublyNode* iter = pHead; iter != pre; iter = iter->pNext) {
        ALOG->animateNodeFromNearIterToNormal(iter);
        ALOG->animateArrowSlideFromIterToNormal(&iter->aNext);
    }
    ALOG->animateArrowSlideFromIterToNormal(&pre->aNext);
    ALOG->animateArrowSlideFromIterToNormal(&nxt->aPrev);
    ALOG->animateTransText(&pre->sub, cf::num2str(k-1) + "/pre", "");
    ALOG->animateTransText(&nxt->sub, cf::num2str(k) + "/nxt", "");
    for (; nxt != nullptr; nxt = nxt->pNext) {
        ALOG->animateTransform(nxt, nxt->x, nxt->y, -Graphic::SLL_NODE_DIST, 0);
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

void GraphicDoublyLinkedList::reset() {
    clearSaparated();
    clearArrows();
    resetColorAllNodes();
    resetSubTextAllNodes();
}

void GraphicDoublyLinkedList::clearSaparated() {
    for (GraphicDoublyNode* node : nodes) {
        delete node;
    }
    nodes.clear();
}

void GraphicDoublyLinkedList::clearArrows() {
    for (GraphicTrackArrow* arrow : arrows) {
        arrow->isTrack = false;
    }
    arrows.clear();
}

void GraphicDoublyLinkedList::draw() {
    for (GraphicDoublyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        curr->draw();
    }
    for (GraphicDoublyNode* node : nodes) {
        node->draw();
    }
}

void GraphicDoublyLinkedList::destroy() {
    while (pHead != nullptr) {
        GraphicDoublyNode* tmp = pHead;
        pHead = pHead->pNext;
        delete tmp;
    }
    for (GraphicDoublyNode* curr : nodes) {
        delete curr;
    }
    nodes.clear();
    arrows.clear();
}
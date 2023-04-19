#include "GraphicSinglyLinkedList.h"

GraphicSinglyLinkedList::GraphicSinglyLinkedList() {
    pHead = nullptr;
    _size = 0;
}

void GraphicSinglyLinkedList::resetColorAllNodes() {
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        curr->resetColor();
        curr->aNext.resetColor();
    }
}

void GraphicSinglyLinkedList::resetSubTextAllNodes() {
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        if (curr == pHead) {
            curr->setSubText("head");
        } else {
            curr->setSubText("");
        }
    }
}

void GraphicSinglyLinkedList::vanishAllNodes() {
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        curr->vanish();
        curr->aNext.vanish();
    }
}

void GraphicSinglyLinkedList::appearAllNodes() {
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        curr->appear();
        curr->aNext.appear();
    }
}

bool GraphicSinglyLinkedList::empty() const {
    return _size == 0;
}

int GraphicSinglyLinkedList::size() const {
    return _size;
}

ExitStatus GraphicSinglyLinkedList::initialize(int initSize, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) { // Randomly initialize
    if (initSize < 0 || initSize > Core::MAX_NUM_NODE_SLL) {
        return ExitMess::FAIL_LL_SIZE_OOB;
    }
    std::vector<int> vals;
    for (int i = 0; i < initSize; ++i) {
        vals.push_back(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
    }
    return initialize(vals, ALOG);
}

ExitStatus GraphicSinglyLinkedList::initialize(std::vector<int> vals, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) { // Initialize with given values
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
    GraphicSinglyNode* curr = pHead;
    for (int i = 0; i < (int)vals.size(); ++i) {
        if (pHead == nullptr) {
            pHead = new GraphicSinglyNode(Graphic::SLL_ORG_X, Graphic::SLL_ORG_Y, Graphic::NODE_SIZE, false, vals[i]);
            pHead->setSubText("head");
            curr = pHead;
        } else {
            GraphicSinglyNode* newNode = new GraphicSinglyNode(curr->x + Graphic::SLL_NODE_DIST, curr->y, Graphic::NODE_SIZE, false, vals[i]);
            curr->setNext(newNode);
            curr = curr->pNext;
        }
    }
    _size = (int)vals.size();

    ALOG->addNewGroup();
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        ALOG->animateFadeIn(curr);
        ALOG->animateFadeIn(&curr->aNext);
    }

    ALOG->addNewGroup();
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        ALOG->animateSlideIn(&curr->aNext);
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicSinglyLinkedList::initialize(std::string strVals, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) {
    std::pair<ExitStatus, std::vector<int>> input = User::input2vector(strVals, Valid::DIGIT + " ,");
    if (input.first.success) {
        return initialize(input.second, ALOG);
    } else {
        return input.first;
    }
}

ExitStatus GraphicSinglyLinkedList::searchFirst(int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) {
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::SLL_SEARCH_FIRST);

    reset();

    if (pHead == nullptr) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateDelay();
        return ExitMess::SUCCESS;
    }

    int id = 0;
    GraphicSinglyNode* pre = nullptr;
    GraphicSinglyNode* curr = pHead;

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

ExitStatus GraphicSinglyLinkedList::updateHeadValue(int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) {
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }
    
    ALOG->clearGroup();
    ALOG->loadCode(CPath::SLL_UPDATE_HEAD);
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


ExitStatus GraphicSinglyLinkedList::updateValue(int k, int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) {
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
    ALOG->loadCode(CPath::SLL_UPDATE);
    reset();

    GraphicSinglyNode* pre = nullptr;
    GraphicSinglyNode* curr = pHead;
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

ExitStatus GraphicSinglyLinkedList::peek(ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) {
    ALOG->clearGroup();
    ALOG->loadCode(CPath::SLL_PEEK);
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


ExitStatus GraphicSinglyLinkedList::pushFront(int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) {
    if (_size == Core::MAX_NUM_NODE_SLL) {
        return ExitMess::FAIL_LL_REACH_MAX_SIZE;
    }
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::SLL_INSERT_FORD);
    reset();

    _size++;

    if (pHead == nullptr) {
        // line number 0
        pHead = new GraphicSinglyNode(Graphic::SLL_ORG_X, Graphic::SLL_ORG_Y + Graphic::SLL_NODE_DIST, Graphic::NODE_SIZE, false, val);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateFadeIn(pHead);
        ALOG->animateNodeFromNormalToIter(pHead);
        ALOG->animateTransText(&pHead->sub, "", "node");
        // ---

        // line number 1
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        ALOG->animateDelay();
        // ---

        // line number 2
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        ALOG->animateNodeFromIterToFocus(pHead);
        ALOG->animateTransText(&pHead->sub, "node", "head/node");
        // ---

        // transform
        ALOG->addNewGroup();
        ALOG->animateTransform(pHead, pHead->x, pHead->y, 0, -Graphic::SLL_NODE_DIST);
        // ---
    } else {
        // line number 0
        GraphicSinglyNode* newNode = new GraphicSinglyNode(Graphic::SLL_ORG_X, Graphic::SLL_ORG_Y + Graphic::SLL_NODE_DIST, Graphic::NODE_SIZE, false, val);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateFadeIn(newNode);
        ALOG->animateNodeFromNormalToIter(newNode);
        ALOG->animateTransText(&newNode->sub, "", "node");
        // ---

        // line number 1
        newNode->setNext(pHead);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        ALOG->animateSlideIn(&newNode->aNext);
        ALOG->animateFadeIn(&newNode->aNext);
        ALOG->animateArrowFromNormalToIter(&newNode->aNext);
        // ---

        // line number 2
        pHead = newNode;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        ALOG->animateNodeFromIterToFocus(pHead);
        ALOG->animateArrowFromIterToNormal(&pHead->aNext);
        ALOG->animateTransText(&pHead->pNext->sub, "head", "");
        ALOG->animateTransText(&pHead->sub, "node", "head/node");
        // ---

        // transform
        ALOG->addNewGroup();
        ALOG->animateTransform(pHead, pHead->x, pHead->y, 0, -Graphic::SLL_NODE_DIST);
        for (GraphicSinglyNode* curr = pHead->pNext; curr != nullptr; curr = curr->pNext) {
            ALOG->animateTransform(curr, curr->x, curr->y, Graphic::SLL_NODE_DIST, 0);
        }
    }

    ALOG->build();
    
    return ExitMess::SUCCESS;
}

ExitStatus GraphicSinglyLinkedList::pushBack(int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) {
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
    ALOG->loadCode(CPath::SLL_INSERT_BACK);
    reset();

    _size++;

    GraphicSinglyNode* pre = nullptr;
    GraphicSinglyNode* curr = pHead;    

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

    GraphicSinglyNode* newNode = new GraphicSinglyNode(curr->x + Graphic::SLL_NODE_DIST, Graphic::SLL_ORG_Y, Graphic::NODE_SIZE, false, val);
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({3});
    ALOG->animateFadeIn(newNode);
    ALOG->animateNodeFromNormalToFocus(newNode);
    ALOG->animateTransText(&newNode->sub, "", "node");
    
    curr->setNext(newNode);
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({4});
    ALOG->animateSlideIn(&curr->aNext);
    ALOG->animateFadeIn(&curr->aNext);
    ALOG->animateNodeFromIterToNearIter(curr);
    ALOG->animateArrowFromNormalToFocus(&curr->aNext);

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicSinglyLinkedList::pushAtKth(int k, int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) {
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
    ALOG->loadCode(CPath::SLL_INSERT_KTH);

    reset();

    _size++;

    GraphicSinglyNode* prepre = nullptr;
    GraphicSinglyNode* pre = pHead;
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

    GraphicSinglyNode* nxt = pre->pNext;
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({3});
    ALOG->animateNodeFromNormalToRefer(nxt);
    pre->aNext.pSlideColor = &Theme::currTheme.ARROW_LINE_FOCUS_ITER;
    ALOG->animateSlideColorIn(&pre->aNext);
    ALOG->animateTransText(&nxt->sub, "", cf::num2str(k) + "/nxt");

    GraphicSinglyNode* cur = new GraphicSinglyNode(nxt->x, Graphic::SLL_ORG_Y + Graphic::SLL_NODE_DIST, Graphic::NODE_SIZE, false, val);
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({4});
    ALOG->animateFadeIn(cur);
    ALOG->animateNodeFromNormalToFocus(cur);
    ALOG->animateTransText(&cur->sub, "", "cur");

    cur->setNext(nxt);
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({5});
    ALOG->animateFadeIn(&cur->aNext);
    ALOG->animateArrowFromNormalToFocus(&cur->aNext);
    ALOG->animateSlideIn(&cur->aNext);

    pre->updateNext(cur);
    pre->setNextArrowTrans(nxt);
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({6});
    ALOG->animateRedirectHead(pre, &pre->aNext, nxt);
    ALOG->animateTransText(&cur->sub, "cur", cf::num2str(k) + "/cur");
    ALOG->animateTransText(&nxt->sub, cf::num2str(k) + "/nxt", cf::num2str(k+1) + "/nxt");

    ALOG->addNewGroup();
    ALOG->animateTransform(cur, cur->x, cur->y, 0, -Graphic::SLL_NODE_DIST);
    ALOG->animateNodeFromIterToNormal(pre);
    ALOG->animateArrowSlideFromIterToNormal(&pre->aNext);
    ALOG->animateNodeFromReferToNormal(nxt);
    ALOG->animateArrowFromFocusToNormal(&cur->aNext);
    ALOG->animateTransText(&pre->sub, cf::num2str(k-1) + "/pre", "");
    ALOG->animateTransText(&nxt->sub, cf::num2str(k+1) + "/nxt", "");
    for (GraphicSinglyNode* iter = pHead; iter != pre; iter = iter->pNext) {
        ALOG->animateNodeFromNearIterToNormal(iter);
        ALOG->animateSlideColorOut(&iter->aNext);
    }
    for (; nxt != nullptr; nxt = nxt->pNext) {
        ALOG->animateTransform(nxt, nxt->x, nxt->y, Graphic::SLL_NODE_DIST, 0);
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicSinglyLinkedList::popFront(ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) {
    ALOG->clearGroup();
    ALOG->loadCode(CPath::SLL_REMOVE_FORD);
    reset();

    if (pHead == nullptr) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateDelay();
    } else {
        _size--;
        GraphicSinglyNode* tmp = pHead;
        nodes.push_back(tmp);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        ALOG->animateNodeFromNormalToIter(tmp);
        ALOG->animateTransText(&tmp->sub, "head", "head/tmp");

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
            ALOG->addNewGroup();
            for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
                ALOG->animateTransform(curr, curr->x, curr->y, -Graphic::SLL_NODE_DIST, 0);
            }
        }
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicSinglyLinkedList::popBack(ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) {
    if (_size == 1) {
        return popFront(ALOG);
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::SLL_REMOVE_BACK);
    reset();

    if (pHead == nullptr) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateDelay();
    } else {
        _size--;
        GraphicSinglyNode* prepre = nullptr;
        GraphicSinglyNode* pre = pHead;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        ALOG->animateNodeFromNormalToIter(pre);
        ALOG->animateTransText(&pre->sub, "head", "head/pre");

        GraphicSinglyNode* tmp = pHead->pNext;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        ALOG->animateNodeFromNormalToFocus(tmp);
        pre->aNext.pSlideColor = &Theme::currTheme.ARROW_LINE_FOCUS_ITER;
        ALOG->animateSlideColorIn(&pre->aNext);
        ALOG->animateTransText(&tmp->sub, "", "tmp");

        while (true) {
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({3});
            ALOG->animateArrowSlideFromIterToNormal(&pre->aNext);
            ALOG->animateSlideColorOut(&pre->aNext);

            if (tmp->pNext == nullptr) {
                break;
            }

            prepre = pre;
            pre = tmp;
            tmp = tmp->pNext;


            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({4,5});
            ALOG->animateNodeFromIterToNearIter(prepre);
            ALOG->animateSlideColorIn(&prepre->aNext);
            ALOG->animateArrowSlideFromNormalToIter(&prepre->aNext);
            ALOG->animateNodeFromFocusToIter(pre);
            pre->aNext.pSlideColor = &Theme::currTheme.ARROW_LINE_FOCUS;
            ALOG->animateSlideColorIn(&pre->aNext);
            ALOG->animateNodeFromNormalToFocus(tmp);
            if (prepre == pHead) {
                ALOG->animateTransText(&prepre->sub, "head/pre", "head");
            } else {
                ALOG->animateTransText(&prepre->sub, "pre", "");
            }
            ALOG->animateTransText(&pre->sub, "tmp", "pre");
            ALOG->animateTransText(&tmp->sub, "", "tmp");
        }

        nodes.push_back(tmp);
        arrows.push_back(&pre->aNext);
        pre->pNext = nullptr;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({7});
        ALOG->animateSlideOut(&pre->aNext);

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({8});
        ALOG->animateFadeOut(tmp);
        ALOG->animateNodeFromIterToNearIter(pre);
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicSinglyLinkedList::popAtKth(int k, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) {
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
    ALOG->loadCode(CPath::SLL_REMOVE_KTH);
    reset();

    _size--;

    GraphicSinglyNode* prepre = nullptr;
    GraphicSinglyNode* pre = pHead;
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({1});
    ALOG->animateNodeFromNormalToIter(pre);
    ALOG->animateTransText(&pre->sub, "head", "0/head/pre");

    for (int i = 0; i < k-1; ++i) {
        prepre = pre;
        pre = pre->pNext;

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        ALOG->animateDelay();

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({3});
        ALOG->animateNodeFromIterToNearIter(prepre);
        prepre->aNext.pSlideColor = &Theme::currTheme.ARROW_LINE_FOCUS_ITER;
        ALOG->animateSlideColorIn(&prepre->aNext);
        ALOG->animateNodeFromNormalToIter(pre);
        if (prepre == pHead) {
            ALOG->animateTransText(&prepre->sub, "0/head/pre", "head");
        } else {
            ALOG->animateTransText(&prepre->sub, cf::num2str(i) + "/pre", "");
        }
        ALOG->animateTransText(&pre->sub, "", cf::num2str(i+1) + "/pre");
    }

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({2});
    ALOG->animateDelay();

    GraphicSinglyNode* del = pre->pNext;
    GraphicSinglyNode* nxt = del->pNext;

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({4,5});
    pre->aNext.pSlideColor = &Theme::currTheme.ARROW_LINE_FOCUS_ITER;
    ALOG->animateSlideColorIn(&pre->aNext);
    ALOG->animateNodeFromNormalToRemove(del);
    del->aNext.pSlideColor = &Theme::currTheme.ARROW_LINE_FOCUS_ITER;
    ALOG->animateSlideColorIn(&del->aNext);
    ALOG->animateNodeFromNormalToFocus(nxt);
    ALOG->animateTransText(&del->sub, "", cf::num2str(k) + "/del");
    ALOG->animateTransText(&nxt->sub, "", cf::num2str(k+1) + "/nxt");

    nodes.push_back(del);
    pre->updateNext(nxt);
    pre->setNextArrowTrans(del);
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({6});
    ALOG->animateTransform(del, del->x, del->y, 0, Graphic::SLL_NODE_DIST);
    ALOG->animateRedirectHead(pre, &pre->aNext, del);
    ALOG->animateTransText(&del->sub, cf::num2str(k) + "/del", "del");
    ALOG->animateTransText(&nxt->sub, cf::num2str(k+1) + "/nxt", cf::num2str(k) + "/nxt");
    
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({7});
    ALOG->animateFadeOut(del);
    ALOG->animateFadeOut(&del->aNext);
    ALOG->animateSlideOut(&del->aNext);

    ALOG->addNewGroup();
    for (GraphicSinglyNode* iter = pHead; iter != pre; iter = iter->pNext) {
        ALOG->animateNodeFromNearIterToNormal(iter);
        ALOG->animateArrowSlideFromIterToNormal(&iter->aNext);
    }
    ALOG->animateArrowSlideFromIterToNormal(&pre->aNext);
    ALOG->animateTransText(&pre->sub, cf::num2str(k-1) + "/pre", "");
    ALOG->animateTransText(&nxt->sub, cf::num2str(k) + "/nxt", "");
    for (; nxt != nullptr; nxt = nxt->pNext) {
        ALOG->animateTransform(nxt, nxt->x, nxt->y, -Graphic::SLL_NODE_DIST, 0);
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

void GraphicSinglyLinkedList::draw() {
    // for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
    //     std::cerr << curr->x << ' '; 
    // }
    // std::cerr << '\n';
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        curr->draw();
    }
    for (GraphicSinglyNode* node : nodes) {
        node->draw();
    }
}

void GraphicSinglyLinkedList::reset() {
    clearSaparated();
    clearArrows();
    resetColorAllNodes();
    resetSubTextAllNodes();
}

void GraphicSinglyLinkedList::clearSaparated() {
    for (GraphicSinglyNode* node : nodes) {
        delete node;
    }
    nodes.clear();
}

void GraphicSinglyLinkedList::clearArrows() {
    for (GraphicTrackArrow* curr : arrows) {
        curr->isTrack = false;
    }
    arrows.clear();
}

void GraphicSinglyLinkedList::destroy() {
    while (pHead != nullptr) {
        GraphicSinglyNode* tmp = pHead;
        pHead = pHead->pNext;
        delete tmp;
    }
    for (GraphicSinglyNode* node : nodes) {
        delete node;
    }
    nodes.clear();
    arrows.clear();
}
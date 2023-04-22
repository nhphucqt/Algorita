#include "GraphicCircularLinkedList.h"

GraphicCircularLinkedList::GraphicCircularLinkedList() {
    pHead = nullptr;
    _size = 0;
}

void GraphicCircularLinkedList::resetColorAllNodes() {
    GraphicSinglyNode* curr = pHead;
    if (curr != nullptr) do {
        curr->resetColor();
        curr->aNext.resetColor();
        curr = curr->pNext;
    } while (curr != pHead);
    harrow.resetColor();
}

void GraphicCircularLinkedList::resetSubTextAllNodes() {
    GraphicSinglyNode* curr = pHead;
    if (curr != nullptr) do {
        if (curr == pHead) {
            curr->setSubText("head");
        } else {
            curr->setSubText("");
        }
        curr = curr->pNext;
    } while (curr != pHead);
}

bool GraphicCircularLinkedList::empty() const {
    return _size == 0;
}

int GraphicCircularLinkedList::size() const {
    return _size;
}

ExitStatus GraphicCircularLinkedList::initialize(int initSize, ListOfOperationsGroups<GraphicCircularLinkedList>* ALOG) { // Randomly initialize
    if (initSize < 0 || initSize > Core::MAX_NUM_NODE_SLL) {
        return ExitMess::FAIL_LL_SIZE_OOB;
    }
    std::vector<int> vals;
    for (int i = 0; i < initSize; ++i) {
        vals.push_back(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
    }
    return initialize(vals, ALOG);
}

ExitStatus GraphicCircularLinkedList::initialize(std::vector<int> vals, ListOfOperationsGroups<GraphicCircularLinkedList>* ALOG) { // Initialize with given values
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
            pHead = new GraphicSinglyNode(Graphic::LL_ORG_X, Graphic::LL_ORG_Y, Graphic::NODE_SIZE, false, vals[i]);
            pHead->setSubText("head");
            curr = pHead;
        } else {
            GraphicSinglyNode* newNode = new GraphicSinglyNode(curr->x + Graphic::LL_NODE_DIST, curr->y, Graphic::NODE_SIZE, false, vals[i]);
            curr->setNext(newNode);
            curr = curr->pNext;
        }
    }
    _size = (int)vals.size();

    if (_size > 0) {
        harrow = GraphicHookArrow(pHead->x, pHead->y, curr->x, curr->y, pHead->size, curr->size, pHead->outerShapeIn, curr->outerShapeOut);
        // std::cerr << " >> harrow.x0y0 = " << harrow.p[0].x << ' ' << harrow.p[0].y << '\n';
        // std::cerr << " >> curr.xy = " << curr->x << ' ' << curr->y << '\n';
        // std::cerr << " >> curr.cxy = " << curr->x + curr->size/2 << ' ' << curr->y + curr->size/2 << '\n';
        // std::cerr << " >> curr.dxy = " << curr->x + curr->size << ' ' << curr->y + curr->size/2 << '\n';

        curr->pNext = pHead;
        curr = pHead;

        ALOG->addNewGroup();
        do {
            ALOG->animateFadeIn(curr);
            ALOG->animateFadeIn(&curr->aNext);
            curr = curr->pNext;
        } while (curr != pHead);
        ALOG->animateFadeIn(&harrow);

        ALOG->addNewGroup();
        do {
            ALOG->animateSlideIn(&curr->aNext);
            curr = curr->pNext;
        } while (curr != pHead);
        ALOG->animateSlideIn(&harrow);
    } else {
        ALOG->addNewGroup();
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicCircularLinkedList::initialize(std::string strVals, ListOfOperationsGroups<GraphicCircularLinkedList>* ALOG) {
    std::pair<ExitStatus, std::vector<int>> input = User::input2vector(strVals, Valid::DIGIT + " ,");
    if (input.first.success) {
        return initialize(input.second, ALOG);
    } else {
        return input.first;
    }
}

ExitStatus GraphicCircularLinkedList::searchFirst(int val, ListOfOperationsGroups<GraphicCircularLinkedList>* ALOG) {
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::CLL_SEARCH_FIRST);
    reset();

    if (pHead == nullptr) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateDelay();
    }

    int id = 0;
    GraphicSinglyNode* cur = pHead;
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({1,2});
    ALOG->animateNodeFromNormalToIter(cur);
    ALOG->animateTransText(&cur->sub, "head", "0/head/cur");

    do {
        if (cur->nVal == val) {
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({4,5});
            ALOG->animateNodeFromIterToFocus(cur);

            ALOG->build();
            return ExitMess::SUCCESS;
        } else {
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({4});
            ALOG->animateNodeFromIterToNearIter(cur);

            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({6,7,8});
            if (cur->pNext == pHead) {
                harrow.pSlideColor = &Theme::currTheme.ARROW_LINE_FOCUS_ITER;
                ALOG->animateSlideColorIn(&harrow);
                ALOG->animateNodeFromNearIterToRemove(cur->pNext);
                if (cur == pHead) {
                    ALOG->animateTransText(&cur->sub, "0/head/cur", cf::num2str(id+1) + "/head/cur");
                } else {
                    ALOG->animateTransText(&cur->sub, cf::num2str(id) + "/cur", "");
                    ALOG->animateTransText(&cur->pNext->sub, "head", cf::num2str(id+1) + "/head/cur");
                }
            } else {
                cur->aNext.pSlideColor = &Theme::currTheme.ARROW_LINE_FOCUS_ITER;
                ALOG->animateSlideColorIn(&cur->aNext);
                ALOG->animateNodeFromNormalToIter(cur->pNext);
                if (cur == pHead) {
                    ALOG->animateTransText(&cur->sub, "0/head/cur", "head");
                } else {
                    ALOG->animateTransText(&cur->sub, cf::num2str(id) + "/cur", "");
                }
                ALOG->animateTransText(&cur->pNext->sub, "", cf::num2str(id+1) + "/cur");
            }
            id++;
            cur = cur->pNext;
        }
    } while (cur != pHead);

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({9});
    ALOG->animateNodeFromRemoveToNearIter(cur);

    return ExitMess::SUCCESS;
}

ExitStatus GraphicCircularLinkedList::updateValue(int k, int val, ListOfOperationsGroups<GraphicCircularLinkedList>* ALOG) {
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
    ALOG->loadCode(CPath::CLL_UPDATE);
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

ExitStatus GraphicCircularLinkedList::pushFront(int val, ListOfOperationsGroups<GraphicCircularLinkedList>* ALOG) {
    if (_size == Core::MAX_NUM_NODE_SLL) {
        return ExitMess::FAIL_LL_REACH_MAX_SIZE;
    }
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::CLL_INSERT_FORD);
    reset();

    _size++;

    GraphicSinglyNode* vxt = new GraphicSinglyNode(Graphic::LL_ORG_X, Graphic::LL_ORG_Y - Graphic::LL_NODE_DIST, Graphic::NODE_SIZE, false, val);
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({0});
    ALOG->animateFadeIn(vxt);
    ALOG->animateNodeFromNormalToIter(vxt);
    ALOG->animateTransText(&vxt->sub, "", "vxt");

    if (pHead == nullptr) {
        vxt->pNext = vxt;
        harrow = GraphicHookArrow(vxt->x, vxt->y, vxt->x, vxt->y, vxt->size, vxt->size, vxt->outerShapeIn, vxt->outerShapeOut);
        harrow.appear();
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1,2});
        harrow.pLineColor = &Theme::currTheme.ARROW_LINE_FOCUS_ITER;
        ALOG->animateSlideIn(&harrow);

        pHead = vxt;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({10});
        ALOG->animateNodeFromIterToFocus(pHead);
        ALOG->animateTransText(&pHead->sub, "vxt", "head/vxt");
        ALOG->animateTransform(pHead, pHead->x, pHead->y, 0, Graphic::LL_NODE_DIST);
        for (int i = 0; i < Graphic::ARROW_NUM_JOIN; ++i) {
            ALOG->animateTransform(harrow.p+i, harrow.p[i].x, harrow.p[i].y, 0, Graphic::LL_NODE_DIST);
        }
        ALOG->animateArrowFromIterToNormal(&harrow);
    } else {
        vxt->setNext(pHead);
        vxt->aNext.appear();
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({3,4});
        ALOG->animateArrowFromNormalToIter(&vxt->aNext);
        ALOG->animateSlideIn(&vxt->aNext);

        GraphicSinglyNode* cur = pHead;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({5});
        ALOG->animateNodeFromNormalToIter(cur);
        ALOG->animateTransText(&cur->sub, "head", "head/cur");

        while (cur->pNext != pHead) {
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({6});
            ALOG->animateNodeFromIterToNearIter(cur);
            if (cur == pHead) {
                ALOG->animateTransText(&cur->sub, "head/cur", "head");
            } else {
                ALOG->animateTransText(&cur->sub, "cur", "");
            }

            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({7});
            cur->aNext.pSlideColor = &Theme::currTheme.ARROW_LINE_FOCUS_ITER;
            ALOG->animateSlideColorIn(&cur->aNext);
            cur = cur->pNext;
            ALOG->animateNodeFromNormalToIter(cur);
            ALOG->animateTransText(&cur->sub, "", "cur");
        }

        cur->pNext = vxt;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({8});
        for (int i = 4; i <= 5; ++i) {
            ALOG->animateTransform(harrow.p+i, harrow.p[i].x, harrow.p[i].y, 0, -Graphic::LL_NODE_DIST);
        }
        harrow.pSlideColor = &Theme::currTheme.ARROW_LINE_FOCUS_ITER;
        ALOG->animateSlideColorIn(&harrow);

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({10});
        if (pHead->pNext == vxt) {
            ALOG->animateTransText(&pHead->sub, "head/cur", "cur");
        } else {
            ALOG->animateTransText(&pHead->sub, "head", "");
        }
        pHead = vxt;
        ALOG->animateNodeFromIterToFocus(pHead);
        ALOG->animateTransText(&pHead->sub, "vxt", "head/vtx");
        ALOG->animateTransform(pHead, pHead->x, pHead->y, 0, Graphic::LL_NODE_DIST);
        ALOG->animateArrowFromIterToNormal(&pHead->aNext);
        for (int i = 4; i <= 5; ++i) {
            ALOG->animateTransform(harrow.p+i, harrow.p[i].x, harrow.p[i].y - Graphic::LL_NODE_DIST, 0, Graphic::LL_NODE_DIST);
        }
        for (int i = 0; i <= 2; ++i) {
            ALOG->animateTransform(harrow.p+i, harrow.p[i].x, harrow.p[i].y, Graphic::LL_NODE_DIST, 0);
        }
        for (GraphicSinglyNode* tmp = pHead->pNext; tmp != vxt; tmp = tmp->pNext) {
            ALOG->animateTransform(tmp, tmp->x, tmp->y, Graphic::LL_NODE_DIST, 0);
            if (tmp == cur) {
                ALOG->animateNodeFromIterToNormal(tmp);
                ALOG->animateArrowSlideFromIterToNormal(&harrow);
            } else {
                ALOG->animateNodeFromNearIterToNormal(tmp);
                ALOG->animateArrowSlideFromIterToNormal(&tmp->aNext);
            }
        }
    }
    
    ALOG->build();
    
    return ExitMess::SUCCESS;
}

ExitStatus GraphicCircularLinkedList::pushBack(int val, ListOfOperationsGroups<GraphicCircularLinkedList>* ALOG) {
    if (_size == Core::MAX_NUM_NODE_SLL) {
        return ExitMess::FAIL_LL_REACH_MAX_SIZE;
    }
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::CLL_INSERT_BACK);
    reset();

    _size++;

    if (pHead == nullptr) {
        //std::cerr << " LINE : " << __LINE__ << '\n';
        pHead = new GraphicSinglyNode(Graphic::LL_ORG_X, Graphic::LL_ORG_Y, Graphic::NODE_SIZE, false, val);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0,1});
        ALOG->animateFadeIn(pHead);
        ALOG->animateNodeFromNormalToIter(pHead);

        //std::cerr << " LINE : " << __LINE__ << '\n';
        pHead->pNext = pHead;
        harrow = GraphicHookArrow(pHead->x, pHead->y, pHead->x, pHead->y, pHead->size, pHead->size, pHead->outerShapeIn, pHead->outerShapeOut);
        harrow.appear();
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        ALOG->animateNodeFromIterToFocus(pHead);
        ALOG->animateSlideIn(&harrow);
    } else {
        //std::cerr << " LINE : " << __LINE__ << '\n';
        GraphicSinglyNode* cur = pHead;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({3,4});
        ALOG->animateNodeFromNormalToIter(cur);
        ALOG->animateTransText(&cur->sub, "head", "head/cur");

        while (cur->pNext != pHead) {
            //std::cerr << " LINE : " << __LINE__ << '\n';
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({5});
            ALOG->animateNodeFromIterToNearIter(cur);
            
            //std::cerr << " LINE : " << __LINE__ << '\n';
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({6});
            cur->aNext.pSlideColor = &Theme::currTheme.ARROW_LINE_FOCUS_ITER;
            ALOG->animateSlideColorIn(&cur->aNext);
            ALOG->animateNodeFromNormalToIter(cur->pNext);
            if (cur == pHead) {
                ALOG->animateTransText(&cur->sub, "head/cur", "head");
            } else {
                ALOG->animateTransText(&cur->sub, "cur", "");
            }
            ALOG->animateTransText(&cur->pNext->sub, "", "cur");
            cur = cur->pNext;
        }

        //std::cerr << " LINE : " << __LINE__ << '\n';
        GraphicSinglyNode* vxt = new GraphicSinglyNode(cur->x, cur->y - Graphic::LL_NODE_DIST, Graphic::NODE_SIZE, false, val);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({7});
        ALOG->animateFadeIn(vxt);
        ALOG->animateNodeFromNormalToFocus(vxt);

        //std::cerr << " LINE : " << __LINE__ << '\n';
        cur->setNext(vxt);
        cur->aNext.appear();
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({8});
        ALOG->animateArrowFromNormalToFocus(&cur->aNext);
        ALOG->animateSlideIn(&cur->aNext);
        ALOG->animateSlideOut(&harrow);

        //std::cerr << " LINE : " << __LINE__ << '\n';
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({9});
        if (cur == pHead) {
            ALOG->animateTransText(&cur->sub, "head/cur", "head");
        } else {
            ALOG->animateTransText(&cur->sub, "cur", "");
        }
        ALOG->animateTransText(&cur->pNext->sub, "vxt", "cur/vxt");
        for (int i = 0; i <= 1; ++i) {
            ALOG->animateTransform(harrow.p+i, harrow.p[i].x, harrow.p[i].y, 0, -Graphic::LL_NODE_DIST);
        }
        cur = vxt;

        //std::cerr << " LINE : " << __LINE__ << '\n';
        cur->pNext = pHead;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({10});
        ALOG->animateArrowFromNormalToFocus(&harrow);
        ALOG->animateSlideIn(&harrow);

        //std::cerr << " LINE : " << __LINE__ << '\n';
        ALOG->addNewGroup();
        ALOG->animateTransform(cur, cur->x, cur->y, Graphic::LL_NODE_DIST, Graphic::LL_NODE_DIST);
        for (int i = 0; i <= 1; ++i) {
            ALOG->animateTransform(harrow.p+i, harrow.p[i].x, harrow.p[i].y - Graphic::LL_NODE_DIST, Graphic::LL_NODE_DIST, Graphic::LL_NODE_DIST);
        }
        ALOG->animateTransform(harrow.p+2, harrow.p[2].x, harrow.p[2].y, Graphic::LL_NODE_DIST, 0);
        cur = pHead;
        for (; cur->pNext != vxt; cur = cur->pNext) {
            ALOG->animateNodeFromNearIterToNormal(cur);
            ALOG->animateArrowSlideFromIterToNormal(&cur->aNext);
        }
        ALOG->animateNodeFromIterToNormal(cur);
        ALOG->animateArrowFromFocusToNormal(&cur->aNext);
        ALOG->animateArrowFromFocusToNormal(&harrow);
    }

    //std::cerr << " LINE : " << __LINE__ << '\n';

    ALOG->build();    

    return ExitMess::SUCCESS;
}

ExitStatus GraphicCircularLinkedList::pushAtKth(int k, int val, ListOfOperationsGroups<GraphicCircularLinkedList>* ALOG) {
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
    ALOG->loadCode(CPath::CLL_INSERT_KTH);
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

    GraphicSinglyNode* vxt = new GraphicSinglyNode(nxt->x, Graphic::LL_ORG_Y - Graphic::LL_NODE_DIST, Graphic::NODE_SIZE, false, val);
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({4});
    ALOG->animateFadeIn(vxt);
    ALOG->animateNodeFromNormalToFocus(vxt);
    ALOG->animateTransText(&vxt->sub, "", "vxt");

    vxt->setNext(nxt);
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({5});
    ALOG->animateFadeIn(&vxt->aNext);
    ALOG->animateArrowFromNormalToFocus(&vxt->aNext);
    ALOG->animateSlideIn(&vxt->aNext);

    pre->updateNext(vxt);
    pre->setNextArrowTrans(nxt);
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({6});
    ALOG->animateRedirectHead(pre, &pre->aNext, nxt);
    ALOG->animateTransText(&vxt->sub, "vxt", cf::num2str(k) + "/vxt");
    ALOG->animateTransText(&nxt->sub, cf::num2str(k) + "/nxt", cf::num2str(k+1) + "/nxt");

    ALOG->addNewGroup();
    ALOG->animateTransform(vxt, vxt->x, vxt->y, 0, Graphic::LL_NODE_DIST);
    ALOG->animateNodeFromIterToNormal(pre);
    ALOG->animateArrowSlideFromIterToNormal(&pre->aNext);
    ALOG->animateNodeFromReferToNormal(nxt);
    ALOG->animateArrowFromFocusToNormal(&vxt->aNext);
    ALOG->animateTransText(&pre->sub, cf::num2str(k-1) + "/pre", "");
    ALOG->animateTransText(&nxt->sub, cf::num2str(k+1) + "/nxt", "");
    for (GraphicSinglyNode* iter = pHead; iter != pre; iter = iter->pNext) {
        ALOG->animateNodeFromNearIterToNormal(iter);
        ALOG->animateSlideColorOut(&iter->aNext);
    }
    for (; nxt != pHead; nxt = nxt->pNext) {
        ALOG->animateTransform(nxt, nxt->x, nxt->y, Graphic::LL_NODE_DIST, 0);
    }
    for (int i = 0; i <= 2; ++i) {
        ALOG->animateTransform(harrow.p+i, harrow.p[i].x, harrow.p[i].y, Graphic::LL_NODE_DIST, 0);
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicCircularLinkedList::popFront(ListOfOperationsGroups<GraphicCircularLinkedList>* ALOG) {
    ALOG->clearGroup();
    ALOG->loadCode(CPath::CLL_REMOVE_FORD);
    reset();

    if (pHead == nullptr) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateDelay();
        
        ALOG->build();
        return ExitMess::SUCCESS;
    }

    _size--;

    if (pHead->pNext == pHead) {
        nodes.push_back(pHead);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1,2});
        ALOG->animateFadeOut(pHead);
        ALOG->animateSlideOut(&harrow);
        ALOG->animateFadeOut(&harrow);

        pHead = nullptr;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({3});
        ALOG->animateDelay();
    } else {
        GraphicSinglyNode* cur = pHead;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({4,5});
        ALOG->animateNodeFromNormalToIter(cur);
        ALOG->animateTransText(&cur->sub, "head", "head/cur");

        while (cur->pNext != pHead) {
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({6});
            ALOG->animateNodeFromIterToNearIter(cur);

            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({7});
            cur->aNext.pSlideColor = &Theme::currTheme.ARROW_LINE_FOCUS_ITER;
            ALOG->animateSlideColorIn(&cur->aNext);
            ALOG->animateNodeFromNormalToIter(cur->pNext);
            if (cur == pHead) {
                ALOG->animateTransText(&cur->sub, "head/cur", "head");
            } else {
                ALOG->animateTransText(&cur->sub, "cur", "");
            }
            ALOG->animateTransText(&cur->pNext->sub, "", "cur");
            cur = cur->pNext;
        }

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({8});
        ALOG->animateNodeFromNearIterToRemove(pHead);
        ALOG->animateTransText(&pHead->sub, "head", "");
        if (pHead->pNext == cur) {
            ALOG->animateTransText(&pHead->pNext->sub, "cur", "head/cur");
            ALOG->animateNodeFromIterToFocus(pHead->pNext);
        } else {
            ALOG->animateTransText(&pHead->pNext->sub, "", "head");
            ALOG->animateNodeFromNearIterToFocus(pHead->pNext);
        }
        pHead = pHead->pNext;

        nodes.push_back(cur->pNext);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({9});
        ALOG->animateFadeOut(cur->pNext);
        ALOG->animateSlideOut(&cur->pNext->aNext);
        ALOG->animateFadeOut(&cur->pNext->aNext);
        ALOG->animateSlideOut(&harrow);

        cur->pNext = pHead;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({10});
        ALOG->animateTransform(harrow.p+5, harrow.p[5].x, harrow.p[5].y, Graphic::LL_NODE_DIST, 0);
        ALOG->animateArrowFromNormalToIter(&harrow);
        ALOG->animateSlideIn(&harrow);

        GraphicSinglyNode* tmp = pHead;
        ALOG->addNewGroup();
        ALOG->animateTransform(harrow.p+5, harrow.p[5].x + Graphic::LL_NODE_DIST, harrow.p[5].y, -Graphic::LL_NODE_DIST, 0);
        for (int i = 0; i <= 2; ++i) {
            ALOG->animateTransform(harrow.p+i, harrow.p[i].x, harrow.p[i].y, -Graphic::LL_NODE_DIST, 0);
        }
        do {
            ALOG->animateTransform(tmp, tmp->x, tmp->y, -Graphic::LL_NODE_DIST, 0);
            tmp = tmp->pNext;
        } while (tmp != pHead);
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicCircularLinkedList::popBack(ListOfOperationsGroups<GraphicCircularLinkedList>* ALOG) {
    if (_size == 1) {
        return popFront(ALOG);
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::CLL_REMOVE_BACK);
    reset();

    if (pHead == nullptr) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateDelay();

        ALOG->build();
        return ExitMess::SUCCESS;
    }

    _size--;

    if (pHead->pNext == pHead) {
        nodes.push_back(pHead);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1,2});
        ALOG->animateFadeOut(pHead);
        ALOG->animateSlideOut(&pHead->aNext);

        pHead = nullptr;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({3});
        ALOG->animateDelay();
    } else {
        GraphicSinglyNode* cur = pHead;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({4,5});
        ALOG->animateNodeFromNormalToIter(cur);
        ALOG->animateTransText(&cur->sub, "head", "head/cur");

        while (cur->pNext->pNext != pHead) {
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({6});
            ALOG->animateNodeFromIterToNearIter(cur);

            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({7});
            cur->aNext.pSlideColor = &Theme::currTheme.ARROW_LINE_FOCUS_ITER;
            ALOG->animateSlideColorIn(&cur->aNext);
            ALOG->animateNodeFromNormalToIter(cur->pNext);
            if (cur == pHead) {
                ALOG->animateTransText(&cur->sub, "head/cur", "head");
            } else {
                ALOG->animateTransText(&cur->sub, "cur", "");
            }
            ALOG->animateTransText(&cur->pNext->sub, "", "cur");
            cur = cur->pNext;
        }

        GraphicSinglyNode* del = cur->pNext;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({8});
        ALOG->animateNodeFromNormalToRemove(del);
        ALOG->animateTransText(&del->sub, "", "del");

        nodes.push_back(del);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({9});
        ALOG->animateFadeOut(del);
        ALOG->animateSlideOut(&cur->aNext);
        ALOG->animateSlideColorOut(&cur->aNext);
        ALOG->animateSlideOut(&harrow);

        cur->pNext = pHead;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({10});
        for (int i = 0; i <= 2; ++i) {
            ALOG->animateTransform(harrow.p+i, harrow.p[i].x, harrow.p[i].y, -Graphic::LL_NODE_DIST, 0);
        }
        ALOG->animateSlideIn(&harrow);
        ALOG->animateArrowFromNormalToIter(&harrow);
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicCircularLinkedList::popAtKth(int k, ListOfOperationsGroups<GraphicCircularLinkedList>* ALOG) {
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
    ALOG->loadCode(CPath::CLL_REMOVE_KTH);
    reset();

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
    ALOG->animateTransform(del, del->x, del->y, 0, -Graphic::LL_NODE_DIST);
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
    for (; nxt != pHead; nxt = nxt->pNext) {
        ALOG->animateTransform(nxt, nxt->x, nxt->y, -Graphic::LL_NODE_DIST, 0);
    }
    for (int i = 0; i <= 2; ++i) {
        ALOG->animateTransform(harrow.p+i, harrow.p[i].x, harrow.p[i].y, -Graphic::LL_NODE_DIST, 0);
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

void GraphicCircularLinkedList::draw() {
    harrow.draw();
    GraphicSinglyNode* curr = pHead;
    if (curr != nullptr) do {
        curr->draw();
        curr = curr->pNext;
    } while (curr != pHead);
    for (GraphicSinglyNode* node : nodes) {
        node->draw();
    }
}

void GraphicCircularLinkedList::reset() {
    clearSaparated();
    clearArrows();
    resetColorAllNodes();
    resetSubTextAllNodes();
}

void GraphicCircularLinkedList::clearSaparated() {
    for (GraphicSinglyNode* node : nodes) {
        delete node;
    }
    nodes.clear();
}

void GraphicCircularLinkedList::clearArrows() {
    for (GraphicTrackArrow* curr : arrows) {
        curr->isTrack = false;
    }
    arrows.clear();
}

void GraphicCircularLinkedList::destroy() {
    GraphicSinglyNode* pivot = pHead;
    if (pHead != nullptr) do {
        GraphicSinglyNode* tmp = pHead;
        pHead = pHead->pNext;
        delete tmp;
    } while (pHead != pivot);
    pHead = nullptr;
    for (GraphicSinglyNode* node : nodes) {
        delete node;
    }
    _size = 0;
    nodes.clear();
    arrows.clear();
    harrow = GraphicHookArrow();
}
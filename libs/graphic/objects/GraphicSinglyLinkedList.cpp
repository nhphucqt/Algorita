#include "GraphicSinglyLinkedList.h"

GraphicSinglyLinkedList::GraphicSinglyLinkedList() {
    pHead = nullptr;
    size = 0;
}

void GraphicSinglyLinkedList::unfocusAllNodes() {
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        curr->unfocus();
        curr->unfocusBorder();
        curr->aNext.unfocus();
    }
    // std::cerr << " done unfocusAllNodes : " << ALOG->groups.size() << '\n';
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

ExitStatus GraphicSinglyLinkedList::initialize(int initSize, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) { // Randomly initialize
    if (initSize < 0 || initSize > Core::MAX_NUM_NODE_SLL) {
        return ExitStatus(false, "Size is out of bound");
    }
    std::vector<int> vals;
    for (int i = 0; i < initSize; ++i) {
        vals.push_back(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
    }
    return initialize(vals, ALOG);
}

ExitStatus GraphicSinglyLinkedList::initialize(std::vector<int> vals, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) { // Initialize with given values
    ALOG->clearGroup();
    ALOG->resetCode();

    clearSaparated();
    destroy();

    // Initialize
    GraphicSinglyNode* curr = pHead;
    for (int i = 0; i < (int)vals.size(); ++i) {
        if (pHead == nullptr) {
            pHead = new GraphicSinglyNode(Graphic::SLL_ORG_X, Graphic::SLL_ORG_Y, Graphic::NODE_SIZE, false, vals[i]);
            curr = pHead;
        } else {
            GraphicSinglyNode* newNode = new GraphicSinglyNode(curr->x + Graphic::SLL_NODE_DIST, curr->y, Graphic::NODE_SIZE, false, vals[i]);
            curr->setNext(newNode);
            curr = curr->pNext;
        }
    }
    size = (int)vals.size();

    ALOG->addNewGroup();
    ALOG->animateAppearAllNodes<GraphicSinglyLinkedList, GraphicSinglyNode>(this);
    // ---

    ALOG->addNewGroup();
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        ALOG->animateSlideIn(&curr->aNext);
    }

    ALOG->build();

    return ExitStatus(true, "");
}

ExitStatus GraphicSinglyLinkedList::searchFirst(int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) {
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitStatus(false, "Value out of range, accept from " + cf::num2str(Core::NODE_MIN_VALUE) + " to " + cf::num2str(Core::NODE_MAX_VALUE));
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::SLL_SEARCH_FIRST);

    reset();

    size++;

    if (pHead == nullptr) {
        // code line 0
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        // ---
        return ExitStatus(true, "");
    }

    int id = 0;
    GraphicSinglyNode* pre = nullptr;
    GraphicSinglyNode* curr = pHead;

    // code line 1, 2
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({1, 2});
    ALOG->animateFocus(pHead);
    ALOG->animateFocusBorder(pHead);
    // ---

    // std::cerr << "code line 4, 5\n";
    while (curr->nVal != val) {
        pre = curr;
        curr = curr->pNext;
        id++; 
        if (curr != nullptr) {
            // code line 3
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({3});
            ALOG->animateUnfocus(pre);
            // ---

            // code line 4, 5
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({4, 5});
            ALOG->animateFocus(&pre->aNext);
            ALOG->animateFocus(curr);
            ALOG->animateFocusBorder(curr);
            // ---
        }

        if (curr == nullptr) {
            // code line 5, 6
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({5, 6});
            ALOG->animateUnfocus(pre);
            // ---
            return ExitStatus(true, "");
        }
    }

    // code line 8
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({8});

    ALOG->build();

    return ExitStatus(true, "");
}

ExitStatus GraphicSinglyLinkedList::pushFront(int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) {
    if (size == Core::MAX_NUM_NODE_SLL) {
        return ExitStatus(false, "The size reach the maximum size allowed is " + cf::num2str(Core::MAX_NUM_NODE_SLL));
    }
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitStatus(false, "Value is out of range");
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::SLL_INSERT_FORD);

    reset();

    size++;

    if (pHead == nullptr) {
        // line number 0
        pHead = new GraphicSinglyNode(Graphic::SLL_ORG_X, Graphic::SLL_ORG_Y + Graphic::SLL_NODE_DIST, Graphic::NODE_SIZE, false, val);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateFadeIn(pHead);
        ALOG->animateFocus(pHead);
        ALOG->animateFocusBorder(pHead);
        // ---

        // line number 1
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        ALOG->animateDelay();
        // ---

        // line number 2
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        ALOG->animateTransform(pHead, pHead->x, pHead->y, 0, -Graphic::SLL_NODE_DIST);
        // ---
    } else {
        // line number 0
        GraphicSinglyNode* newNode = new GraphicSinglyNode(Graphic::SLL_ORG_X, Graphic::SLL_ORG_Y + Graphic::SLL_NODE_DIST, Graphic::NODE_SIZE, false, val, pHead);
        pHead = newNode;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateFadeIn(pHead);
        ALOG->animateFocus(pHead);
        ALOG->animateFocusBorder(pHead);
        // ---

        // line number 1
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        ALOG->animateSlideIn(&pHead->aNext);
        ALOG->animateFadeIn(&pHead->aNext);
        ALOG->animateFocus(&pHead->aNext);
        // ---

        // line number 2
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        ALOG->animateTransform(pHead, pHead->x, pHead->y, 0, -Graphic::SLL_NODE_DIST);
        for (GraphicSinglyNode* curr = pHead->pNext; curr != nullptr; curr = curr->pNext) {
            ALOG->animateTransform(curr, curr->x, curr->y, Graphic::SLL_NODE_DIST, 0);
        }
        ALOG->animateUnfocus(&pHead->aNext);
        // ---
    }

    ALOG->build();
    
    return ExitStatus(true, "");
}

ExitStatus GraphicSinglyLinkedList::pushBack(int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) {
    if (size == Core::MAX_NUM_NODE_SLL) {
        return ExitStatus(false, "The size reach the maximum size allowed is " + cf::num2str(Core::MAX_NUM_NODE_SLL));
    }
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitStatus(false, "Value is out of range");
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::SLL_INSERT_BACK);
    
    reset();

    size++;

    if (pHead == nullptr) {
        pHead = new GraphicSinglyNode(Graphic::SLL_ORG_X, Graphic::SLL_ORG_Y, Graphic::NODE_SIZE, false, val);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0,1});
        ALOG->animateFadeIn(pHead);
        ALOG->animateFocus(pHead);
        ALOG->animateFocusBorder(pHead);
    } else {
        GraphicSinglyNode* pre = nullptr;
        GraphicSinglyNode* curr = pHead;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({3});
        ALOG->animateFocus(curr);
        ALOG->animateFocusBorder(curr);
        while (curr->pNext != nullptr) {
            pre = curr;
            curr = curr->pNext;
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({4});
            ALOG->animateUnfocus(pre);

            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({5});
            ALOG->animateFocus(curr);
            ALOG->animateFocusBorder(curr);
            ALOG->animateFocus(&pre->aNext);
        }
        GraphicSinglyNode* newNode = new GraphicSinglyNode(curr->x + Graphic::SLL_NODE_DIST, Graphic::SLL_ORG_Y, Graphic::NODE_SIZE, false, val);
        curr->setNext(newNode);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({6});
        ALOG->animateFadeIn(newNode);
        
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({7});
        ALOG->animateSlideIn(&curr->aNext);
        ALOG->animateFadeIn(&curr->aNext);
        ALOG->animateFocus(&curr->aNext);
        ALOG->animateFocus(newNode);
        ALOG->animateFocusBorder(newNode);
        ALOG->animateUnfocus(curr);
    }

    ALOG->build();

    return ExitStatus(true, "");
}

ExitStatus GraphicSinglyLinkedList::pushAtKth(int k, int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) {
    if (size == Core::MAX_NUM_NODE_SLL) {
        return ExitStatus(false, "The size reach the maximum size allowed is " + cf::num2str(Core::MAX_NUM_NODE_SLL));
    }
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitStatus(false, "Value is out of range");
    }
    if (k < 0 || k > size) {
        return ExitStatus(false, "k is out of range");
    }

    if (k == 0) {
        return pushFront(val, ALOG);
    }
    if (k == size) {
        return pushBack(val, ALOG);
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::SLL_INSERT_KTH);

    reset();

    size++;

    GraphicSinglyNode* prepre = nullptr;
    GraphicSinglyNode* pre = pHead;
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({0});
    ALOG->animateFocus(pre);
    ALOG->animateFocusBorder(pre);

    for (int i = 0; i < k-1; ++i) {
        prepre = pre;
        pre = pre->pNext;

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        ALOG->animateUnfocus(prepre);

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        ALOG->animateFocus(&prepre->aNext);
        ALOG->animateFocus(pre);
        ALOG->animateFocusBorder(pre);
    }

    GraphicSinglyNode* nxt = pre->pNext;
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({3});
    ALOG->animateFocus(&pre->aNext);
    ALOG->animateFocus(nxt);
    ALOG->animateFocusBorder(nxt);

    GraphicSinglyNode* cur = new GraphicSinglyNode(nxt->x, Graphic::SLL_ORG_Y + Graphic::SLL_NODE_DIST, Graphic::NODE_SIZE, false, val);
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({4});
    ALOG->animateFadeIn(cur);
    ALOG->animateFocus(cur);
    ALOG->animateFocusBorder(cur);

    cur->setNext(nxt);
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({5});
    ALOG->animateFadeIn(&cur->aNext);
    ALOG->animateFocus(&cur->aNext);
    ALOG->animateSlideIn(&cur->aNext);

    pre->updateNext(cur);
    pre->setArrowTrans(nxt);
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({6});
    ALOG->animateRedirect(pre, nxt);

    ALOG->addNewGroup();
    ALOG->animateTransform(cur, cur->x, cur->y, 0, -Graphic::SLL_NODE_DIST);
    for (; nxt != nullptr; nxt = nxt->pNext) {
        ALOG->animateTransform(nxt, nxt->x, nxt->y, Graphic::SLL_NODE_DIST, 0);
    }

    ALOG->build();

    return ExitStatus(true, "");
}

ExitStatus GraphicSinglyLinkedList::popFront(ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) {
    ALOG->clearGroup();
    ALOG->loadCode(CPath::SLL_REMOVE_FORD);

    reset();


    if (pHead == nullptr) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
    } else {
        size--;
        GraphicSinglyNode* tmp = pHead;
        nodes.push_back(tmp);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        ALOG->animateFocus(tmp);
        ALOG->animateFocusBorder(tmp);

        pHead = pHead->pNext;
        if (pHead != nullptr) {
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({2});
            ALOG->animateFocus(pHead);
            ALOG->animateFocusBorder(pHead);
        }

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({3});
        ALOG->animateFadeOut(tmp);
        ALOG->animateSlideOut(&tmp->aNext);

        ALOG->addNewGroup();
        for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
            ALOG->animateTransform(curr, curr->x, curr->y, -Graphic::SLL_NODE_DIST, 0);
        }
    }

    ALOG->build();

    return ExitStatus(true, "");
}

ExitStatus GraphicSinglyLinkedList::popBack(ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) {
    ALOG->clearGroup();
    ALOG->loadCode(CPath::SLL_REMOVE_BACK);

    reset();

    if (pHead == nullptr) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
    } else {
        if (size == 1) {
            return popFront(ALOG);
        }
        size--;
        GraphicSinglyNode* prepre = nullptr;
        GraphicSinglyNode* pre = pHead;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        ALOG->animateFocus(pre);
        ALOG->animateFocusBorder(pre);

        GraphicSinglyNode* tmp = pHead->pNext;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        ALOG->animateFocus(&pre->aNext);
        ALOG->animateFocus(tmp);
        ALOG->animateFocusBorder(tmp);

        while (true) {
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({3});
            ALOG->animateUnfocus(&pre->aNext);

            if (tmp->pNext == nullptr) {
                break;
            }

            prepre = pre;
            pre = tmp;
            tmp = tmp->pNext;


            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({4,5});
            ALOG->animateUnfocus(prepre);
            ALOG->animateFocus(&prepre->aNext);
            ALOG->animateFocus(pre);
            ALOG->animateFocusBorder(pre);
            ALOG->animateFocus(&pre->aNext);
            ALOG->animateFocus(tmp);
            ALOG->animateFocusBorder(tmp);
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
    }

    ALOG->build();

    return ExitStatus(true, "");
}



void GraphicSinglyLinkedList::draw() {
    // for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
    //     std::cerr << curr->x << ' '; 
    // }
    // std::cerr << '\n';
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        curr->draw();
    }
    for (GraphicSinglyNode* curr : nodes) {
        curr->draw();
    }
}

void GraphicSinglyLinkedList::makeCopy(GraphicSinglyLinkedList* src) {
    destroy();
    if (src->pHead != nullptr) {
        pHead = new GraphicSinglyNode;
        pHead->makeCopy(src->pHead);
        GraphicSinglyNode* curr = pHead;
        GraphicSinglyNode* srcCurr = src->pHead;
        for (; srcCurr->pNext != nullptr; curr = curr->pNext, srcCurr = srcCurr->pNext) {
            GraphicSinglyNode* tmp = new GraphicSinglyNode;
            tmp->makeCopy(srcCurr->pNext);
            curr->setNext(tmp);
            curr->aNext.copyAttribute(srcCurr->aNext);
        }
    }
}

void GraphicSinglyLinkedList::reset() {
    clearSaparated();
    clearArrows();
    unfocusAllNodes();
    
}

void GraphicSinglyLinkedList::clearSaparated() {
    for (GraphicSinglyNode* curr : nodes) {
        delete curr;
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
    for (GraphicSinglyNode* curr : nodes) {
        delete curr;
    }
    nodes.clear();
}
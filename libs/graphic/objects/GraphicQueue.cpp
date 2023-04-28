#include "GraphicQueue.h"

GraphicQueue::GraphicQueue() {
    pHead = nullptr;
    pTail = nullptr;
    _size = 0;
}

void GraphicQueue::resetColorAllNodes() {
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        curr->resetColor();
        curr->aNext.resetColor();
    }
}

void GraphicQueue::resetSubTextAllNodes() {
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        if (curr == pHead) {
            curr->setSubText("head");
        } else if (curr == pTail) {
            curr->setSubText("tail");
        } else {
            curr->setSubText("");
        }
    }
    if (_size == 1) {
        pHead->setSubText("head/tail");
    }
}

bool GraphicQueue::empty() const {
    return _size == 0;
}
int GraphicQueue::size() const {
    return _size;
}

ExitStatus GraphicQueue::initialize(int initSize, ListOfOperationsGroups<GraphicQueue>* ALOG) { // Randomly initialize
    if (initSize < 0 || initSize > Core::MAX_NUM_NODE_SLL) {
        return ExitMess::FAIL_LL_SIZE_OOB;
    }
    std::vector<int> vals;
    for (int i = 0; i < initSize; ++i) {
        vals.push_back(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
    }
    return initialize(vals, ALOG);
}

ExitStatus GraphicQueue::initialize(std::vector<int> vals, ListOfOperationsGroups<GraphicQueue>* ALOG) { // Initialize with given values
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
    _size = (int)vals.size();

    for (int i = 0; i < (int)vals.size(); ++i) {
        if (pHead == nullptr) {
            pHead = new GraphicSinglyNode(Graphic::LL_ORG_X, Graphic::LL_ORG_Y, Graphic::NODE_SIZE, false, vals[i]);
            pHead->setSubText("head");
            pTail = pHead;
        } else {
            GraphicSinglyNode* newNode = new GraphicSinglyNode(pTail->x + Graphic::LL_NODE_DIST, pTail->y, Graphic::NODE_SIZE, false, vals[i]);
            pTail->setNext(newNode);
            pTail = pTail->pNext;
        }
    }

    if (_size == 1) {
        pHead->setSubText("head/tail");
    } else if (_size > 1) {
        pTail->setSubText("tail");
    }

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

ExitStatus GraphicQueue::initialize(std::string strVals, ListOfOperationsGroups<GraphicQueue>* ALOG) { // Initialize with given values
    ExitStatus status;
    std::vector<int> vals;
    status = User::input2vector(strVals, vals, Valid::DIGIT + " ,\r\n");
    if (!status.success) {
        return status;
    }
    return initialize(vals, ALOG);
}

ExitStatus GraphicQueue::peek(ListOfOperationsGroups<GraphicQueue>* ALOG) {
    ALOG->clearGroup();
    ALOG->loadCode(CPath::QUEUE_PEEK);
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

ExitStatus GraphicQueue::update(int val, ListOfOperationsGroups<GraphicQueue>* ALOG) {
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::QUEUE_UPDATE);
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

ExitStatus GraphicQueue::push(int val, ListOfOperationsGroups<GraphicQueue>* ALOG) {
    if (_size == Core::MAX_NUM_NODE_SLL) {
        return ExitMess::FAIL_LL_REACH_MAX_SIZE;
    }
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::QUEUE_PUSH);
    reset();

    _size++;

    
    if (pHead == nullptr) {
        GraphicSinglyNode* vtx = new GraphicSinglyNode(Graphic::LL_ORG_X, Graphic::LL_ORG_Y, Graphic::NODE_SIZE, false, val);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateFadeIn(vtx);
        ALOG->animateNodeFromNormalToIter(vtx);
        ALOG->animateTransText(&vtx->sub, "", "vtx");

        pHead = vtx;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1,2});
        ALOG->animateNodeFromIterToFocus(pHead);
        ALOG->animateTransText(&pHead->sub, "vtx", "head/vtx");

        pTail = vtx;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({3});
        ALOG->animateTransText(&pHead->sub, "head/vtx", "head/tail/vtx");
    } else {
        GraphicSinglyNode* vtx = new GraphicSinglyNode(pTail->x + Graphic::LL_NODE_DIST, pTail->y, Graphic::NODE_SIZE, false, val);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateFadeIn(vtx);
        ALOG->animateNodeFromNormalToIter(vtx);
        ALOG->animateTransText(&vtx->sub, "", "vtx");

        pTail->setNext(vtx);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({4,5});
        ALOG->animateNodeFromNormalToFocus(pTail);
        ALOG->animateFadeIn(&pTail->aNext);
        ALOG->animateArrowFromNormalToIter(&pTail->aNext);
        ALOG->animateSlideIn(&pTail->aNext);

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({6});
        ALOG->animateNodeFromFocusToNormal(pTail);
        ALOG->animateNodeFromIterToFocus(vtx);
        if (pHead == pTail) {
            ALOG->animateTransText(&pTail->sub, "head/tail", "head");
        } else {
            ALOG->animateTransText(&pTail->sub, "tail", "");
        }
        ALOG->animateTransText(&vtx->sub, "vtx", "tail/vtx");
        pTail = vtx;
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}
ExitStatus GraphicQueue::pop(ListOfOperationsGroups<GraphicQueue>* ALOG) {
    ALOG->clearGroup();
    ALOG->loadCode(CPath::QUEUE_POP);
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
        if (pHead == pTail) {
            ALOG->animateTransText(&tmp->sub, "head/tail", "head/tail/tmp");
        } else {
            ALOG->animateTransText(&tmp->sub, "head", "head/tmp");
        }

        pHead = pHead->pNext;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        if (pHead != nullptr) {
            ALOG->animateNodeFromNormalToFocus(pHead);
            tmp->aNext.pSlideColor = &Theme::currTheme.ARROW_LINE_FOCUS_ITER;
            ALOG->animateSlideColorIn(&tmp->aNext);
            if (pHead == pTail) {
                ALOG->animateTransText(&pHead->sub, "tail", "head/tail");
            } else {
                ALOG->animateTransText(&pHead->sub, "", "head");
            }
        }
        if (pHead == nullptr) {
            ALOG->animateTransText(&tmp->sub, "head/tail/tmp", "tmp");
        } else {
            ALOG->animateTransText(&tmp->sub, "head/tmp", "tmp");
        }

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({3});
        ALOG->animateFadeOut(tmp);
        ALOG->animateFadeOut(&tmp->aNext);
        ALOG->animateSlideOut(&tmp->aNext);

        if (pHead != nullptr) {
            ALOG->addNewGroup();
            for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
                ALOG->animateTransform(curr, curr->x, curr->y, -Graphic::LL_NODE_DIST, 0);
            }
        } else {
            pTail = nullptr;
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({4});
            ALOG->animateDelay();
        }
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

void GraphicQueue::draw() {
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        curr->draw();
    }
    for (GraphicSinglyNode* node : nodes) {
        node->draw();
    }
}

void GraphicQueue::reset() {
    clearSaparated();
    resetColorAllNodes();
    resetSubTextAllNodes();
}

void GraphicQueue::clearSaparated() {
    for (GraphicSinglyNode* node : nodes) {
        delete node;
    }
    nodes.clear();
}

void GraphicQueue::destroy() {
    while (pHead != nullptr) {
        GraphicSinglyNode* tmp = pHead;
        pHead = pHead->pNext;
        delete tmp;
    }
    pTail = nullptr;
    for (GraphicNode* node : nodes) {
        delete node;
    }
    _size = 0;
    nodes.clear();
}
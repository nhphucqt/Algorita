#include "GraphicHashTable.h"

GraphicHashTable::GraphicHashTable() {
    _size = 0;
    pHead = nullptr;
    chainSize = nullptr;
}

void GraphicHashTable::resetColorAllNodes() {
    for (int i = 0; i < _size; ++i) {
        for (GraphicSinglyNode* curr = pHead[i]; curr != nullptr; curr = curr->pNext) {
            curr->resetColor();
            curr->aNext.resetColor();
        }
    }
}

void GraphicHashTable::resetSubTextAllNodes() {

}

int GraphicHashTable::hashFunc(int key) {
    return key % _size;    
}

ExitStatus GraphicHashTable::initialize(int initSize, int initNum, ListOfOperationsGroups* ALOG) {
    // std::cerr << "GraphicHashTable::initialize() start!\n";
    if (initSize <= 0 || initSize > Core::MAX_NUM_HT_HOR_ELM) {
        return ExitMess::FAIL_HT_SIZE_OOB;
    }
    if (initNum < 0 || initNum > Core::MAX_NUM_HT_VER_ELM * initSize) {
        return ExitMess::FAIL_HT_NUM_OOB;
    }
    std::vector<int> cnt(initSize, 0);
    std::vector<int> vals(initNum, 0);
    for (int i = 0; i < initNum; ++i) {
        int x = GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE);
        while (cnt[x%initSize] >= Core::MAX_NUM_HT_VER_ELM) {
            x = GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE);
        }
        cnt[x%initSize]++;
        vals[i] = x;
    }
    return initialize(initSize, vals, ALOG);
}

ExitStatus GraphicHashTable::initialize(int initSize, std::vector<int> vals, ListOfOperationsGroups* ALOG) {
    if (initSize <= 0 || initSize > Core::MAX_NUM_HT_HOR_ELM) {
        return ExitMess::FAIL_HT_SIZE_OOB;
    }
    for (int i = 0; i < (int)vals.size(); ++i) {
        if (vals[i] < Core::NODE_MIN_VALUE || vals[i] > Core::NODE_MAX_VALUE) {
            return ExitMess::FAIL_VALUE_OOB;
        }
    }
    std::vector<int> cnt(initSize, 0);
    for (int i = 0; i < (int)vals.size(); ++i) {
        if (++cnt[vals[i]%initSize] > Core::MAX_NUM_HT_VER_ELM) {
            return ExitMess::FAIL_HT_REACH_MAX_VER_SIZE;
        }
    }

    ALOG->clearGroup();
    destroy();

    _size = initSize;
    pHead = new GraphicSinglyNode*[_size]();
    chainSize = new int[_size]();
    int orgX = (Window::WIDTH - Graphic::HT_EML_HOR_DIST * (_size - 1) - Graphic::NODE_SIZE) / 2 - 100;
    assert(orgX >= 0);
    for (int i = 0; i < _size; ++i) {
        pHead[i] = new GraphicSinglyNode(orgX + Graphic::HT_EML_HOR_DIST * i, Graphic::HT_ORG_Y, Graphic::NODE_SIZE_SMALL, Graphic::NODE_BORDER_WIDTH_SMALL, true, Gfont::defaultFontSmall, i, nullptr);
    }
    
    for (int i = 0; i < (int)vals.size(); ++i) {
        int hkey = hashFunc(vals[i]);
        GraphicSinglyNode* newNode = new GraphicSinglyNode(pHead[hkey]->x, pHead[hkey]->y, Graphic::NODE_SIZE_SMALL, Graphic::NODE_BORDER_WIDTH_SMALL, false, Gfont::defaultFontSmall, vals[i], nullptr);
        newNode->setNext(pHead[hkey]->pNext, Graphic::ARROW_LINE_WIDTH_SMALL, Graphic::ARROW_HEAD_WIDTH_SMALL, Graphic::ARROW_HEAD_LENGTH_SMALL);
        pHead[hkey]->setNext(newNode, Graphic::ARROW_LINE_WIDTH_SMALL, Graphic::ARROW_HEAD_WIDTH_SMALL, Graphic::ARROW_HEAD_LENGTH_SMALL);
        chainSize[hkey]++;
        for (GraphicSinglyNode* curr = newNode; curr != nullptr; curr = curr->pNext) {
            curr->y += Graphic::HT_EML_VER_DIST;
        }
    }

    ALOG->addNewGroup();
    for (int i = 0; i < _size; ++i) {
        for (GraphicSinglyNode* curr = pHead[i]; curr != nullptr; curr = curr->pNext) {
            ALOG->animateFadeIn(curr);
            ALOG->animateFadeIn(&curr->aNext);
        }
    }

    ALOG->addNewGroup();
    for (int i = 0; i < _size; ++i) {
        for (GraphicSinglyNode* curr = pHead[i]; curr != nullptr; curr = curr->pNext) {
            ALOG->animateSlideIn(&curr->aNext);
        }
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicHashTable::initialize(int initSize, std::string strVals, ListOfOperationsGroups* ALOG) {
    if (initSize <= 0 || initSize > Core::MAX_NUM_HT_HOR_ELM) {
        return ExitMess::FAIL_HT_SIZE_OOB;
    }
    ExitStatus status;
    std::vector<int> vals;
    status = User::input2vector(strVals, vals, Valid::DIGIT + " ,\r\n");
    if (!status.success) {
        return status;
    }
    return initialize(initSize, vals, ALOG);
}

ExitStatus GraphicHashTable::initialize(std::string strVals, ListOfOperationsGroups* ALOG) {
    ExitStatus status;
    std::stringstream ss(strVals);
    bool flagEOF = false;
    status = User::getNum(ss, _size, flagEOF, 0, Core::MAX_NUM_ARRAY_ELM, Valid::DIGIT + " ,\r\n");
    if (!status.success) {
        return status;
    }
    std::vector<int> vals;
    status = User::extract2vector(ss, vals, Valid::DIGIT + " ,\r\n");
    if (!status.success) {
        return status;
    }
    return initialize(_size, vals, ALOG);
}

ExitStatus GraphicHashTable::searchFirst(int val, ListOfOperationsGroups* ALOG) {
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::HASHTABLE_SEARCH);
    reset();

    int hkey = hashFunc(val);
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({0});
    ALOG->animateNodeFromNormalToRefer(pHead[hkey]);

    GraphicSinglyNode* curr = pHead[hkey]->pNext;
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({1});
    if (curr != nullptr) {
        ALOG->animateNodeFromNormalToIter(curr);
    } else {
        ALOG->animateDelay();
    }

    while (true) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        ALOG->animateDelay();

        if (curr == nullptr) {
            break;
        }

        ALOG->addNewGroup();
        if (curr->nVal == val) {
            ALOG->backGroup()->setHighlightLines({3,4});
            ALOG->animateNodeFromIterToFocus(curr);
            break;
        }
        ALOG->backGroup()->setHighlightLines({3});
        ALOG->animateNodeFromIterToNearIter(curr);

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({5});
        if (curr->pNext != nullptr) {
            ALOG->animateArrowSlideFromNormalToIter(&curr->aNext);
            ALOG->animateSlideColorIn(&curr->aNext);
            ALOG->animateNodeFromNormalToIter(curr->pNext);
        } else {
            ALOG->animateDelay();
        }
        curr = curr->pNext;
    }

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({6});
    ALOG->animateDelay();

    ALOG->build();
    return ExitMess::SUCCESS;
}

ExitStatus GraphicHashTable::push(int val, ListOfOperationsGroups* ALOG) {
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }
    int hkey = hashFunc(val);
    if (chainSize[hkey] + 1 > Core::MAX_NUM_HT_VER_ELM) {
        return ExitMess::FAIL_HT_REACH_MAX_VER_SIZE;
    }
    
    ALOG->clearGroup();
    ALOG->loadCode(CPath::HASHTABLE_PUSH);
    reset();

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({0});
    ALOG->animateNodeFromNormalToRefer(pHead[hkey]);

    GraphicSinglyNode* newNode = new GraphicSinglyNode(pHead[hkey]->x, pHead[hkey]->y + Graphic::HT_EML_VER_DIST, Graphic::NODE_SIZE_SMALL, Graphic::NODE_BORDER_WIDTH_SMALL, false, Gfont::defaultFontSmall, val, nullptr);
    chainSize[hkey]++;

    if (pHead[hkey]->pNext == nullptr) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        ALOG->animateFadeIn(newNode);
        ALOG->animateNodeFromNormalToFocus(newNode);

        pHead[hkey]->setNext(newNode);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2,3});
        ALOG->animateFadeIn(&pHead[hkey]->aNext);
        ALOG->animateSlideIn(&pHead[hkey]->aNext);
        ALOG->animateArrowFromNormalToFocus(&pHead[hkey]->aNext);
    } else {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        ALOG->animateTransform(&pHead[hkey]->aNext.transB, 0, 0, 0, Graphic::HT_EML_VER_DIST);
        for (GraphicSinglyNode* curr = pHead[hkey]->pNext; curr != nullptr; curr = curr->pNext) {
            ALOG->animateTransform(curr, curr->x, curr->y, 0, Graphic::HT_EML_VER_DIST);
        }

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        ALOG->animateFadeIn(newNode);
        ALOG->animateNodeFromNormalToFocus(newNode);

        newNode->setNext(pHead[hkey]->pNext);
        pHead[hkey]->updateNext(newNode);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2,3});
        ALOG->animateTransform(&pHead[hkey]->aNext.transB, 0, Graphic::HT_EML_VER_DIST, 0, -Graphic::HT_EML_VER_DIST);
        ALOG->animateArrowFromNormalToFocus(&pHead[hkey]->aNext);
        ALOG->animateFadeIn(&newNode->aNext);
        ALOG->animateSlideIn(&newNode->aNext);
        ALOG->animateArrowFromNormalToIter(&newNode->aNext);
    }

    ALOG->build();
    return ExitMess::SUCCESS;
}

ExitStatus GraphicHashTable::pop(int val, ListOfOperationsGroups* ALOG) {
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::HASHTABLE_POP);
    reset();

    int hkey = hashFunc(val);
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({0});
    ALOG->animateNodeFromNormalToRefer(pHead[hkey]);

    GraphicSinglyNode* curr = pHead[hkey];
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({1});
    ALOG->animateNodeFromReferToIter(curr);

    while (true) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        if (curr->pNext != nullptr) {
            ALOG->animateSlideColorIn(&curr->aNext);
            ALOG->animateArrowSlideFromNormalToIter(&curr->aNext);
            ALOG->animateNodeFromNormalToRefer(curr->pNext);
        } else {
            ALOG->animateDelay();
        }

        if (curr->pNext == nullptr) {
            break;
        }

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({3});
        if (curr->pNext->nVal == val) {
            ALOG->animateDelay();

            chainSize[hkey]--;

            GraphicSinglyNode* tmp = curr->pNext;
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({4});
            ALOG->animateNodeFromReferToRemove(tmp);
            if (tmp->pNext != nullptr) {
                ALOG->animateNodeFromNormalToRefer(tmp->pNext);
                ALOG->animateSlideColorIn(&tmp->aNext);
                ALOG->animateArrowSlideFromNormalToIter(&tmp->aNext);

                curr->updateNext(tmp->pNext);
                curr->setNextArrowTrans(tmp);
                nodes.push_back(tmp);
                ALOG->addNewGroup();
                ALOG->backGroup()->setHighlightLines({5,6});
                ALOG->animateTransform(tmp, tmp->x, tmp->y, Graphic::HT_EML_HOR_DIST, 0);
                ALOG->animateFadeOut(tmp);
                ALOG->animateFadeOut(&tmp->aNext);
                ALOG->animateSlideOut(&tmp->aNext);
                ALOG->animateRedirectHead(curr, &curr->aNext, tmp);

                ALOG->addNewGroup();
                ALOG->backGroup()->setHighlightLines({7});
                for (GraphicSinglyNode* curr2 = curr->pNext; curr2 != nullptr; curr2 = curr2->pNext) {
                    ALOG->animateTransform(curr2, curr2->x, curr2->y, 0, -Graphic::HT_EML_VER_DIST);
                }
            } else {
                nodes.push_back(tmp);
                arrows.push_back(&curr->aNext);
                curr->pNext = nullptr;
                ALOG->addNewGroup();
                ALOG->backGroup()->setHighlightLines({5});
                ALOG->animateSlideOut(&curr->aNext);

                ALOG->addNewGroup();
                ALOG->backGroup()->setHighlightLines({6});
                ALOG->animateFadeOut(tmp);

                ALOG->addNewGroup();
                ALOG->backGroup()->setHighlightLines({7});
                ALOG->animateNodeFromIterToNearIter(curr);
            }
            
            return ExitMess::SUCCESS;
        }
        ALOG->animateNodeFromIterToNearIter(curr);
        
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({9});
        ALOG->animateNodeFromReferToIter(curr->pNext);
        curr = curr->pNext;
    }

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({10});
    ALOG->animateNodeFromIterToNearIter(curr);
    
    ALOG->build();

    return ExitMess::SUCCESS;    
}

void GraphicHashTable::draw() {
    // std::cerr << "GraphicHashTable::draw() start!\n";
    for (int i = 0; i < _size; ++i) {
        for (GraphicSinglyNode* curr = pHead[i]; curr != nullptr; curr = curr->pNext) {
            curr->draw();
        }
    }
    for (GraphicSinglyNode* node : nodes) {
        node->draw();
    }
    // std::cerr << "GraphicHashTable::draw() done!\n";
}

void GraphicHashTable::reset() {
    clearSaparated();
    clearArrows();
    resetColorAllNodes();
}

void GraphicHashTable::clearSaparated() {
    for (GraphicSinglyNode* node : nodes) {
        delete node;
    }
    nodes.clear();
}

void GraphicHashTable::clearArrows() {
    for (GraphicTrackArrow* curr : arrows) {
        curr->isTrack = false;
    }
    arrows.clear();
}

void GraphicHashTable::destroy() {
    for (int i = 0; i < _size; ++i) {
        while (pHead[i] != nullptr) {
            GraphicSinglyNode* temp = pHead[i];
            pHead[i] = pHead[i]->pNext;
            delete temp;
        }
    }
    delete[] pHead;
    delete[] chainSize;
    _size = 0;
    pHead = nullptr;
    chainSize = nullptr;
    clearSaparated();
    arrows.clear();
}
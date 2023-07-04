#include "GraphicHashTable.h"

GraphicHashTable::GraphicHashTable() {
    _size = 0;
    pHead = nullptr;
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

    ALOG->clearGroup();
    destroy();

    _size = initSize;
    pHead = new GraphicSinglyNode*[_size]();
    int orgX = (Window::WIDTH - Graphic::HT_EML_HOR_DIST * (_size - 1) - Graphic::NODE_SIZE) / 2;
    assert(orgX >= 0);
    for (int i = 0; i < _size; ++i) {
        pHead[i] = new GraphicSinglyNode(orgX + Graphic::HT_EML_HOR_DIST * i, Graphic::HT_ORG_Y, Graphic::NODE_SIZE_SMALL, Graphic::NODE_BORDER_WIDTH_SMALL, true, Gfont::defaultFontSmall, i, nullptr);
    }
    
    for (int i = 0; i < (int)vals.size(); ++i) {
        int hkey = hashFunc(vals[i]);
        GraphicSinglyNode* newNode = new GraphicSinglyNode(pHead[hkey]->x, pHead[hkey]->y, Graphic::NODE_SIZE_SMALL, Graphic::NODE_BORDER_WIDTH_SMALL, false, Gfont::defaultFontSmall, vals[i], nullptr);
        newNode->setNext(pHead[hkey]->pNext, Graphic::ARROW_LINE_WIDTH_SMALL, Graphic::ARROW_HEAD_WIDTH_SMALL, Graphic::ARROW_HEAD_LENGTH_SMALL);
        pHead[hkey]->setNext(newNode, Graphic::ARROW_LINE_WIDTH_SMALL, Graphic::ARROW_HEAD_WIDTH_SMALL, Graphic::ARROW_HEAD_LENGTH_SMALL);
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

ExitStatus GraphicHashTable::initialize(std::string strVals, ListOfOperationsGroups* ALOG) {

}

ExitStatus GraphicHashTable::searchFirst(int val, ListOfOperationsGroups* ALOG) {

}

ExitStatus GraphicHashTable::push(int val, ListOfOperationsGroups* ALOG) {

}

ExitStatus GraphicHashTable::popFront(ListOfOperationsGroups* ALOG) {

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
    for (GraphicTrackArrow* arrow : arrows) {
        delete arrow;
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
    _size = 0;
    pHead = nullptr;
    clearSaparated();
    clearArrows();
}
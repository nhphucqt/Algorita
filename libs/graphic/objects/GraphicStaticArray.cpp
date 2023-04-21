#include "GraphicStaticArray.h"

GraphicStaticArray::GraphicStaticArray() {
    _size = 0;
    arr = nullptr;
}

void GraphicStaticArray::resetColorAllNodes() {
    for (int i = 0; i < _size; ++i) {
        arr[i].resetColor();
    }
}

int GraphicStaticArray::size() const {
    return _size;
}

bool GraphicStaticArray::empty() const {
    return _size == 0;
}

ExitStatus GraphicStaticArray::initialize(int initSize, bool isRand, ListOfOperationsGroups<GraphicStaticArray>* ALOG) {
    if (initSize < 0 || initSize > Core::MAX_NUM_ARRAY_ELM) {
        return ExitMess::FAIL_ARR_SIZE_OOB;
    }
    std::vector<int> vals(initSize, 0);
    if (isRand) {
        for (int i = 0; i < initSize; ++i) {
            vals[i] = GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE);
        }
    }
    return initialize(vals, ALOG);
}

ExitStatus GraphicStaticArray::initialize(const std::vector<int> &vals, ListOfOperationsGroups<GraphicStaticArray>* ALOG) {
    if ((int)vals.size() < 0 || (int)vals.size() > Core::MAX_NUM_ARRAY_ELM) {
        return ExitMess::FAIL_ARR_SIZE_OOB;
    }
    for (int i = 0; i < (int)vals.size(); ++i) {
        if (vals[i] < Core::NODE_MIN_VALUE || vals[i] > Core::NODE_MAX_VALUE) {
            return ExitMess::FAIL_VALUE_OOB;
        }
    }

    ALOG->clearGroup();
    destroy();

    _size = (int)vals.size();
    arr = new GraphicNode[_size];
    for (int i = 0; i < _size; ++i) {
        arr[i] = GraphicNode(Graphic::ARR_ORG_X + (Graphic::NODE_SIZE + Graphic::ARR_EML_DIST) * i, Graphic::ARR_ORG_Y, Graphic::NODE_SIZE, true, vals[i]);
        arr[i].setSuperText(cf::num2str(i));
    }

    ALOG->addNewGroup();
    for (int i = 0; i < _size; ++i) {
        ALOG->animateFadeIn(arr+i);
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicStaticArray::initialize(const std::string &strVals, ListOfOperationsGroups<GraphicStaticArray>* ALOG) {
    std::pair<ExitStatus, std::vector<int>> input = User::input2vector(strVals, Valid::DIGIT + " ,");
    if (input.first.success) {
        return initialize(input.second, ALOG);
    } else {
        return input.first;
    }
}

ExitStatus GraphicStaticArray::searchFirst(int val, ListOfOperationsGroups<GraphicStaticArray>* ALOG) {
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }
    
    ALOG->clearGroup();
    ALOG->loadCode(CPath::STAT_ARR_SEARCH_FIRST);
    reset();

    for (int i = 0; i < _size; ++i) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateNodeFromNormalToIter(arr+i);

        if (arr[i].nVal == val) {
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({1,2});
            ALOG->animateNodeFromIterToFocus(arr+i);

            ALOG->build();
            return ExitMess::SUCCESS;
        } else {
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({1});
            ALOG->animateNodeFromIterToNearIter(arr+i);
        }
    }

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({3});
    ALOG->animateDelay();

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicStaticArray::updateValue(int k, int val, ListOfOperationsGroups<GraphicStaticArray>* ALOG) {
    if (_size == 0) {
        return ExitMess::FAIL_ARR_EMPTY;
    }
    if (k < 0 || k >= _size) {
        return ExitStatus(false, "i is out of bounds: Allow from 0 to " + cf::num2str(_size-1));
    } 
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::STAT_ARR_UPDATE);
    reset();

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({0});
    ALOG->animateNodeFromNormalToFocus(arr+k);
    ALOG->animateAssignValue(arr+k, arr[k].nVal, val);

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicStaticArray::accessValue(int k, ListOfOperationsGroups<GraphicStaticArray>* ALOG) {
    if (_size == 0) {
        return ExitMess::FAIL_ARR_EMPTY;
    }
    if (k < 0 || k >= _size) {
        return ExitStatus(false, "i is out of bounds: Allow from 0 to " + cf::num2str(_size-1));
    }
    
    ALOG->clearGroup();
    ALOG->loadCode(CPath::STAT_ARR_ACCESS);
    reset();

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({0});
    ALOG->animateNodeFromNormalToFocus(arr+k);
    
    ALOG->build();

    return ExitMess::SUCCESS;
}

void GraphicStaticArray::draw() {
    for (int i = 0; i < _size; ++i) {
        arr[i].draw();
    }
}

void GraphicStaticArray::reset() {
    resetColorAllNodes();
}

void GraphicStaticArray::destroy() {
    _size = 0;
    delete[] arr;
    arr = nullptr;
}
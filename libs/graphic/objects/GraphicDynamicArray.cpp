#include "GraphicDynamicArray.h"

GraphicDynamicArray::GraphicDynamicArray() {
    _size = 0;
    _capacity = 0;
    arr = nullptr;
    _oldSize = 0;
    oldArr = nullptr;
}

void GraphicDynamicArray::deleteOldArray() {
    _oldSize = 0;
    delete[] oldArr;
    oldArr = nullptr;
}

void GraphicDynamicArray::resetColorAllNodes() {
    for (int i = 0; i < _size; ++i) {
        arr[i].resetColor();   
    }
    for (int i = _size; i < _capacity; ++i) {
        arr[i].setDisabledColor();
    }
}

int GraphicDynamicArray::size() const {
    return _size;
}

bool GraphicDynamicArray::empty() const {
    return _size == 0;
}

ExitStatus GraphicDynamicArray::initialize(int initSize, bool isRand, ListOfOperationsGroups<GraphicDynamicArray>* ALOG) {
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

ExitStatus GraphicDynamicArray::initialize(const std::vector<int> &vals, ListOfOperationsGroups<GraphicDynamicArray>* ALOG) {
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

    if (vals.empty()) {
        return ExitMess::SUCCESS;
    }

    _capacity = 1;
    while (_capacity < (int)vals.size()) {
        _capacity <<= 1;
    }
    _size = (int)vals.size();

    arr = new GraphicNode[_capacity];
    for (int i = 0; i < _capacity; ++i) {
        arr[i] = GraphicNode(Graphic::ARR_ORG_X + (Graphic::NODE_SIZE + Graphic::ARR_EML_DIST) * i, Graphic::ARR_ORG_Y, Graphic::NODE_SIZE, true, i < _size ? vals[i] : 0);
        arr[i].setSuperText(cf::num2str(i));
        if (i >= _size) {
            arr[i].setDisabledColor();
        }
    }

    ALOG->addNewGroup();
    for (int i = 0; i < _capacity; ++i) {
        ALOG->animateFadeIn(arr+i);
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicDynamicArray::initialize(const std::string &strVals, ListOfOperationsGroups<GraphicDynamicArray>* ALOG) {
    std::pair<ExitStatus, std::vector<int>> input = User::input2vector(strVals, Valid::DIGIT + " ,\r\n");
    if (input.first.success) {
        return initialize(input.second, ALOG);
    } else {
        return input.first;
    }
}

ExitStatus GraphicDynamicArray::searchFirst(int val, ListOfOperationsGroups<GraphicDynamicArray>* ALOG) {
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }
    
    ALOG->clearGroup();
    ALOG->loadCode(CPath::DYNA_ARR_SEARCH_FIRST);
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

ExitStatus GraphicDynamicArray::updateValue(int k, int val, ListOfOperationsGroups<GraphicDynamicArray>* ALOG) {
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
    ALOG->loadCode(CPath::DYNA_ARR_UPDATE);
    reset();

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({0});
    ALOG->animateNodeFromNormalToFocus(arr+k);
    ALOG->animateAssignValue(arr+k, arr[k].nVal, val);

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicDynamicArray::accessValue(int k, ListOfOperationsGroups<GraphicDynamicArray>* ALOG) {
    if (_size == 0) {
        return ExitMess::FAIL_ARR_EMPTY;
    }
    if (k < 0 || k >= _size) {
        return ExitStatus(false, "i is out of bounds: Allow from 0 to " + cf::num2str(_size-1));
    }
    
    ALOG->clearGroup();
    ALOG->loadCode(CPath::DYNA_ARR_ACCESS);
    reset();

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({0});
    ALOG->animateNodeFromNormalToFocus(arr+k);
    
    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicDynamicArray::pushBack(int val, ListOfOperationsGroups<GraphicDynamicArray>* ALOG) {
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }
    if (_size == _capacity && _capacity == Core::MAX_NUM_ARRAY_ELM) {
        return ExitMess::FAIL_ARR_REACH_MAX_SIZE;
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::DYNA_ARR_PUSH_BACK);
    reset();

    if (_size == _capacity) {
        _capacity = _capacity == 0 ? 1 : _capacity * 2;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateDelay();
        
        GraphicNode* newArr = new GraphicNode[_capacity];
        for (int i = 0; i < _capacity; ++i) {
            newArr[i] = GraphicNode(Graphic::ARR_ORG_X + (Graphic::NODE_SIZE + Graphic::ARR_EML_DIST) * i, Graphic::ARR_ORG_Y + Graphic::NODE_SIZE * 2, Graphic::NODE_SIZE, true, 0);
            newArr[i].setSuperText(cf::num2str(i));
        }

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1,2});
        for (int i = 0; i < _capacity; ++i) {
            ALOG->animateFadeIn(newArr+i);
            if (i >= _size) {
                ALOG->animateNodeFromNormalToDisabled(newArr+i);
            }
        }

        for (int i = 0; i < _size; ++i) {
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({3});
            ALOG->animateNodeFromNormalToIter(arr+i);
            
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({4});
            ALOG->animateNodeFromNormalToFocus(newArr+i);
            ALOG->animateAssignValue(newArr+i, 0, arr[i].nVal);
        }

        _oldSize = _size;
        oldArr = arr;
        arr = newArr;

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({5});
        for (int i = 0; i < _oldSize; ++i) {
            ALOG->animateFadeOut(oldArr+i);
        }

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({6});
        for (int i = 0; i < _capacity; ++i) {
            ALOG->animateTransform(arr+i, arr[i].x, arr[i].y, 0, - Graphic::NODE_SIZE * 2);        
        }
    }

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({8});
    ALOG->animateNodeFromDisabledToFocus(arr+_size);
    ALOG->animateAssignValue(arr+_size, 0, val);
    _size++;

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicDynamicArray::popBack(ListOfOperationsGroups<GraphicDynamicArray>* ALOG) {
    ALOG->clearGroup();
    ALOG->loadCode(CPath::DYNA_ARR_POP_BACK);
    reset();

    if (_size == 0) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateDelay();
    } else {
        _size--;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        ALOG->animateAssignValue(arr+_size, arr[_size].nVal, 0);
        ALOG->animateNodeFromNormalToDisabled(arr+_size);
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

void GraphicDynamicArray::draw() {
    for (int i = 0; i < _capacity; ++i) {
        arr[i].draw();
    }
    for (int i = 0; i < _oldSize; ++i) {
        oldArr[i].draw();
    }
}

void GraphicDynamicArray::reset() {
    resetColorAllNodes();
    deleteOldArray();
}

void GraphicDynamicArray::destroy() {
    _size = 0;
    _capacity = 0;
    delete[] arr;
    arr = nullptr;
    deleteOldArray();
}
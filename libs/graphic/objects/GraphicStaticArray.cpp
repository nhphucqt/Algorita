#include "GraphicStaticArray.h"

GraphicStaticArray::GraphicStaticArray() {
    _capacity = 0;
    _size = 0;
    arr = nullptr;
}

void GraphicStaticArray::resetColorAllNodes() {
    for (int i = 0; i < _size; ++i) {
        arr[i].resetColor();
    }
    for (int i = _size; i < _capacity; ++i) {
        arr[i].setDisabledColor();
    }
}

void GraphicStaticArray::resetSubTextAllNodes() {
    for (int i = 0; i < _capacity; ++i) {
        arr[i].setSubText("");
    }
}

int GraphicStaticArray::capacity() const {
    return _capacity;
}

int GraphicStaticArray::size() const {
    return _size;
}

bool GraphicStaticArray::empty() const {
    return _size == 0;
}

ExitStatus GraphicStaticArray::initialize(int initCapa, int initSize, bool isRand, ListOfOperationsGroups* ALOG) {
    if (initCapa < 0 || initCapa > Core::MAX_NUM_ARRAY_ELM) {
        return ExitMess::FAIL_ARR_CAPA_OOB;
    }
    if (initSize < 0 || initSize > initCapa) {
        return ExitMess::FAIL_ARR_SIZE_OOB_CAPA;
    }
    std::vector<int> vals(initSize, 0);
    if (isRand) {
        for (int i = 0; i < initSize; ++i) {
            vals[i] = GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE);
        }
    }
    return initialize(initCapa, vals, ALOG);
}

ExitStatus GraphicStaticArray::initialize(int initCapa, const std::vector<int> &vals, ListOfOperationsGroups* ALOG) {
    if (initCapa < 0 || initCapa > Core::MAX_NUM_ARRAY_ELM) {
        return ExitMess::FAIL_ARR_CAPA_OOB;
    }
    if ((int)vals.size() < 0 || (int)vals.size() > initCapa) {
        return ExitMess::FAIL_ARR_SIZE_OOB_CAPA;
    }
    for (int i = 0; i < (int)vals.size(); ++i) {
        if (vals[i] < Core::NODE_MIN_VALUE || vals[i] > Core::NODE_MAX_VALUE) {
            return ExitMess::FAIL_VALUE_OOB;
        }
    }

    ALOG->clearGroup();
    destroy();

    _capacity = initCapa;
    _size = (int)vals.size();
    arr = new GraphicNode[_capacity];

    for (int i = 0; i < _size; ++i) {
        arr[i] = GraphicNode(Graphic::ARR_ORG_X + (Graphic::NODE_SIZE + Graphic::ARR_EML_HOR_DIST) * i, Graphic::ARR_ORG_Y, Graphic::NODE_SIZE, true, vals[i]);
        arr[i].setSuperText(cf::num2str(i));
    }
    for (int i = _size; i < _capacity; ++i) {
        arr[i] = GraphicNode(Graphic::ARR_ORG_X + (Graphic::NODE_SIZE + Graphic::ARR_EML_HOR_DIST) * i, Graphic::ARR_ORG_Y, Graphic::NODE_SIZE, true, 0);
        arr[i].setSuperText(cf::num2str(i));
        arr[i].setDisabledColor();
    }

    ALOG->addNewGroup();
    for (int i = 0; i < _capacity; ++i) {
        ALOG->animateFadeIn(arr+i);
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicStaticArray::initialize(int initCapa, const std::string &strVals, ListOfOperationsGroups* ALOG) {
    if (initCapa < 0 || initCapa > Core::MAX_NUM_ARRAY_ELM) {
        return ExitMess::FAIL_ARR_CAPA_OOB;
    }
    ExitStatus status;
    std::vector<int> vals;
    status = User::input2vector(strVals, vals, Valid::DIGIT + " ,\r\n");
    if (!status.success) {
        return status;
    }
    return initialize(initCapa, vals, ALOG);
}

ExitStatus GraphicStaticArray::initialize(const std::string &strVals, ListOfOperationsGroups* ALOG) {
    ExitStatus status;
    std::stringstream ss(strVals);
    bool flagEOF = false;
    status = User::getNum(ss, _capacity, flagEOF, 0, Core::MAX_NUM_ARRAY_ELM, Valid::DIGIT + " ,\r\n");
    if (!status.success) {
        return status;
    }
    std::vector<int> vals;
    status = User::extract2vector(ss, vals, Valid::DIGIT + " ,\r\n");
    if (!status.success) {
        return status;
    }
    return initialize(_capacity, vals, ALOG);
}

ExitStatus GraphicStaticArray::searchFirst(int val, ListOfOperationsGroups* ALOG) {
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
        if (i > 0) {
            // ALOG->animateTransText(&arr[i-1].sub, "i", "");
        }
        // ALOG->animateTransText(&arr[i].sub, "", "i");

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
    if (_size > 0) {
        // ALOG->animateTransText(&arr[_size-1].sub, "i", ""); 
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicStaticArray::updateValue(int k, int val, ListOfOperationsGroups* ALOG) {
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
    // ALOG->animateTransText(&arr[k].sub, "", "i");

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicStaticArray::accessValue(int k, ListOfOperationsGroups* ALOG) {
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
    // ALOG->animateTransText(&arr[k].sub, "", "i");
    
    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicStaticArray::pushFront(int val, ListOfOperationsGroups* ALOG) {
    if (_size == _capacity) {
        return ExitMess::FAIL_ARR_REACH_MAX_SIZE_CAPA;
    }
    if (val < 0 || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::STAT_ARR_INSERT_FORD);
    reset();

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({0});
    ALOG->animateNodeFromDisabledToNormal(arr+_size);
    _size++;


    for (int i = _size-1; i > 0; --i) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        if (i == _size-1) {
            ALOG->animateNodeFromNormalToIter(arr+i);
            // ALOG->animateTransText(&arr[i].sub, "", "i");
        } else {
            ALOG->animateNodeFromFocusToNormal(arr+i+1);
            ALOG->animateNodeFromReferToIter(arr+i);
            // ALOG->animateTransText(&arr[i+1].sub, "i", "");
            // ALOG->animateTransText(&arr[i].sub, "i-1", "i");
        }
        ALOG->animateNodeFromNormalToRefer(arr+i-1);
        // ALOG->animateTransText(&arr[i-1].sub, "", "i-1");

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        ALOG->animateNodeFromIterToFocus(arr+i);
        ALOG->animateAssignValue(arr+i, arr[i].nVal, arr[i-1].nVal);
    }

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({1});
    if (_size == 1) {
        ALOG->animateNodeFromNormalToIter(arr);
        // ALOG->animateTransText(&arr[0].sub, "", "i");
    } else {
        ALOG->animateNodeFromFocusToNormal(arr+1);
        ALOG->animateNodeFromReferToIter(arr);
        // ALOG->animateTransText(&arr[1].sub, "i", "");
        // ALOG->animateTransText(&arr[0].sub, "i-1", "i");
    }

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({3});
    ALOG->animateNodeFromIterToFocus(arr);
    ALOG->animateAssignValue(arr, arr->nVal, val);
    // ALOG->animateTransText(&arr[0].sub, "i", "");

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicStaticArray::pushBack(int val, ListOfOperationsGroups* ALOG) {
    if (_size == _capacity) {
        return ExitMess::FAIL_ARR_REACH_MAX_SIZE_CAPA;
    }
    if (val < 0 || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::STAT_ARR_INSERT_BACK);
    reset();

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({0});
    ALOG->animateNodeFromDisabledToFocus(arr+_size);
    ALOG->animateAssignValue(arr+_size, arr[_size].nVal, val);
    _size++;

    ALOG->build();
    
    return ExitMess::SUCCESS;
}

ExitStatus GraphicStaticArray::pushAtKth(int val, int k, ListOfOperationsGroups* ALOG) {
    if (_size == _capacity) {
        return ExitMess::FAIL_ARR_REACH_MAX_SIZE_CAPA;
    }
    if (val < 0 || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }
    if (k < 0 || k > _size) {
        return ExitStatus(false, "i is out of bounds: Allow from 0 to " + cf::num2str(_size));
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::STAT_ARR_INSERT_KTH);
    reset();

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({0});
    ALOG->animateNodeFromDisabledToNormal(arr+_size);
    _size++;

    for (int i = _size-1; i > k; --i) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        if (i == _size-1) {
            ALOG->animateNodeFromNormalToIter(arr+i);
            // ALOG->animateTransText(&arr[i].sub, "", "j");
        } else {
            ALOG->animateNodeFromFocusToNormal(arr+i+1);
            ALOG->animateNodeFromReferToIter(arr+i);
            // ALOG->animateTransText(&arr[i+1].sub, "j", "");
            // ALOG->animateTransText(&arr[i].sub, "j-1", "j");
        }
        ALOG->animateNodeFromNormalToRefer(arr+i-1);
        // ALOG->animateTransText(&arr[i-1].sub, "", "j-1");

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        ALOG->animateNodeFromIterToFocus(arr+i);
        ALOG->animateAssignValue(arr+i, arr[i].nVal, arr[i-1].nVal);
    }

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({1});
    if (k == _size-1) {
        ALOG->animateNodeFromNormalToIter(arr+k);
        // ALOG->animateTransText(&arr[k].sub, "", "j");
    } else {
        ALOG->animateNodeFromFocusToNormal(arr+k+1);
        ALOG->animateNodeFromReferToIter(arr+k);
        // ALOG->animateTransText(&arr[k+1].sub, "j", "");
        // ALOG->animateTransText(&arr[k].sub, "j-1", "j");
    }

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({3});
    ALOG->animateNodeFromIterToFocus(arr+k);
    ALOG->animateAssignValue(arr+k, arr[k].nVal, val);
    // ALOG->animateTransText(&arr[k].sub, "j", "i");

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicStaticArray::popFront(ListOfOperationsGroups* ALOG) {
    ALOG->clearGroup();
    ALOG->loadCode(CPath::STAT_ARR_REMOVE_FORD);
    reset();

    if (_size == 0) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateDelay();
    } else {
        for (int i = 0; i < _size-1; ++i) {
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({1});
            if (i == 0) {
                ALOG->animateNodeFromNormalToIter(arr+i);
                // ALOG->animateTransText(&arr[i].sub, "", "i");
            } else {
                ALOG->animateNodeFromFocusToNormal(arr+i-1);
                ALOG->animateNodeFromReferToIter(arr+i);
                // ALOG->animateTransText(&arr[i-1].sub, "i", "");
                // ALOG->animateTransText(&arr[i].sub, "i+1", "i");
            }
            ALOG->animateNodeFromNormalToRefer(arr+i+1);
            // ALOG->animateTransText(&arr[i+1].sub, "", "i+1");

            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({2});
            ALOG->animateNodeFromIterToFocus(arr+i);
            ALOG->animateAssignValue(arr+i, arr[i].nVal, arr[i+1].nVal);
        }

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        if (_size == 1) {
            ALOG->animateNodeFromNormalToIter(arr+_size-1);
            // ALOG->animateTransText(&arr[_size-1].sub, "", "i");
        } else {
            ALOG->animateNodeFromFocusToNormal(arr+_size-2);
            ALOG->animateNodeFromReferToIter(arr+_size-1);
            // ALOG->animateTransText(&arr[_size-2].sub, "i", "");
            // ALOG->animateTransText(&arr[_size-1].sub, "i+1", "i");
        }

        _size--;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({3});
        ALOG->animateNodeFromIterToDisabled(arr+_size);
        ALOG->animateAssignValue(arr+_size, arr[_size].nVal, 0);
        // ALOG->animateTransText(&arr[_size].sub, "i", "");
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicStaticArray::popBack(ListOfOperationsGroups* ALOG) {
    ALOG->clearGroup();
    ALOG->loadCode(CPath::STAT_ARR_REMOVE_BACK);
    reset();

    if (_size == 0) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateDelay();
    } else {
        _size--;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        ALOG->animateNodeFromNormalToDisabled(arr+_size);
        ALOG->animateAssignValue(arr+_size, arr[_size].nVal, 0);
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicStaticArray::popAtKth(int k, ListOfOperationsGroups* ALOG) {
    if (_size == 0) {
        return ExitMess::FAIL_ARR_EMPTY;
    }
    if (k < 0 || k >= _size) {
        return ExitStatus(false, "i is out of bounds: Allow from 0 to " + cf::num2str(_size-1));
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::STAT_ARR_REMOVE_KTH);
    reset();

    if (_size == 0) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateDelay();
    } else {
        for (int i = k; i < _size-1; ++i) {
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({1});
            if (i == k) {
                ALOG->animateNodeFromNormalToIter(arr+i);
                // ALOG->animateTransText(&arr[i].sub, "", "j");
            } else {
                ALOG->animateNodeFromFocusToNormal(arr+i-1);
                ALOG->animateNodeFromReferToIter(arr+i);
                // ALOG->animateTransText(&arr[i-1].sub, "j", "");
                // ALOG->animateTransText(&arr[i].sub, "j+1", "j");
            }
            ALOG->animateNodeFromNormalToRefer(arr+i+1);
            // ALOG->animateTransText(&arr[i+1].sub, "", "j+1");

            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({2});
            ALOG->animateNodeFromIterToFocus(arr+i);
            ALOG->animateAssignValue(arr+i, arr[i].nVal, arr[i+1].nVal);
        }

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        if (k == _size-1) {
            ALOG->animateNodeFromNormalToIter(arr+_size-1);
            // ALOG->animateTransText(&arr[_size-1].sub, "", "j");
        } else {
            ALOG->animateNodeFromFocusToNormal(arr+_size-2);
            ALOG->animateNodeFromReferToIter(arr+_size-1);
            // // ALOG->animateTransText(&arr[_size-2].sub, "j", "");
            // // ALOG->animateTransText(&arr[_size-1].sub, "j+1", "j");
        }

        _size--;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({3});
        ALOG->animateNodeFromIterToDisabled(arr+_size);
        ALOG->animateAssignValue(arr+_size, arr[_size].nVal, 0);
        // // ALOG->animateTransText(&arr[_size].sub, "j", "");
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

void GraphicStaticArray::draw() {
    for (int i = 0; i < _capacity; ++i) {
        arr[i].draw();
    }
}

void GraphicStaticArray::reset() {
    resetColorAllNodes();
    resetSubTextAllNodes();
}

void GraphicStaticArray::destroy() {
    _capacity = 0;
    _size = 0;
    delete[] arr;
    arr = nullptr;
}
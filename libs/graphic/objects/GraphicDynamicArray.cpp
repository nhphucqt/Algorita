#include "GraphicDynamicArray.h"

GraphicDynamicArray::GraphicDynamicArray() {
    _size = 0;
    arr = nullptr;
    _oldSize = 0;
    oldArr = nullptr;
}

void GraphicDynamicArray::deleteCurArray() {
    _size = 0;
    delete[] arr;
    arr = nullptr;
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
}

void GraphicDynamicArray::resetSubTextAllNodes() {
    for (int i = 0; i < _size; ++i) {
        arr[i].setSubText("");
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

    _size = (int)vals.size();

    arr = new GraphicNode[_size];
    for (int i = 0; i < _size; ++i) {
        arr[i] = GraphicNode(Graphic::ARR_ORG_X + (Graphic::NODE_SIZE + Graphic::ARR_EML_HOR_DIST) * i, Graphic::ARR_ORG_Y, Graphic::NODE_SIZE, true, i < _size ? vals[i] : 0);
        arr[i].setSuperText(cf::num2str(i));
    }

    ALOG->addNewGroup();
    for (int i = 0; i < _size; ++i) {
        ALOG->animateFadeIn(arr+i);
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicDynamicArray::initialize(const std::string &strVals, ListOfOperationsGroups<GraphicDynamicArray>* ALOG) {
    ExitStatus status;
    std::vector<int> vals;
    status = User::input2vector(strVals, vals, Valid::DIGIT + " ,\r\n");
    if (!status.success) {
        return status;
    }
    return initialize(vals, ALOG);
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

ExitStatus GraphicDynamicArray::pushFront(int val, ListOfOperationsGroups<GraphicDynamicArray>* ALOG) {
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }
    if (_size == Core::MAX_NUM_ARRAY_ELM) {
        return ExitMess::FAIL_ARR_REACH_MAX_SIZE;
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::DYNA_ARR_INSERT_FORD);
    reset();

    GraphicNode* newArr = new GraphicNode[_size+1];
    for (int i = 0; i < _size+1; ++i) {
        newArr[i] = GraphicNode(Graphic::ARR_ORG_X + (Graphic::NODE_SIZE + Graphic::ARR_EML_HOR_DIST) * i, Graphic::ARR_ORG_Y + Graphic::ARR_EML_VER_DIST, Graphic::NODE_SIZE, true, 0);
        newArr[i].setSuperText(cf::num2str(i));
    }
    newArr[0].setDisabledColor();

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({0});
    for (int i = 0; i < _size+1; ++i) {
        ALOG->animateFadeIn(newArr+i);
    }

    for (int i = 0; i < _size; ++i) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        if (i > 0) {
            ALOG->animateNodeFromIterToNearIter(arr+i-1);
        }
        ALOG->animateNodeFromNormalToIter(arr+i);

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        ALOG->animateNodeFromNormalToFocus(newArr+i+1);
        ALOG->animateAssignValue(newArr+i+1, 0, arr[i].nVal);
    }

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({1});
    if (_size > 0) {
        ALOG->animateNodeFromIterToNearIter(arr+_size-1);
    } else {
        ALOG->animateDelay();
    }

    _oldSize = _size;
    oldArr = arr;
    arr = newArr;

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({3});
    for (int i = 0; i < _oldSize; ++i) {
        ALOG->animateFadeOut(oldArr+i);
    }

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({4});
    for (int i = 0; i < _size+1; ++i) {
        ALOG->animateTransform(arr+i, arr[i].x, arr[i].y, 0, - Graphic::ARR_EML_VER_DIST);
        if (i > 0) {
            ALOG->animateNodeFromFocusToNormal(arr+i);
        }
    }

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({5});
    ALOG->animateNodeFromDisabledToFocus(arr);
    ALOG->animateAssignValue(arr, 0, val);
    _size++;

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicDynamicArray::pushBack(int val, ListOfOperationsGroups<GraphicDynamicArray>* ALOG) {
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }
    if (_size == Core::MAX_NUM_ARRAY_ELM) {
        return ExitMess::FAIL_ARR_REACH_MAX_SIZE;
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::DYNA_ARR_INSERT_BACK);
    reset();
    
    GraphicNode* newArr = new GraphicNode[_size+1];
    for (int i = 0; i < _size+1; ++i) {
        newArr[i] = GraphicNode(Graphic::ARR_ORG_X + (Graphic::NODE_SIZE + Graphic::ARR_EML_HOR_DIST) * i, Graphic::ARR_ORG_Y + Graphic::ARR_EML_VER_DIST, Graphic::NODE_SIZE, true, 0);
        newArr[i].setSuperText(cf::num2str(i));
    }
    newArr[_size].setDisabledColor();

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({0});
    for (int i = 0; i < _size+1; ++i) {
        ALOG->animateFadeIn(newArr+i);
    }

    for (int i = 0; i < _size; ++i) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        if (i > 0) {
            ALOG->animateNodeFromIterToNearIter(arr+i-1);
        }
        ALOG->animateNodeFromNormalToIter(arr+i);
        
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        ALOG->animateNodeFromNormalToFocus(newArr+i);
        ALOG->animateAssignValue(newArr+i, 0, arr[i].nVal);

        // if (i > 0) {
        //     ALOG->animateTransText(&arr[i-1].sub, "i", "");
        //     ALOG->animateTransText(&newArr[i-1].sub, "i", "");
        // }
        // ALOG->animateTransText(&arr[i].sub, "", "i");
        // ALOG->animateTransText(&newArr[i].sub, "", "i");
    }

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({1});
    if (_size > 0) {
        ALOG->animateNodeFromIterToNearIter(arr+_size-1);
    } else {
        ALOG->animateDelay();
    }

    _oldSize = _size;
    oldArr = arr;
    arr = newArr;

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({3});
    for (int i = 0; i < _oldSize; ++i) {
        ALOG->animateFadeOut(oldArr+i);
    }

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({4});
    for (int i = 0; i < _size+1; ++i) {
        ALOG->animateTransform(arr+i, arr[i].x, arr[i].y, 0, - Graphic::ARR_EML_VER_DIST);
        if (i < _size) {
            ALOG->animateNodeFromFocusToNormal(arr+i);
        }
    }

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({5});
    ALOG->animateNodeFromDisabledToFocus(arr+_size);
    ALOG->animateAssignValue(arr+_size, 0, val);
    _size++;

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicDynamicArray::pushAtKth(int val, int k, ListOfOperationsGroups<GraphicDynamicArray>* ALOG) {
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }
    if (_size == Core::MAX_NUM_ARRAY_ELM) {
        return ExitMess::FAIL_ARR_REACH_MAX_SIZE;
    }
    if (k < 0 || k > _size) {
        return ExitStatus(false, "i is out of bounds: Allow from 0 to " + cf::num2str(_size));
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::DYNA_ARR_INSERT_KTH);
    reset();
    
    GraphicNode* newArr = new GraphicNode[_size+1];
    for (int i = 0; i < _size+1; ++i) {
        newArr[i] = GraphicNode(Graphic::ARR_ORG_X + (Graphic::NODE_SIZE + Graphic::ARR_EML_HOR_DIST) * i, Graphic::ARR_ORG_Y + Graphic::ARR_EML_VER_DIST, Graphic::NODE_SIZE, true, 0);
        newArr[i].setSuperText(cf::num2str(i));
    }
    newArr[k].setDisabledColor();

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({0});
    for (int i = 0; i < _size+1; ++i) {
        ALOG->animateFadeIn(newArr+i);
    }

    for (int i = 0; i < k; ++i) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        if (i > 0) {
            ALOG->animateNodeFromIterToNearIter(arr+i-1);
        }
        ALOG->animateNodeFromNormalToIter(arr+i);
        
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        ALOG->animateNodeFromNormalToFocus(newArr+i);
        ALOG->animateAssignValue(newArr+i, 0, arr[i].nVal);

        // if (i > 0) {
        //     ALOG->animateTransText(&arr[i-1].sub, "i", "");
        //     ALOG->animateTransText(&newArr[i-1].sub, "i", "");
        // }
        // ALOG->animateTransText(&arr[i].sub, "", "i");
        // ALOG->animateTransText(&newArr[i].sub, "", "i");
    }

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({1});
    if (_size > 0) {
        ALOG->animateNodeFromIterToNearIter(arr+k-1);
    } else {
        ALOG->animateDelay();
    }

    for (int i = k; i < _size; ++i) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({3});
        if (i > k) {
            ALOG->animateNodeFromIterToNearIter(arr+i-1);
        }
        ALOG->animateNodeFromNormalToIter(arr+i);

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({4});
        ALOG->animateNodeFromNormalToFocus(newArr+i+1);
        ALOG->animateAssignValue(newArr+i+1, 0, arr[i].nVal);
    }

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({3});
    if (_size > k) {
        ALOG->animateNodeFromIterToNearIter(arr+_size-1);
    } else {
        ALOG->animateDelay();
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
    for (int i = 0; i < _size+1; ++i) {
        ALOG->animateTransform(arr+i, arr[i].x, arr[i].y, 0, - Graphic::ARR_EML_VER_DIST);
        if (i != k) {
            ALOG->animateNodeFromFocusToNormal(arr+i);
        }
    }

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({7});
    ALOG->animateNodeFromDisabledToFocus(arr+k);
    ALOG->animateAssignValue(arr+k, 0, val);
    _size++;

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicDynamicArray::popFront(ListOfOperationsGroups<GraphicDynamicArray>* ALOG) {
    ALOG->clearGroup();
    ALOG->loadCode(CPath::DYNA_ARR_REMOVE_FORD);
    reset();

    if (_size == 0) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateDelay();
    } else {
        GraphicNode* newArr = new GraphicNode[_size-1];
        for (int i = 0; i < _size-1; ++i) {
            newArr[i] = GraphicNode(Graphic::ARR_ORG_X + (Graphic::NODE_SIZE + Graphic::ARR_EML_HOR_DIST) * i, Graphic::ARR_ORG_Y + Graphic::ARR_EML_VER_DIST, Graphic::NODE_SIZE, true, 0);
            newArr[i].setSuperText(cf::num2str(i));
        }

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        for (int i = 0; i < _size-1; ++i) {
            ALOG->animateFadeIn(newArr+i);
        }

        for (int i = 1; i < _size; ++i) {
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({2});
            if (i > 1) {
                ALOG->animateNodeFromIterToNearIter(arr+i-1);
            }
            ALOG->animateNodeFromNormalToIter(arr+i);
            
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({3});
            ALOG->animateNodeFromNormalToFocus(newArr+i-1);
            ALOG->animateAssignValue(newArr+i-1, 0, arr[i].nVal);
        }

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        if (_size > 1) {
            ALOG->animateNodeFromIterToNearIter(arr+_size-1);
        } else {
            ALOG->animateDelay();
        }

        _oldSize = _size;
        oldArr = arr;
        arr = newArr;
        _size--;

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({4});
        for (int i = 0; i < _oldSize; ++i) {
            ALOG->animateFadeOut(oldArr+i);
        }

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({5});
        for (int i = 0; i < _size; ++i) {
            ALOG->animateTransform(arr+i, arr[i].x, arr[i].y, 0, - Graphic::ARR_EML_VER_DIST);
            ALOG->animateNodeFromFocusToNormal(arr+i);
        }
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicDynamicArray::popBack(ListOfOperationsGroups<GraphicDynamicArray>* ALOG) {
    ALOG->clearGroup();
    ALOG->loadCode(CPath::DYNA_ARR_REMOVE_BACK);
    reset();

    if (_size == 0) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateDelay();
    } else {
        GraphicNode* newArr = new GraphicNode[_size-1];
        for (int i = 0; i < _size-1; ++i) {
            newArr[i] = GraphicNode(Graphic::ARR_ORG_X + (Graphic::NODE_SIZE + Graphic::ARR_EML_HOR_DIST) * i, Graphic::ARR_ORG_Y + Graphic::ARR_EML_VER_DIST, Graphic::NODE_SIZE, true, 0);
            newArr[i].setSuperText(cf::num2str(i));
        }

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        for (int i = 0; i < _size-1; ++i) {
            ALOG->animateFadeIn(newArr+i);
        }

        for (int i = 0; i < _size-1; ++i) {
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({2});
            if (i > 0) {
                ALOG->animateNodeFromIterToNearIter(arr+i-1);
            }
            ALOG->animateNodeFromNormalToIter(arr+i);
            
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({3});
            ALOG->animateNodeFromNormalToFocus(newArr+i);
            ALOG->animateAssignValue(newArr+i, 0, arr[i].nVal);
        }

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        if (_size > 1) {
            ALOG->animateNodeFromIterToNearIter(arr+_size-2);
        } else {
            ALOG->animateDelay();
        }

        _oldSize = _size;
        oldArr = arr;
        arr = newArr;
        _size--;

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({4});
        for (int i = 0; i < _oldSize; ++i) {
            ALOG->animateFadeOut(oldArr+i);
        }

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({5});
        for (int i = 0; i < _size; ++i) {
            ALOG->animateTransform(arr+i, arr[i].x, arr[i].y, 0, - Graphic::ARR_EML_VER_DIST);
            ALOG->animateNodeFromFocusToNormal(arr+i);
        }
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicDynamicArray::popAtKth(int k, ListOfOperationsGroups<GraphicDynamicArray>* ALOG) {
    if (_size == 0) {
        return ExitMess::FAIL_ARR_EMPTY;
    }
    if (k < 0 || k >= _size) {
        return ExitStatus(false, "i is out of bounds: Allow from 0 to " + cf::num2str(_size-1));
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::DYNA_ARR_REMOVE_KTH);
    reset();

    if (_size == 0) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateDelay();
    } else {
        GraphicNode* newArr = new GraphicNode[_size-1];
        for (int i = 0; i < _size-1; ++i) {
            newArr[i] = GraphicNode(Graphic::ARR_ORG_X + (Graphic::NODE_SIZE + Graphic::ARR_EML_HOR_DIST) * i, Graphic::ARR_ORG_Y + Graphic::ARR_EML_VER_DIST, Graphic::NODE_SIZE, true, 0);
            newArr[i].setSuperText(cf::num2str(i));
        }

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        for (int i = 0; i < _size-1; ++i) {
            ALOG->animateFadeIn(newArr+i);
        }

        for (int i = 0; i < k; ++i) {
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({2});
            if (i > 0) {
                ALOG->animateNodeFromIterToNearIter(arr+i-1);
            }
            ALOG->animateNodeFromNormalToIter(arr+i);
            
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({3});
            ALOG->animateNodeFromNormalToFocus(newArr+i);
            ALOG->animateAssignValue(newArr+i, 0, arr[i].nVal);
        }

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        if (k > 0) {
            ALOG->animateNodeFromIterToNearIter(arr+k-1);
        } else {
            ALOG->animateDelay();
        }

        for (int i = k+1; i < _size; ++i) {
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({4});
            if (i > k+1) {
                ALOG->animateNodeFromIterToNearIter(arr+i-1);
            }
            ALOG->animateNodeFromNormalToIter(arr+i);
            
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({5});
            ALOG->animateNodeFromNormalToFocus(newArr+i-1);
            ALOG->animateAssignValue(newArr+i-1, 0, arr[i].nVal);
        }

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({4});
        if (_size > k+1) {
            ALOG->animateNodeFromIterToNearIter(arr+_size-1);
        } else {
            ALOG->animateDelay();
        }

        _oldSize = _size;
        oldArr = arr;
        arr = newArr;
        _size--;

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({6});
        for (int i = 0; i < _oldSize; ++i) {
            ALOG->animateFadeOut(oldArr+i);
        }

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({7});
        for (int i = 0; i < _size; ++i) {
            ALOG->animateTransform(arr+i, arr[i].x, arr[i].y, 0, - Graphic::ARR_EML_VER_DIST);
            ALOG->animateNodeFromFocusToNormal(arr+i);
        }
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

void GraphicDynamicArray::draw() {
    for (int i = 0; i < _size; ++i) {
        arr[i].draw();
    }
    for (int i = 0; i < _oldSize; ++i) {
        oldArr[i].draw();
    }
}

void GraphicDynamicArray::reset() {
    resetColorAllNodes();
    resetSubTextAllNodes();
    deleteOldArray();
}

void GraphicDynamicArray::destroy() {
    deleteCurArray();
    deleteOldArray();
}
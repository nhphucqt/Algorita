#ifndef GRAPHIC_STATIC_ARRAY_H
#define GRAPHIC_STATIC_ARRAY_H

#include <vector>

#include "../../conf_raylib.h"
#include "../../global.h"
#include "GraphicNode.h"
#include "../../animation/ListOfOperationsGroups.h"
#include "../../core/ExitStatus.h"
#include "../../core/validator.h"
#include "../../core/userfunc.h"

class GraphicStaticArray {
private:
    GraphicNode* arr;
    int _size, _capacity;

    void resetColorAllNodes();
    void resetSubTextAllNodes();

public:
    GraphicStaticArray();

    int capacity() const;
    int size() const;
    bool empty() const;

    ExitStatus initialize(int initCapa, int initSize, bool isRand, ListOfOperationsGroups* ALOG);
    ExitStatus initialize(int initSize, const std::vector<int> &vals, ListOfOperationsGroups* ALOG);
    ExitStatus initialize(int initCapa, const std::string &strVals, ListOfOperationsGroups* ALOG);
    ExitStatus initialize(const std::string &strVals, ListOfOperationsGroups* ALOG);

    ExitStatus searchFirst(int val, ListOfOperationsGroups* ALOG);

    ExitStatus updateValue(int k, int val, ListOfOperationsGroups* ALOG);
    ExitStatus accessValue(int k, ListOfOperationsGroups* ALOG);

    ExitStatus pushFront(int val, ListOfOperationsGroups* ALOG);
    ExitStatus pushBack(int val, ListOfOperationsGroups* ALOG);
    ExitStatus pushAtKth(int val, int k, ListOfOperationsGroups* ALOG);

    ExitStatus popFront(ListOfOperationsGroups* ALOG);
    ExitStatus popBack(ListOfOperationsGroups* ALOG);
    ExitStatus popAtKth(int k, ListOfOperationsGroups* ALOG);

    void draw();

    void reset();
    void destroy();
    
};

#endif

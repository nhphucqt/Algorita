#ifndef GRAPHIC_DYNAMIC_ARRAY_H
#define GRAPHIC_DYNAMIC_ARRAY_H

#include <vector>

#include "../../conf_raylib.h"
#include "../../global.h"
#include "GraphicNode.h"
#include "../../animation/ListOfOperationsGroups.h"
#include "../../core/ExitStatus.h"
#include "../../core/validator.h"
#include "../../core/userfunc.h"

class GraphicDynamicArray {
private:
    GraphicNode* arr;
    int _size;

    GraphicNode* oldArr;
    int _oldSize;

    void deleteCurArray();
    void deleteOldArray();
    void resetColorAllNodes();
    void resetSubTextAllNodes();

public:
    GraphicDynamicArray();

    int size() const;
    bool empty() const;

    ExitStatus initialize(int initSize, bool isRand, ListOfOperationsGroups* ALOG);
    ExitStatus initialize(const std::vector<int> &vals, ListOfOperationsGroups* ALOG);
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

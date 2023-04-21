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
    int _capacity;
    int _size;

    GraphicNode* oldArr;
    int _oldSize;

    void deleteOldArray();
    void resetColorAllNodes();

public:
    GraphicDynamicArray();

    int size() const;
    bool empty() const;

    ExitStatus initialize(int initSize, bool isRand, ListOfOperationsGroups<GraphicDynamicArray>* ALOG);
    ExitStatus initialize(const std::vector<int> &vals, ListOfOperationsGroups<GraphicDynamicArray>* ALOG);
    ExitStatus initialize(const std::string &strVals, ListOfOperationsGroups<GraphicDynamicArray>* ALOG);

    ExitStatus searchFirst(int val, ListOfOperationsGroups<GraphicDynamicArray>* ALOG);

    ExitStatus updateValue(int k, int val, ListOfOperationsGroups<GraphicDynamicArray>* ALOG);
    ExitStatus accessValue(int k, ListOfOperationsGroups<GraphicDynamicArray>* ALOG);

    ExitStatus pushBack(int val, ListOfOperationsGroups<GraphicDynamicArray>* ALOG);
    ExitStatus popBack(ListOfOperationsGroups<GraphicDynamicArray>* ALOG);

    void draw();

    void reset();
    void destroy();
    
};


#endif

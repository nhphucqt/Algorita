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
    int _size;

    void resetColorAllNodes();

public:
    GraphicStaticArray();

    int size() const;
    bool empty() const;

    ExitStatus initialize(int initSize, bool isRand, ListOfOperationsGroups<GraphicStaticArray>* ALOG);
    ExitStatus initialize(const std::vector<int> &vals, ListOfOperationsGroups<GraphicStaticArray>* ALOG);
    ExitStatus initialize(const std::string &strVals, ListOfOperationsGroups<GraphicStaticArray>* ALOG);

    ExitStatus searchFirst(int val, ListOfOperationsGroups<GraphicStaticArray>* ALOG);

    ExitStatus updateValue(int k, int val, ListOfOperationsGroups<GraphicStaticArray>* ALOG);
    ExitStatus accessValue(int k, ListOfOperationsGroups<GraphicStaticArray>* ALOG);

    void draw();

    void reset();
    void destroy();
    
};

#endif

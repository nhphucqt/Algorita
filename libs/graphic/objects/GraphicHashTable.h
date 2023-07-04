#ifndef GRAPHIC_HASHTABLE_H
#define GRAPHIC_HASHTABLE_H

#include <list>
#include "GraphicSinglyNode.h"
#include "../../core/ExitStatus.h"
#include "../../animation/ListOfOperationsGroups.h"

class GraphicHashTable {
private:
    int _size;
    GraphicSinglyNode** pHead;
    std::list<GraphicSinglyNode*> nodes;
    std::list<GraphicTrackArrow*> arrows;

    void resetColorAllNodes();
    void resetSubTextAllNodes();

    int hashFunc(int key);

public:

    GraphicHashTable();

    ExitStatus initialize(int initSize, int initNum, ListOfOperationsGroups* ALOG); // Randomly initialize
    ExitStatus initialize(int initSize, std::vector<int> vals, ListOfOperationsGroups* ALOG); // Initialize with given values
    ExitStatus initialize(std::string strVals, ListOfOperationsGroups* ALOG); // Initialize with given values

    ExitStatus searchFirst(int val, ListOfOperationsGroups* ALOG);
    ExitStatus push(int val, ListOfOperationsGroups* ALOG);
    ExitStatus popFront(ListOfOperationsGroups* ALOG);

    void draw();

    void reset();
    void clearSaparated();
    void clearArrows();
    void destroy();
};

#endif
#ifndef GRAPHIC_234_TREE_H
#define GRAPHIC_234_TREE_H

#include <list>

#include "../../global.h"
#include "../../core/ExitStatus.h"
#include "Graphic234Node.h"
#include "../../animation/OperationsGroups.h"
#include "../../animation/ListOfOperationsGroups.h"
#include "../../core/userfunc.h"
#include "../../core/ccppfunc.h"

class Graphic234Tree {
private:
    Graphic234Node* pRoot;
    std::list<GraphicTransNode*> nodes;
    std::list<Graphic234Node*> nodes234;
    int _size;

    void resetColorAllNodes(Graphic234Node* pRoot);
    void resetColorAllNodes();
    void resetTransAllNodes(Graphic234Node* pRoot);
    void resetTransAllNodes();
    void resetCurPosAllNodes(Graphic234Node* pRoot);
    void resetCurPosAllNodes();
    void clearSaparated();
    void reset();
    void destroy(Graphic234Node* pRoot);

    void applyTransToAllNodes(Graphic234Node* pRoot);
    void applyTransToAllNodes();

    void buildTransOfSubTree(Graphic234Node* pRoot);
    void buildTransOfAllNodes(Graphic234Node* pRoot);
    void buildTransOfTree();
    void animateTransformAllNodes(Graphic234Node* pRoot, ListOfOperationsGroups* ALOG);
    void balanceTreeLayout(ListOfOperationsGroups* ALOG);

    void realPush(Graphic234Node* pRoot, int val, ListOfOperationsGroups* ALOG);
    void realPush(int val, ListOfOperationsGroups* ALOG);

    void showEdgeOfTree(Graphic234Node* pRoot, ListOfOperationsGroups* ALOG);
    void showEdgeOfTree(ListOfOperationsGroups* ALOG);

    void push(Graphic234Node* pRoot, int val, ListOfOperationsGroups* ALOG);

    void draw(Graphic234Node* pRoot);

public:
    Graphic234Tree();

    ExitStatus initialize(int initSize, ListOfOperationsGroups* ALOG); // Randomly initialize
    ExitStatus initialize(std::vector<int> vals, ListOfOperationsGroups* ALOG); // Initialize with given values
    ExitStatus initialize(std::string strVals, ListOfOperationsGroups* ALOG); // Initialize with given values

    ExitStatus push(int val, ListOfOperationsGroups* ALOG);

    ExitStatus getTop(ListOfOperationsGroups* ALOG);

    ExitStatus remove(int id, ListOfOperationsGroups* ALOG);

    ExitStatus animGetSize(ListOfOperationsGroups* ALOG);

    void draw();

    void destroy();
};

#endif
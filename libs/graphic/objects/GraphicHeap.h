#ifndef GRAPHIC_HEAP_H
#define GRAPHIC_HEAP_H

#include <list>

#include "../../global.h"
#include "../../core/ExitStatus.h"
#include "GraphicBinaryTreeNode.h"
#include "../../animation/OperationsGroups.h"
#include "../../animation/ListOfOperationsGroups.h"
#include "../../core/userfunc.h"
#include "../../core/ccppfunc.h"

class GraphicHeap {
private:
    std::vector<GraphicBinaryTreeNode*> heapNodes;
    std::list<GraphicBinaryTreeNode*> nodes;
    bool isReversed; // true -> heap max, false -> heap min

    GraphicBinaryTreeNode* getRoot();

    void realPush(GraphicBinaryTreeNode* newNode);
    void realPop();

    void resetColorAllNodes();
    void resetTransAllNodes(GraphicBinaryTreeNode* pRoot);
    void resetTransAllNodes();
    void resetCurPosAllNodes(GraphicBinaryTreeNode* pRoot);
    void resetCurPosAllNodes();
    void clearSaparated();
    void reset();
    void destroy(GraphicBinaryTreeNode* pRoot);

    void applyTransToAllNodes(GraphicBinaryTreeNode* pRoot);
    void applyTransToAllNodes();

    void buildTransOfSubTree(GraphicBinaryTreeNode* pRoot);
    void buildTransOfAllNodes(GraphicBinaryTreeNode* pRoot);
    void buildTransOfTree();
    void animateTransformAllNodes(GraphicBinaryTreeNode* pRoot, ListOfOperationsGroups* ALOG);
    void balanceTreeLayout(ListOfOperationsGroups* ALOG);

    void showEdgeOfTree(GraphicBinaryTreeNode* pRoot, ListOfOperationsGroups* ALOG);
    void showEdgeOfTree(ListOfOperationsGroups* ALOG);

    void draw(GraphicBinaryTreeNode* pRoot);

    int getPar(int id);

    bool hasLeft(int id);
    bool hasRight(int id);
    int getLeft(int id);
    int getRight(int id);


    bool isPar(int x, int y);
    bool cmp(int x, int y);
    bool cmp(GraphicBinaryTreeNode* a, GraphicBinaryTreeNode* b);
    void swapParChild(int par, int child);
    void swapTwoNodes(int nodeA, int nodeB);

public:
    GraphicHeap(bool _isReversed);

    int getSize();

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
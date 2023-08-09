#ifndef GRAPHIC_AVL_TREE_H
#define GRAPHIC_AVL_TREE_H

#include <list>

#include "../../global.h"
#include "../../core/ExitStatus.h"
#include "GraphicBinaryTreeNode.h"
#include "../../animation/OperationsGroups.h"
#include "../../animation/ListOfOperationsGroups.h"
#include "../../core/userfunc.h"
#include "../../core/ccppfunc.h"

class GraphicAVLTree {
private:
    GraphicBinaryTreeNode* pRoot;
    int _size;

    std::list<GraphicBinaryTreeNode*> nodes;

    void resetColorAllNodes(GraphicBinaryTreeNode* pRoot);
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

    GraphicBinaryTreeNode* realRotateLeft(GraphicBinaryTreeNode* pNode);
    GraphicBinaryTreeNode* realRotateRight(GraphicBinaryTreeNode* pNode);
    GraphicBinaryTreeNode* realPush(GraphicBinaryTreeNode* pRoot, int val, ListOfOperationsGroups* ALOG);
    void showEdgeOfTree(GraphicBinaryTreeNode* pRoot, ListOfOperationsGroups* ALOG);
    void showEdgeOfTree(ListOfOperationsGroups* ALOG);

    void realPush(int val, ListOfOperationsGroups* ALOG);

    void checkAndRebalanceTreeFactor(GraphicBinaryTreeNode*& pRoot, ListOfOperationsGroups* ALOG);
    GraphicBinaryTreeNode* push(GraphicBinaryTreeNode* pRoot, int val, ListOfOperationsGroups* ALOG);
    void search(GraphicBinaryTreeNode* pRoot, int val, ListOfOperationsGroups* ALOG);
    GraphicBinaryTreeNode* remove(GraphicBinaryTreeNode* pRoot, int val, ListOfOperationsGroups* ALOG);
    GraphicBinaryTreeNode* removeAtRight(GraphicBinaryTreeNode* pRoot, int val, GraphicBinaryTreeNode* orgNode, ListOfOperationsGroups* ALOG);
    void draw(GraphicBinaryTreeNode* pRoot);

public:
    GraphicAVLTree();

    int getHeight(GraphicBinaryTreeNode* pNode);
    int getBalanceFactor(GraphicBinaryTreeNode* pNode);
    void updateHeight(GraphicBinaryTreeNode* pNode);

    GraphicBinaryTreeNode* rotateLeft(GraphicBinaryTreeNode* pNode, ListOfOperationsGroups* ALOG);
    GraphicBinaryTreeNode* rotateRight(GraphicBinaryTreeNode* pNode, ListOfOperationsGroups* ALOG);

    ExitStatus initialize(int initSize, ListOfOperationsGroups* ALOG); // Randomly initialize
    ExitStatus initialize(std::vector<int> vals, ListOfOperationsGroups* ALOG); // Initialize with given values
    ExitStatus initialize(std::string strVals, ListOfOperationsGroups* ALOG); // Initialize with given values

    ExitStatus push(int val, ListOfOperationsGroups* ALOG);

    ExitStatus search(int val, ListOfOperationsGroups* ALOG);

    ExitStatus remove(int val, ListOfOperationsGroups* ALOG);

    void draw();

    void destroy();
};

#endif
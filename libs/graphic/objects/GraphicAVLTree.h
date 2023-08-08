#ifndef GRAPHIC_AVL_TREE_H
#define GRAPHIC_AVL_TREE_H

#include <list>

#include "../../global.h"
#include "../../core/ExitStatus.h"
#include "GraphicBinaryTreeNode.h"
#include "../../animation/OperationsGroups.h"
#include "../../animation/ListOfOperationsGroups.h"

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

    GraphicBinaryTreeNode* push(GraphicBinaryTreeNode* pRoot, int val, ListOfOperationsGroups* ALOG);
    void search(GraphicBinaryTreeNode* pRoot, int val, ListOfOperationsGroups* ALOG);
    void draw(GraphicBinaryTreeNode* pRoot);

public:
    GraphicAVLTree();

    int getHeight(GraphicBinaryTreeNode* pNode);
    int getBalanceFactor(GraphicBinaryTreeNode* pNode);
    void updateHeight(GraphicBinaryTreeNode* pNode);

    GraphicBinaryTreeNode* rotateLeft(GraphicBinaryTreeNode* pNode, ListOfOperationsGroups* ALOG);
    GraphicBinaryTreeNode* rotateRight(GraphicBinaryTreeNode* pNode, ListOfOperationsGroups* ALOG);


    ExitStatus initialize(ListOfOperationsGroups* ALOG);

    ExitStatus push(int val, ListOfOperationsGroups* ALOG);

    ExitStatus search(int val, ListOfOperationsGroups* ALOG);


    void draw();

    void destroy();
};

#endif
#ifndef GRAPHIC_SINGLY_LINKED_LIST_H
#define GRAPHIC_SINGLY_LINKED_LIST_H

#include <assert.h>
#include <vector>
#include <map>

#include "GraphicSinglyNode.h"
#include "../../core/objects/CoreSinglyLinkedList.h"
#include "../../core/ccppfunc.h"
#include "../../core/ExitStatus.h"
#include "../../animation/animation.h"
#include "../../animation/OperationsGroups.h"
#include "../../animation/ListOfOperationsGroups.h"

class GraphicSinglyLinkedList {
// private:
public:
    GraphicSinglyNode* pHead;
    CoreSinglyLinkedList core;
    std::list<GraphicSinglyNode*> separatedNodes;

    bool registerNode(GraphicSinglyNode* node);
    bool unRegisterNode(GraphicSinglyNode* node);
    bool unRegisterAndDeleteNode(GraphicSinglyNode* node);

    void animateUnfocusAllNodes();

    bool transformAllNodes(int Tx, int Ty);
    bool transformAllNodesFrom(int Tx, int Ty, GraphicSinglyNode* start);

    bool animateInitialize(std::vector<int> vals);

    bool animatePushFront(int val);
    bool animatePushBack(int val);
    bool animatePushAtKth(int k, int val);

    bool animatePopFront();
    bool animatePopBack();
    bool animatePopAtKth(int k);

    bool animateSearchFirst(int val);

    void animateFocusAtKthNode(int k, bool isNewScene);
    void animateUnfocusAtKthNode(int k, bool isNewScene);

    void animateFocusAtKthNodeBorder(int k, bool isNewScene);
    void animateUnfocusAtKthNodeBorder(int k, bool isNewScene);

    void animateFocusAtKthArrow(int k, bool isNewScene);
    void animateUnfocusAtKthArrow(int k, bool isNewScene);

public:

    GraphicSinglyLinkedList();

    GraphicSinglyNode* KthNode(int k) const;

    void unfocusAllNodes();

    ExitStatus initialize(int initSize); // Randomly initialize
    ExitStatus initialize(std::vector<int> vals); // Initialize with given values

    ExitStatus pushFront(int val);
    ExitStatus pushBack(int val);
    ExitStatus pushAtKth(int k, int val);

    ExitStatus popFront();
    ExitStatus popBack();
    ExitStatus popAtKth(int val);

    ExitStatus searchFirst(int val);
    ExitStatus searchFirst(int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG);

    void draw();

    void makeCopy(const GraphicSinglyLinkedList &src);
    void copyAttributes(const GraphicSinglyLinkedList &src);

    void destroy();
};

#endif
#ifndef GRAPHIC_SINGLY_LINKED_LIST_H
#define GRAPHIC_SINGLY_LINKED_LIST_H

#include <assert.h>
#include <vector>

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
    int size;

    void transformAllNodesFrom(int k, int Tx, int Ty);

    void unfocusAllNodes(ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG);

    void appearAllNodes(ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG);
    void vanishAllNodes(ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG);

    void animateUnfocusAllNodes(bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group);

    void animateVanishAllNodes(bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group);
    void animateAppearAllNodes(bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group);

    void animateFadeInAtKthNode(int k, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group);
    void animateFadeOutAtKthNode(int k, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group);

    void animateFadeInAtKthArrow(int k, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group);
    void animateFadeOutAtKthArrow(int k, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group);

    void animateFocusAtKthNode(int k, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group);
    void animateUnfocusAtKthNode(int k, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group);

    void animateFocusAtKthNodeBorder(int k, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group);
    void animateUnfocusAtKthNodeBorder(int k, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group);

    void animateFocusAtKthArrow(int k, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group);
    void animateUnfocusAtKthArrow(int k, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group);

    void animateTransformAtKthNode(int k, int Tx, int Ty, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group);
    void animateDisplaceAtKthNode(int k, int Dx, int Dy, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group);

    void animateSlideInAtKthArrow(int k, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group);
    void animateSlideOutAtKthArrow(int k, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group);

    void animateTransformAllNodesFrom(int k, int Tx, int Ty, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group);

    void animateDelay(bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group);
public:

    GraphicSinglyLinkedList();

    GraphicSinglyNode* KthNode(int k) const;

    ExitStatus initialize(int initSize, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG, Codeblock* codeblock); // Randomly initialize
    ExitStatus initialize(std::vector<int> vals, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG, Codeblock* codeblock); // Initialize with given values

    ExitStatus pushFront(int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG, Codeblock* codeblock);
    
    ExitStatus searchFirst(int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG, Codeblock* codeblock);

    void draw();

    void makeCopy(GraphicSinglyLinkedList* src);

    void destroy();
};

#endif
#include "GraphicSinglyLinkedList.h"

GraphicSinglyLinkedList::GraphicSinglyLinkedList() {
    pHead = nullptr;
    size = 0;
}

GraphicSinglyNode* GraphicSinglyLinkedList::KthNode(int k) const {
    GraphicSinglyNode* curr = pHead;
    while (k-- > 0) {
        curr = curr->pNext;
    }
    return curr;
}

void GraphicSinglyLinkedList::transformAllNodesFrom(int k, int Tx, int Ty) {
    for (GraphicSinglyNode* curr = KthNode(k); curr != nullptr; curr = curr->pNext) {
        curr->lx = (curr->x += Tx);
        curr->ly = (curr->y += Ty);
    }
}

void GraphicSinglyLinkedList::unfocusAllNodes(ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) {
    // std::cerr << " start unfocusAllNodes : " << ALOG->groups.size() << '\n';
    ALOG->addNewGroup();
    ALOG->backGroup()->pushStaObj(this);
        animateUnfocusAllNodes(true, ALOG->backGroup());
        for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
            curr->unfocus();
            curr->unfocusBorder();
            curr->aNext.unfocus();
        }
    ALOG->backGroup()->pushFinObj(this);
    // std::cerr << " done unfocusAllNodes : " << ALOG->groups.size() << '\n';
}

void GraphicSinglyLinkedList::vanishAllNodes(ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) {
    ALOG->addNewGroup();
    ALOG->backGroup()->pushStaObj(this);
        animateVanishAllNodes(true, ALOG->backGroup());
        for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
            curr->vanish();
        }
    ALOG->backGroup()->pushFinObj(this);
}

void GraphicSinglyLinkedList::appearAllNodes(ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) {
    ALOG->addNewGroup();
    ALOG->backGroup()->pushStaObj(this);
        animateAppearAllNodes(true, ALOG->backGroup());
        for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
            curr->appear();
            curr->aNext.appear();
        }
    ALOG->backGroup()->pushFinObj(this);
}

void GraphicSinglyLinkedList::animateFadeInAtKthNode(int k, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group) {
    if (isNewScene) {
        group->pushNew(std::bind(&Animate::fadeInKthNode<GraphicSinglyLinkedList>, this, k, group->getCurrTime(), group->getIsReversed()));
    } else {
        group->pushBack(std::bind(&Animate::fadeInKthNode<GraphicSinglyLinkedList>, this, k, group->getCurrTime(), group->getIsReversed()));
    }
}

void GraphicSinglyLinkedList::animateFadeOutAtKthNode(int k, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group) {
    if (isNewScene) {
        group->pushNew(std::bind(&Animate::fadeOutKthNode<GraphicSinglyLinkedList>, this, k, group->getCurrTime(), group->getIsReversed()));
    } else {
        group->pushBack(std::bind(&Animate::fadeOutKthNode<GraphicSinglyLinkedList>, this, k, group->getCurrTime(), group->getIsReversed()));
    }
}

void GraphicSinglyLinkedList::animateFadeInAtKthArrow(int k, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group) {
    if (isNewScene) {
        group->pushNew(std::bind(&Animate::fadeInKthArrow<GraphicSinglyLinkedList>, this, k, group->getCurrTime(), group->getIsReversed()));
    } else {
        group->pushBack(std::bind(&Animate::fadeInKthArrow<GraphicSinglyLinkedList>, this, k, group->getCurrTime(), group->getIsReversed()));
    }
}

void GraphicSinglyLinkedList::animateFadeOutAtKthArrow(int k, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group) {
    if (isNewScene) {
        group->pushNew(std::bind(&Animate::fadeOutKthArrow<GraphicSinglyLinkedList>, this, k, group->getCurrTime(), group->getIsReversed()));
    } else {
        group->pushBack(std::bind(&Animate::fadeOutKthArrow<GraphicSinglyLinkedList>, this, k, group->getCurrTime(), group->getIsReversed()));
    }
}

void GraphicSinglyLinkedList::animateFocusAtKthNode(int k, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group) {
    // assert
    if (isNewScene) {
        group->pushNew(std::bind(&Animate::focusKthNode<GraphicSinglyLinkedList>, this, k, group->getCurrTime(), group->getIsReversed()));
    } else {
        group->pushBack(std::bind(&Animate::focusKthNode<GraphicSinglyLinkedList>, this, k, group->getCurrTime(), group->getIsReversed()));
    }
}

void GraphicSinglyLinkedList::animateUnfocusAtKthNode(int k, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group) {
    // assert
    if (isNewScene) {
        group->pushNew(std::bind(&Animate::unfocusKthNode<GraphicSinglyLinkedList>, this, k, group->getCurrTime(), group->getIsReversed()));
    } else {
        group->pushBack(std::bind(&Animate::unfocusKthNode<GraphicSinglyLinkedList>, this, k, group->getCurrTime(), group->getIsReversed()));
    }
}

void GraphicSinglyLinkedList::animateFocusAtKthNodeBorder(int k, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group) {
    // assert
    if (isNewScene) {
        group->pushNew(std::bind(&Animate::focusKthNodeBorder<GraphicSinglyLinkedList>, this, k, group->getCurrTime(), group->getIsReversed()));
    } else {
        group->pushBack(std::bind(&Animate::focusKthNodeBorder<GraphicSinglyLinkedList>, this, k, group->getCurrTime(), group->getIsReversed()));
    }
}

void GraphicSinglyLinkedList::animateUnfocusAtKthNodeBorder(int k, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group) {
    // assert
    if (isNewScene) {
        group->pushNew(std::bind(&Animate::unfocusKthNodeBorder<GraphicSinglyLinkedList>, this, k, group->getCurrTime(), group->getIsReversed()));
    } else {
        group->pushBack(std::bind(&Animate::unfocusKthNodeBorder<GraphicSinglyLinkedList>, this, k, group->getCurrTime(), group->getIsReversed()));
    }
}

void GraphicSinglyLinkedList::animateFocusAtKthArrow(int k, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group) {
    // assert
    if (isNewScene) {
        group->pushNew(std::bind(&Animate::focusKthArrow<GraphicSinglyLinkedList>, this, k, group->getCurrTime(), group->getIsReversed()));
    } else {
        group->pushBack(std::bind(&Animate::focusKthArrow<GraphicSinglyLinkedList>, this, k, group->getCurrTime(), group->getIsReversed()));
    }
}

void GraphicSinglyLinkedList::animateUnfocusAtKthArrow(int k, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group) {
    if (isNewScene) {
        group->pushNew(std::bind(&Animate::unfocusKthArrow<GraphicSinglyLinkedList>, this, k, group->getCurrTime(), group->getIsReversed()));
    } else {
        group->pushBack(std::bind(&Animate::unfocusKthArrow<GraphicSinglyLinkedList>, this, k, group->getCurrTime(), group->getIsReversed()));
    }
}

void GraphicSinglyLinkedList::animateTransformAtKthNode(int k, int Tx, int Ty, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group) {
    if (isNewScene) {
        group->pushNew(std::bind(&Animate::transformKthNode<GraphicSinglyLinkedList>, this, k, Tx, Ty, group->getCurrTime(), group->getIsReversed()));
    } else {
        group->pushBack(std::bind(&Animate::transformKthNode<GraphicSinglyLinkedList>, this, k, Tx, Ty, group->getCurrTime(), group->getIsReversed()));
    }
}

void GraphicSinglyLinkedList::animateDisplaceAtKthNode(int k, int Dx, int Dy, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group) {
    if (isNewScene) {
        group->pushNew(std::bind(&Animate::displaceKthNode<GraphicSinglyLinkedList>, this, k, Dx, Dy, group->getCurrTime(), group->getIsReversed()));
    } else {
        group->pushBack(std::bind(&Animate::displaceKthNode<GraphicSinglyLinkedList>, this, k, Dx, Dy, group->getCurrTime(), group->getIsReversed()));
    }
}

void GraphicSinglyLinkedList::animateSlideInAtKthArrow(int k, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group) {
    if (isNewScene) {
        group->pushNew(std::bind(&Animate::slideInKthArrow<GraphicSinglyLinkedList>, this, k, group->getCurrTime(), group->getIsReversed()));
    } else {
        group->pushBack(std::bind(&Animate::slideInKthArrow<GraphicSinglyLinkedList>, this, k, group->getCurrTime(), group->getIsReversed()));
    }
}

void GraphicSinglyLinkedList::animateSlideOutAtKthArrow(int k, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group) {
    if (isNewScene) {
        group->pushNew(std::bind(&Animate::slideOutKthArrow<GraphicSinglyLinkedList>, this, k, group->getCurrTime(), group->getIsReversed()));
    } else {
        group->pushBack(std::bind(&Animate::slideOutKthArrow<GraphicSinglyLinkedList>, this, k, group->getCurrTime(), group->getIsReversed()));
    }
}

void GraphicSinglyLinkedList::animateDelay(bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group) {
    if (isNewScene) {
        group->pushNew(std::bind(&Animate::delay, group->getCurrTime(), group->getIsReversed()));
    } else {
        group->pushBack(std::bind(&Animate::delay, group->getCurrTime(), group->getIsReversed()));
    }
}

void GraphicSinglyLinkedList::animateUnfocusAllNodes(bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group) {
    if (isNewScene) {
        group->pushNew(std::bind(&Animate::unfocusAllNodes<GraphicSinglyLinkedList, GraphicSinglyNode>, this, group->getCurrTime(), group->getIsReversed()));
    } else {
        group->pushBack(std::bind(&Animate::unfocusAllNodes<GraphicSinglyLinkedList, GraphicSinglyNode>, this, group->getCurrTime(), group->getIsReversed()));
    }
}

void GraphicSinglyLinkedList::animateAppearAllNodes(bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group) {
    if (isNewScene) {
        group->pushNew(std::bind(&Animate::fadeInAllNodes<GraphicSinglyLinkedList, GraphicSinglyNode>, this, group->getCurrTime(), group->getIsReversed()));
    } else {
        group->pushBack(std::bind(&Animate::fadeInAllNodes<GraphicSinglyLinkedList, GraphicSinglyNode>, this, group->getCurrTime(), group->getIsReversed()));
    }
}

void GraphicSinglyLinkedList::animateVanishAllNodes(bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group) {
    if (isNewScene) {
        group->pushNew(std::bind(&Animate::fadeOutAllNodes<GraphicSinglyLinkedList, GraphicSinglyNode>, this, group->getCurrTime(), group->getIsReversed()));
    } else {
        group->pushBack(std::bind(&Animate::fadeOutAllNodes<GraphicSinglyLinkedList, GraphicSinglyNode>, this, group->getCurrTime(), group->getIsReversed()));
    }
}


void GraphicSinglyLinkedList::animateTransformAllNodesFrom(int k, int Tx, int Ty, bool isNewScene, OperationsGroups<GraphicSinglyLinkedList>* group) {
    if (isNewScene) {
        group->pushNew(std::bind(&Animate::transformAllNodesFrom<GraphicSinglyLinkedList, GraphicSinglyNode>, this, k, Tx, Ty, group->getCurrTime(), group->getIsReversed()));
    } else {
        group->pushBack(std::bind(&Animate::transformAllNodesFrom<GraphicSinglyLinkedList, GraphicSinglyNode>, this, k, Tx, Ty, group->getCurrTime(), group->getIsReversed()));
    }
} 


ExitStatus GraphicSinglyLinkedList::initialize(int initSize, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG, Codeblock* codeblock) { // Randomly initialize
    if (initSize < 0 || initSize > Core::MAX_NUM_NODE_SLL) {
        return ExitStatus(false, "Size is out of bound");
    }
    std::vector<int> vals;
    for (int i = 0; i < initSize; ++i) {
        vals.push_back(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
    }
    return initialize(vals, ALOG, codeblock);
}

ExitStatus GraphicSinglyLinkedList::initialize(std::vector<int> vals, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG, Codeblock* codeblock) { // Initialize with given values
    // Animate::queueOfScenes.pushToNewScene(std::bind(&unfocusAllNodes, this));

    std::cerr << " start Initialize\n";
    unfocusAllNodes(ALOG);

    destroy();

    std::cerr << " >> Initialize\n";
    // Initialize
    GraphicSinglyNode* curr = pHead;
    for (int i = 0; i < (int)vals.size(); ++i) {
        if (pHead == nullptr) {
            pHead = new GraphicSinglyNode(Graphic::SLL_ORG_X, Graphic::SLL_ORG_Y, Graphic::NODE_SIZE, false, vals[i]);
            curr = pHead;
        } else {
            GraphicSinglyNode* newNode = new GraphicSinglyNode(curr->x + Graphic::SLL_NODE_DIST, curr->y, Graphic::NODE_SIZE, false, vals[i]);
            curr->setNext(newNode);
            curr = curr->pNext;
        }
    }
    size = (int)vals.size();

    ALOG->addNewGroup();
    ALOG->backGroup()->pushStaObj(this);
        appearAllNodes(ALOG);
    ALOG->backGroup()->pushFinObj(this);
    // ---

    std::cerr << " >> SlideIn all Arrows\n";
    // SlideIn all Arrows
    ALOG->addNewGroup();
    ALOG->backGroup()->pushStaObj(this);
        ALOG->backGroup()->pushBlank();
        for (int i = 0; i < (int)vals.size(); ++i) {
            animateSlideInAtKthArrow(i, false, ALOG->backGroup());
        }
        for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
            curr->aNext.maximize();   
            std::cerr << " >> " << curr->aNext.isAppear << ' ' << curr->aNext.percent << '\n';
        }
    ALOG->backGroup()->pushFinObj(this);
    //

    std::cerr << " >> OVER\n";

    return ExitStatus(true, "");
}

ExitStatus GraphicSinglyLinkedList::pushFront(int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG, Codeblock* codeblock) {
    if (size == Core::MAX_NUM_NODE_SLL) {
        return ExitStatus(false, "The size reach the maximum size allowed is " + cf::num2str(Core::MAX_NUM_NODE_SLL));
    }
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitStatus(false, "Value is out of range");
    }

    // Unfocus All node
    unfocusAllNodes(ALOG);
    // ---

    size++;

    if (pHead == nullptr) {
        // line number 0
        pHead = new GraphicSinglyNode(Graphic::SLL_ORG_X, Graphic::SLL_ORG_Y + Graphic::SLL_NODE_DIST, Graphic::NODE_SIZE, false, val);
        ALOG->addNewGroup();
        ALOG->backGroup()->pushHighlightLines({0}, codeblock);
        ALOG->backGroup()->pushStaObj(this);
            std::cerr << "GSLL::pushFront -> ALOG->bg x,y " << ALOG->backGroup()->staObj.pHead->x << ' ' << ALOG->backGroup()->staObj.pHead->y << '\n'; 
            animateFadeInAtKthNode(0, true, ALOG->backGroup());
            pHead->appear();
            animateFocusAtKthNode(0, false, ALOG->backGroup());
            pHead->focus();
            animateFocusAtKthNodeBorder(0, false, ALOG->backGroup());
            pHead->focusBorder();
        ALOG->backGroup()->pushFinObj(this);
        // ---

        // line number 1
        ALOG->addNewGroup();
        ALOG->backGroup()->pushHighlightLines({1}, codeblock);
        ALOG->backGroup()->pushStaObj(this);
            animateDelay(true, ALOG->backGroup());
        ALOG->backGroup()->pushFinObj(this);
        // ---

        // line number 2
        ALOG->addNewGroup();
        ALOG->backGroup()->pushHighlightLines({2}, codeblock);
        ALOG->backGroup()->pushStaObj(this);
            animateTransformAtKthNode(0, 0, -Graphic::SLL_NODE_DIST, true, ALOG->backGroup());
            pHead->transform(0, -Graphic::SLL_NODE_DIST);
        ALOG->backGroup()->pushFinObj(this);
        // ---
    } else {
        // line number 0
        GraphicSinglyNode* newNode = new GraphicSinglyNode(Graphic::SLL_ORG_X, Graphic::SLL_ORG_Y + Graphic::SLL_NODE_DIST, Graphic::NODE_SIZE, false, val, pHead);
        pHead = newNode;
        ALOG->addNewGroup();
        ALOG->backGroup()->pushHighlightLines({0}, codeblock);
        ALOG->backGroup()->pushStaObj(this);
            animateFadeInAtKthNode(0, true, ALOG->backGroup());
            newNode->appear();
            animateFocusAtKthNode(0, false, ALOG->backGroup());
            newNode->focus();
            animateFocusAtKthNodeBorder(0, false, ALOG->backGroup());
            newNode->focusBorder();
        ALOG->backGroup()->pushFinObj(this);
        // ---

        // line number 1
        ALOG->addNewGroup();
        ALOG->backGroup()->pushHighlightLines({1}, codeblock);
        ALOG->backGroup()->pushStaObj(this);
            animateSlideInAtKthArrow(0, true, ALOG->backGroup());
            newNode->aNext.maximize();
            animateFadeInAtKthArrow(0, false, ALOG->backGroup());
            newNode->aNext.appear();
            animateFocusAtKthArrow(0, false, ALOG->backGroup());
            newNode->aNext.focus();
        ALOG->backGroup()->pushFinObj(this);
        // ---

        // line number 2
        ALOG->addNewGroup();
        ALOG->backGroup()->pushHighlightLines({2}, codeblock);
        ALOG->backGroup()->pushStaObj(this);
            animateTransformAtKthNode(0, 0, -Graphic::SLL_NODE_DIST, true, ALOG->backGroup());
            newNode->transform(0, -Graphic::SLL_NODE_DIST);
            animateTransformAllNodesFrom(1, Graphic::SLL_NODE_DIST, 0, false, ALOG->backGroup());
            transformAllNodesFrom(1, Graphic::SLL_NODE_DIST, 0);
            animateUnfocusAtKthArrow(0, false, ALOG->backGroup());
            newNode->aNext.unfocus();
        ALOG->backGroup()->pushFinObj(this);
        // ---
    }
    
    return ExitStatus(true, "");
}

ExitStatus GraphicSinglyLinkedList::searchFirst(int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG, Codeblock* codeblock) {
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitStatus(false, "Value out of range, accept from " + cf::num2str(Core::NODE_MIN_VALUE) + " to " + cf::num2str(Core::NODE_MAX_VALUE));
    }

    // Unfocus all Nodes
    unfocusAllNodes(ALOG);
    // ---


    if (pHead == nullptr) {
        // code line 0
        ALOG->addNewGroup();
        ALOG->backGroup()->pushHighlightLines({0}, codeblock);
        ALOG->backGroup()->pushStaObj(this);
        ALOG->backGroup()->pushFinObj(this);
        // ---
        return ExitStatus(true, "");
    }

    // std::cerr << "code line 1, 2, 3\n";
    int id = 0;
    GraphicSinglyNode* pre = nullptr;
    GraphicSinglyNode* curr = pHead;

    // code line 1, 2
    ALOG->addNewGroup();
    ALOG->backGroup()->pushHighlightLines({1, 2}, codeblock);
    ALOG->backGroup()->pushStaObj(this);
        animateFocusAtKthNode(0, true, ALOG->backGroup());
        curr->focus();
        animateFocusAtKthNodeBorder(0, false, ALOG->backGroup());
        curr->focusBorder();
    ALOG->backGroup()->pushFinObj(this);
    // ---

    // std::cerr << "code line 4, 5\n";
    while (curr->nVal != val) {
        pre = curr;
        curr = curr->pNext;
        id++; 
        if (curr != nullptr) {
            // code line 3
            ALOG->addNewGroup();
            ALOG->backGroup()->pushHighlightLines({3}, codeblock);
            ALOG->backGroup()->pushStaObj(this);
                animateUnfocusAtKthNode(id-1, true, ALOG->backGroup());
                pre->unfocus();
            ALOG->backGroup()->pushFinObj(this);
            // ---

            // code line 4, 5
            ALOG->addNewGroup();
            ALOG->backGroup()->pushHighlightLines({4, 5}, codeblock);
            ALOG->backGroup()->pushStaObj(this);
                animateFocusAtKthArrow(id-1, true, ALOG->backGroup());
                pre->aNext.focus();
                animateFocusAtKthNode(id, false, ALOG->backGroup());
                curr->focus();
                animateFocusAtKthNodeBorder(id, false, ALOG->backGroup());
                curr->focusBorder();
            ALOG->backGroup()->pushFinObj(this);
            // ---
        }

        // std::cerr << "code line 5, 6\n";
        if (curr == nullptr) {
            // code line 5, 6
            ALOG->addNewGroup();
            ALOG->backGroup()->pushHighlightLines({5, 6}, codeblock);
            ALOG->backGroup()->pushStaObj(this);
                animateUnfocusAtKthNode(id-1, true, ALOG->backGroup());
                pre->unfocus();
            ALOG->backGroup()->pushFinObj(this);
            // ---
            return ExitStatus(true, "");
        }
    }

    // std::cerr << "code line 8\n";
    // code line 8
    ALOG->addNewGroup();
    ALOG->backGroup()->pushHighlightLines({8}, codeblock);
    ALOG->backGroup()->pushStaObj(this);
    ALOG->backGroup()->pushFinObj(this);
    // ---

    return ExitStatus(true, "");
}

void GraphicSinglyLinkedList::draw() {
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        std::cerr << curr->x << ' '; 
    }
    std::cerr << '\n';
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        curr->draw();
    }
}

void GraphicSinglyLinkedList::makeCopy(GraphicSinglyLinkedList* src) {
    destroy();
    if (src->pHead != nullptr) {
        pHead = new GraphicSinglyNode;
        pHead->makeCopy(src->pHead);
        GraphicSinglyNode* curr = pHead;
        GraphicSinglyNode* srcCurr = src->pHead;
        for (; srcCurr->pNext != nullptr; curr = curr->pNext, srcCurr = srcCurr->pNext) {
            GraphicSinglyNode* tmp = new GraphicSinglyNode;
            tmp->makeCopy(srcCurr->pNext);
            curr->setNext(tmp);
            curr->aNext.copyAttribute(srcCurr->aNext);
        }
    }
}

void GraphicSinglyLinkedList::destroy() {
    while (pHead != nullptr) {
        GraphicSinglyNode* tmp = pHead;
        pHead = pHead->pNext;
        delete tmp;
    }
}
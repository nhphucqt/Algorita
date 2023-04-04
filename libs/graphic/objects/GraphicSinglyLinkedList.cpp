#include "GraphicSinglyLinkedList.h"

GraphicSinglyLinkedList::GraphicSinglyLinkedList() {
    pHead = nullptr;
}

bool GraphicSinglyLinkedList::registerNode(GraphicSinglyNode* node) {
    separatedNodes.push_back(node);
    return true;
}

bool GraphicSinglyLinkedList::unRegisterNode(GraphicSinglyNode* node) {
    separatedNodes.remove(node);
    return true;
}

bool GraphicSinglyLinkedList::unRegisterAndDeleteNode(GraphicSinglyNode* node) {
    unRegisterNode(node);
    delete node;
    return true;
}

void GraphicSinglyLinkedList::animateUnfocusAllNodes() {
    Animate::queueOfScenes.pushToNewScene(
        std::bind(
            &Animate::unfocusAllNodes<GraphicSinglyLinkedList, GraphicSinglyNode>, 
            this, 
            &Animate::queueOfScenes.currTime, 
            Animate::UNFOCUS_TIME
        )
    );
}

bool GraphicSinglyLinkedList::transformAllNodes(int Tx, int Ty) {
    Animate::queueOfScenes.addBlankSceneToKth(1);
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        Animate::queueOfScenes.pushTransformToKthScene(1, curr, Tx, Ty);
    }
    return true;
}

bool GraphicSinglyLinkedList::transformAllNodesFrom(int Tx, int Ty, GraphicSinglyNode* pStart) {
    Animate::queueOfScenes.addBlankSceneToKth(1);
    for (GraphicSinglyNode* curr = pStart; curr != nullptr; curr = curr->pNext) {
        Animate::queueOfScenes.pushTransformToKthScene(1, curr, Tx, Ty);
    }
    return true;
}

// 

GraphicSinglyNode* GraphicSinglyLinkedList::KthNode(int k) const {
    GraphicSinglyNode* curr = pHead;
    while (k-- > 0) {
        curr = curr->pNext;
    }
    return curr;
}

ExitStatus GraphicSinglyLinkedList::initialize(int initSize) { // Randomly initialize
    if (initSize < 0 || initSize > Core::MAX_NUM_NODE_SLL) {
        return ExitStatus(false, "Size is out of bound");
    }
    std::vector<int> vals;
    for (int i = 0; i < initSize; ++i) {
        vals.push_back(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
    }
    return initialize(vals);
}

ExitStatus GraphicSinglyLinkedList::initialize(std::vector<int> vals) { // Initialize with given values
    core.initialize(vals);
    // Animate::queueOfScenes.pushToNewScene(std::bind(&unfocusAllNodes, this));
    Animate::queueOfScenes.pushToNewScene(std::bind(&animateInitialize, this, vals));
    return ExitStatus(true, "");
}

bool GraphicSinglyLinkedList::animateInitialize(std::vector<int> vals) {
    int Kth = 0;
    Animate::queueOfScenes.addBlankSceneToKth(++Kth);
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        registerNode(curr);
        Animate::queueOfScenes.pushSlideOutToKthScene(Kth, &curr->aNext);
    }
    Animate::queueOfScenes.addBlankSceneToKth(++Kth);
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        Animate::queueOfScenes.pushFadeOutToKthScene(Kth, curr);
    }
    Animate::queueOfScenes.addBlankSceneToKth(++Kth);
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        Animate::queueOfScenes.pushToKthScene(Kth, std::bind(&unRegisterAndDeleteNode, this, curr));
    }
    pHead = nullptr;
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
    Animate::queueOfScenes.addBlankSceneToKth(++Kth);
    for (curr = pHead; curr != nullptr; curr = curr->pNext) {
        Animate::queueOfScenes.pushFadeInToKthScene(Kth, curr);
    }
    Animate::queueOfScenes.addBlankSceneToKth(++Kth);
    for (curr = pHead; curr != nullptr; curr = curr->pNext) {
        curr->aNext.appear();
        Animate::queueOfScenes.pushSlideInToKthScene(Kth, &curr->aNext);
    }
    return true;
}

void GraphicSinglyLinkedList::animateFocusAtKthNode(int k, bool isNewScene) {
    // assert
    if (isNewScene) {
        Animate::queueOfScenes.pushToNewScene(std::bind(&Animate::focusKthNode<GraphicSinglyLinkedList>, this, k, &Animate::queueOfScenes.currTime, Animate::FOCUS_TIME));
    } else {
        Animate::queueOfScenes.pushToBackScene(std::bind(&Animate::focusKthNode<GraphicSinglyLinkedList>, this, k, &Animate::queueOfScenes.currTime, Animate::FOCUS_TIME));
    }
}

void GraphicSinglyLinkedList::animateUnfocusAtKthNode(int k, bool isNewScene) {
    // assert
    if (isNewScene) {
        Animate::queueOfScenes.pushToNewScene(std::bind(&Animate::unfocusKthNode<GraphicSinglyLinkedList>, this, k, &Animate::queueOfScenes.currTime, Animate::UNFOCUS_TIME));
    } else {
        Animate::queueOfScenes.pushToBackScene(std::bind(&Animate::unfocusKthNode<GraphicSinglyLinkedList>, this, k, &Animate::queueOfScenes.currTime, Animate::UNFOCUS_TIME));
    }
}

void GraphicSinglyLinkedList::animateFocusAtKthNodeBorder(int k, bool isNewScene) {
    // assert
    if (isNewScene) {
        Animate::queueOfScenes.pushToNewScene(std::bind(&Animate::focusKthNodeBorder<GraphicSinglyLinkedList>, this, k, &Animate::queueOfScenes.currTime, Animate::FOCUS_TIME));
    } else {
        Animate::queueOfScenes.pushToBackScene(std::bind(&Animate::focusKthNodeBorder<GraphicSinglyLinkedList>, this, k, &Animate::queueOfScenes.currTime, Animate::FOCUS_TIME));
    }
}

void GraphicSinglyLinkedList::animateUnfocusAtKthNodeBorder(int k, bool isNewScene) {
    // assert
    if (isNewScene) {
        Animate::queueOfScenes.pushToNewScene(std::bind(&Animate::unfocusKthNodeBorder<GraphicSinglyLinkedList>, this, k, &Animate::queueOfScenes.currTime, Animate::UNFOCUS_TIME));
    } else {
        Animate::queueOfScenes.pushToBackScene(std::bind(&Animate::unfocusKthNodeBorder<GraphicSinglyLinkedList>, this, k, &Animate::queueOfScenes.currTime, Animate::UNFOCUS_TIME));
    }
}

void GraphicSinglyLinkedList::animateFocusAtKthArrow(int k, bool isNewScene) {
    // assert
    if (isNewScene) {
        Animate::queueOfScenes.pushToNewScene(std::bind(&Animate::focusKthArrow<GraphicSinglyLinkedList>, this, k, &Animate::queueOfScenes.currTime, Animate::FOCUS_TIME));
    } else {
        Animate::queueOfScenes.pushToBackScene(std::bind(&Animate::focusKthArrow<GraphicSinglyLinkedList>, this, k, &Animate::queueOfScenes.currTime, Animate::FOCUS_TIME));
    }
}

void GraphicSinglyLinkedList::animateUnfocusAtKthArrow(int k, bool isNewScene) {
    if (isNewScene) {
        Animate::queueOfScenes.pushToNewScene(std::bind(&Animate::unfocusKthArrow<GraphicSinglyLinkedList>, this, k, &Animate::queueOfScenes.currTime, Animate::UNFOCUS_TIME));
    } else {
        Animate::queueOfScenes.pushToBackScene(std::bind(&Animate::unfocusKthArrow<GraphicSinglyLinkedList>, this, k, &Animate::queueOfScenes.currTime, Animate::UNFOCUS_TIME));
    }
}

void GraphicSinglyLinkedList::unfocusAllNodes() {
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        curr->unfocus();
        curr->unfocusBorder();
        curr->aNext.unfocus();
    }
}

ExitStatus GraphicSinglyLinkedList::pushFront(int val) {
    if (core.size() == Core::MAX_NUM_NODE_SLL) {
        return ExitStatus(false, "The size reach the maximum size allowed is " + cf::num2str(Core::MAX_NUM_NODE_SLL));
    }
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitStatus(false, "Value is out of range");
    }
    core.pushFront(val);
    // Animate::queueOfScenes.pushToNewScene(std::bind(&unfocusAllNodes, this));
    Animate::queueOfScenes.pushToNewScene(std::bind(&animatePushFront, this, val));
    return ExitStatus(true, "");
}

bool GraphicSinglyLinkedList::animatePushFront(int val) {
    int Kth = 0;
    if (pHead == nullptr) {
        pHead = new GraphicSinglyNode(Graphic::SLL_ORG_X, Graphic::SLL_ORG_Y, Graphic::NODE_SIZE, false, val);
        Animate::queueOfScenes.pushFadeInToNewKthScene(++Kth, pHead);
        Animate::queueOfScenes.pushFocusToKthScene(Kth, pHead);
        Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, pHead);
    } else {
        GraphicSinglyNode* newNode = new GraphicSinglyNode(Graphic::SLL_ORG_X, Graphic::SLL_ORG_Y + Graphic::SLL_NODE_DIST, Graphic::NODE_SIZE, false, val, pHead);
        Animate::queueOfScenes.pushFadeInToNewKthScene(++Kth, newNode);
        Animate::queueOfScenes.pushFocusToKthScene(Kth, newNode);
        newNode->aNext.appear();
        Animate::queueOfScenes.pushSlideInToNewKthScene(++Kth, &newNode->aNext);
        Animate::queueOfScenes.pushFocusToKthScene(Kth, &newNode->aNext);
        Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, pHead);
        Animate::queueOfScenes.addBlankSceneToKth(++Kth);
        for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
            Animate::queueOfScenes.pushTransformToKthScene(Kth, curr, Graphic::SLL_NODE_DIST, 0);
        }
        Animate::queueOfScenes.pushDisplaceToKthScene(Kth, newNode, Graphic::SLL_ORG_X, Graphic::SLL_ORG_Y);
        Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, newNode);
        Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, &newNode->aNext);
        Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, pHead);
        pHead = newNode;
    }
    return true;
}

ExitStatus GraphicSinglyLinkedList::pushBack(int val) {
    if (core.size() == Core::MAX_NUM_NODE_SLL) {
        return ExitStatus(false, "The size reach the maximum size allowed is " + cf::num2str(Core::MAX_NUM_NODE_SLL));
    }
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitStatus(false, "Value is out of range");
    }
    core.pushBack(val);
    // Animate::queueOfScenes.pushToNewScene(std::bind(&unfocusAllNodes, this));
    Animate::queueOfScenes.pushToNewScene(std::bind(&animatePushBack, this, val));
    return ExitStatus(true, "");
}

bool GraphicSinglyLinkedList::animatePushBack(int val) {
    if (pHead == nullptr) {
        pHead = new GraphicSinglyNode(Graphic::SLL_ORG_X, Graphic::SLL_ORG_Y, Graphic::NODE_SIZE, false, val);
        Animate::queueOfScenes.pushFadeInToNewKthScene(1, pHead);
    } else {
        int Kth = 0;
        GraphicSinglyNode* curr = pHead;
        Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, curr);
        for (; curr->pNext != nullptr; curr = curr->pNext) {
            Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, &curr->aNext);
            Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, curr->pNext);
            Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, curr);
            Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, &curr->aNext);
        }
        GraphicSinglyNode* newNode = new GraphicSinglyNode(curr->x + Graphic::SLL_NODE_DIST, curr->y, Graphic::NODE_SIZE, false, val);
        curr->setNext(newNode);
        curr->aNext.appear();
        curr->aNext.focus();
        Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, newNode);
        Animate::queueOfScenes.pushFadeInToKthScene(Kth, newNode);
        Animate::queueOfScenes.pushSlideInToNewKthScene(++Kth, &curr->aNext);
        Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, curr);
        Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, &curr->aNext);
        Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, newNode);
    }
    return true;
}

ExitStatus GraphicSinglyLinkedList::pushAtKth(int k, int val) {
    if (core.size() == Core::MAX_NUM_NODE_SLL) {
        return ExitStatus(false, "The size reach the maximum size allowed is " + cf::num2str(Core::MAX_NUM_NODE_SLL));
    }
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitStatus(false, "Value is out of range");
    }
    if (k < 0 || k > core.size()) {
        return ExitStatus(false, "k is out of range");
    }
    if (k == 0) {
        return pushFront(val);
    } else if (core.size() == k) {
        return pushBack(val);
    } else {
        core.pushAtKth(k, val);
        // Animate::queueOfScenes.pushToNewScene(std::bind(&unfocusAllNodes, this));
        Animate::queueOfScenes.pushToNewScene(std::bind(&animatePushAtKth, this, k, val));
        return ExitStatus(true, "");
    }
}

bool GraphicSinglyLinkedList::animatePushAtKth(int k, int val) {
    int Kth = 0;
    GraphicSinglyNode* curr = pHead;
    Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, curr);
    for (; --k; curr = curr->pNext) {
        Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, &curr->aNext);
        Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, curr->pNext);
        Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, curr);
        Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, &curr->aNext);
    }
    assert(curr != nullptr);
    GraphicSinglyNode* newNode = new GraphicSinglyNode(curr->pNext->x, curr->pNext->y + Graphic::NODE_DIST, Graphic::NODE_SIZE, false, val, curr->pNext);
    Animate::queueOfScenes.pushFadeInToNewKthScene(++Kth, newNode);
    Animate::queueOfScenes.pushFocusToKthScene(Kth, newNode);
    registerNode(newNode);
    newNode->aNext.appear();
    Animate::queueOfScenes.pushSlideInToNewKthScene(++Kth, &newNode->aNext);
    Animate::queueOfScenes.pushFocusToKthScene(Kth, &newNode->aNext);
    Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, newNode->pNext);
    Animate::queueOfScenes.pushRedirectToNewKthScene(++Kth, curr, newNode);
    Animate::queueOfScenes.pushFocusToKthScene(Kth, &curr->aNext);
    Animate::queueOfScenes.pushToNewKthScene(++Kth, std::bind(&unRegisterNode, this, newNode));
    Animate::queueOfScenes.addBlankSceneToKth(++Kth);
    for (GraphicSinglyNode* curr2 = curr->pNext; curr2 != nullptr; curr2 = curr2->pNext) {
        Animate::queueOfScenes.pushTransformToKthScene(Kth, curr2, Graphic::NODE_DIST, 0);
    }
    Animate::queueOfScenes.pushDisplaceToKthScene(Kth, newNode, curr->x + Graphic::NODE_DIST, curr->y);
    Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, curr);
    Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, &curr->aNext);
    Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, newNode);
    Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, &newNode->aNext);
    Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, newNode->pNext);
    return true;
}

ExitStatus GraphicSinglyLinkedList::popFront() {
    if (core.empty()) {
        return ExitStatus(false, "The list is empty");
    }
    // Animate::queueOfScenes.pushToNewScene(std::bind(&unfocusAllNodes, this));
    Animate::queueOfScenes.pushToNewScene(std::bind(&animatePopFront, this));
    return ExitStatus(core.popFront(), "");
}

bool GraphicSinglyLinkedList::animatePopFront() {
    int Kth = 0;
    assert(pHead != nullptr);
    registerNode(pHead);
    Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, pHead);
    Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, &pHead->aNext);
    if (pHead->pNext != nullptr) {
        Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, pHead->pNext);
    }
    Animate::queueOfScenes.pushSlideOutToNewKthScene(++Kth, &pHead->aNext);
    Animate::queueOfScenes.pushFadeOutToNewKthScene(++Kth, pHead);
    Animate::queueOfScenes.pushToNewKthScene(++Kth, std::bind(&unRegisterAndDeleteNode, this, pHead));
    Animate::queueOfScenes.pushToNewKthScene(++Kth, std::bind(&transformAllNodes, this, -Graphic::SLL_NODE_DIST, 0));
    if (pHead->pNext != nullptr) {
        Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, pHead->pNext);
    }
    pHead = pHead->pNext;
    return true;
}

ExitStatus GraphicSinglyLinkedList::popBack() {
    if (core.empty()) {
        return ExitStatus(false, "The list is empty");
    }
    if (core.size() == 1) {
        return popFront();
    }
    // Animate::queueOfScenes.pushToNewScene(std::bind(&unfocusAllNodes, this));
    Animate::queueOfScenes.pushToNewScene(std::bind(&animatePopBack, this));
    return ExitStatus(core.popBack(), "");
}

bool GraphicSinglyLinkedList::animatePopBack() {
    int Kth = 0;
    assert(pHead != nullptr);
    assert(pHead->pNext != nullptr);
    GraphicSinglyNode* curr = pHead;
    Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, curr);
    for (; curr->pNext->pNext != nullptr; curr = curr->pNext) {
        Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, &curr->aNext);
        Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, curr->pNext);
        Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, curr);
        Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, &curr->aNext);
    }
    registerNode(curr->pNext);
    Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, &curr->aNext);
    Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, curr->pNext);
    Animate::queueOfScenes.pushSlideOutToNewKthScene(++Kth, &curr->aNext);
    curr->aNext.unfocus();
    Animate::queueOfScenes.pushFadeOutToNewKthScene(++Kth, curr->pNext);
    Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, curr);
    Animate::queueOfScenes.pushToNewKthScene(++Kth, std::bind(&unRegisterAndDeleteNode, this, curr->pNext));
    Animate::queueOfScenes.pushToNewKthScene(++Kth, [curr]() {
        curr->unSetNext();
        return true;
    });
    return true;
}

ExitStatus GraphicSinglyLinkedList::popAtKth(int k) {
    if (k < 0 || k >= core.size()) {
        return ExitStatus(false, "Out of range");
    }
    if (k == 0) {
        return popFront();
    }
    if (k == core.size()-1) {
        return popBack();
    }
    core.popAtKth(k);
    // Animate::queueOfScenes.pushToNewScene(std::bind(&unfocusAllNodes, this));
    Animate::queueOfScenes.pushToNewScene(std::bind(&animatePopAtKth, this, k));
    return ExitStatus(true, "");
}

bool GraphicSinglyLinkedList::animatePopAtKth(int k) {
    int Kth = 0;
    assert(pHead != nullptr);
    GraphicSinglyNode* curr = pHead;
    Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, curr);
    for (; --k; curr = curr->pNext) {
        Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, &curr->aNext);
        Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, curr->pNext);
        Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, curr);
        Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, &curr->aNext);
    }
    assert(curr != nullptr);
    assert(curr->pNext != nullptr);
    Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, &curr->aNext);
    Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, curr->pNext);
    Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, &curr->pNext->aNext);
    Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, curr->pNext->pNext);
    Animate::queueOfScenes.pushTransformToNewKthScene(++Kth, curr->pNext, 0, Graphic::SLL_NODE_DIST);
    Animate::queueOfScenes.pushRedirectToKthScene(Kth, curr, curr->pNext->pNext);
    // Animate::queueOfScenes.pushRedirectToNewKthScene(2, curr, curr->pNext->pNext);
    registerNode(curr->pNext);
    Animate::queueOfScenes.pushSlideOutToNewKthScene(++Kth, &curr->pNext->aNext);
    Animate::queueOfScenes.pushFadeOutToNewKthScene(++Kth, curr->pNext);
    Animate::queueOfScenes.pushToNewKthScene(++Kth, std::bind(&unRegisterAndDeleteNode, this, curr->pNext));
    Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, curr);
    Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, &curr->aNext);
    Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, curr->pNext->pNext);
    curr->pNext = curr->pNext->pNext;
    Animate::queueOfScenes.pushToNewKthScene(++Kth, std::bind(&transformAllNodesFrom, this, -Graphic::SLL_NODE_DIST, 0, curr->pNext));
    return true;
}

ExitStatus GraphicSinglyLinkedList::searchFirst(int val) {
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitStatus(false, "Value out of range, accept from " + cf::num2str(Core::NODE_MIN_VALUE) + " to " + cf::num2str(Core::NODE_MAX_VALUE));
    }
    // Animate::queueOfScenes.pushToNewScene(std::bind(&unfocusAllNodes, this));
    Animate::queueOfScenes.pushToNewScene(std::bind(&animateSearchFirst, this, val));
    return ExitStatus(core.search(val), "");
}

ExitStatus GraphicSinglyLinkedList::searchFirst(int val, ListOfOperationsGroups<GraphicSinglyLinkedList>* ALOG) {
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitStatus(false, "Value out of range, accept from " + cf::num2str(Core::NODE_MIN_VALUE) + " to " + cf::num2str(Core::NODE_MAX_VALUE));
    }

    OperationsGroups<GraphicSinglyLinkedList> group;

    //
    group.reset();
    group.setObj(this);
    group.pushBackFunc(std::bind(&animateUnfocusAllNodes, this));
    unfocusAllNodes();
    ALOG->pushBackGroup(group);
    // ---


    // std::cerr << "code line 0\n";
    if (pHead == nullptr) {
        // code line 0
        group.reset();
        group.setObj(this);
        group.setHighlightLines({0});
        ALOG->pushBackGroup(group);
        // ---
        return ExitStatus(true, "");
    }

    // std::cerr << "code line 1, 2, 3\n";
    int id = 0;
    GraphicSinglyNode* pre = nullptr;
    GraphicSinglyNode* curr = pHead;

    // code line 1, 2
    group.reset();
    group.setObj(this);
    group.setHighlightLines({1, 2});
    group.pushBackFunc(std::bind(&animateFocusAtKthNode, this, 0, true));
    curr->focus();
    group.pushBackFunc(std::bind(&animateFocusAtKthNodeBorder, this, 0, false));
    curr->focusBorder();
    ALOG->pushBackGroup(group);
    // ---

    // std::cerr << "code line 4, 5\n";
    while (curr->nVal != val) {
        pre = curr;
        curr = curr->pNext;
        id++; 
        if (curr != nullptr) {
            // code line 3
            group.reset();
            group.setObj(this);
            group.setHighlightLines({3});
            group.pushBackFunc(std::bind(&animateUnfocusAtKthNode, this, id-1, true));
            pre->unfocus();
            ALOG->pushBackGroup(group);
            // ---

            // code line 4, 5
            group.reset();
            group.setObj(this);
            group.setHighlightLines({4, 5});
            group.pushBackFunc(std::bind(&animateFocusAtKthArrow, this, id-1, true));
            pre->aNext.focus();
            group.pushBackFunc(std::bind(&animateFocusAtKthNode, this, id, true));
            curr->focus();
            group.pushBackFunc(std::bind(&animateFocusAtKthNodeBorder, this, id, false));
            curr->focusBorder();
            ALOG->pushBackGroup(group);
            // ---
        }

        // std::cerr << "code line 5, 6\n";
        if (curr == nullptr) {
            // code line 5, 6
            group.reset();
            group.setObj(this);
            group.setHighlightLines({5, 6});
            group.pushBackFunc(std::bind(&animateUnfocusAtKthNode, this, id-1, true));
            pre->unfocus();
            ALOG->pushBackGroup(group);
            // ---
            return ExitStatus(true, "");
        }
    }

    // std::cerr << "code line 8\n";
    // code line 8
    group.reset();
    group.setObj(this);
    group.setHighlightLines({8});
    ALOG->pushBackGroup(group);
    // ---

    return ExitStatus(true, "");
}

bool GraphicSinglyLinkedList::animateSearchFirst(int val) {
    if (pHead != nullptr) {
        int Kth = 0;
        Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, pHead);
        GraphicSinglyNode* curr = pHead;
        for (; curr != nullptr; curr = curr->pNext) {
            if (curr->nVal == val) {
                Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, curr);
                break;
            } else if (curr->pNext != nullptr) {
                Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, &curr->aNext);
                Animate::queueOfScenes.pushFocusToNewKthScene(++Kth, curr->pNext);
                Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, curr);
                Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, &curr->aNext);
            } else {
                Animate::queueOfScenes.pushUnfocusToNewKthScene(++Kth, curr);
            }
        }
    }
    return true;
}

void GraphicSinglyLinkedList::draw() {
    // std::cerr << " >> node x: ";
    // for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
    //     std::cerr << curr->x << ' ';
    // }
    // std::cerr << '\n';
    // std::cerr << " >> node y: ";
    // for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
    //     std::cerr << curr->y << ' ';
    // }
    // std::cerr << '\n';
    // std::cerr << " >> node address: ";
    // for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
    //     std::cerr << curr << ' ';
    // }
    // std::cerr << '\n';
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        curr->draw();
    }
    for (auto curr = separatedNodes.begin(); curr != separatedNodes.end(); ++curr) {
        (*curr)->draw();
    }
}

void GraphicSinglyLinkedList::makeCopy(const GraphicSinglyLinkedList &src) {
    destroy();
    if (src.pHead != nullptr) {
        std::map<GraphicSinglyNode*, GraphicSinglyNode*> refer;
        pHead = new GraphicSinglyNode;
        pHead->makeCopy(*src.pHead);
        refer[src.pHead] = pHead;
        GraphicSinglyNode* curr = pHead;
        GraphicSinglyNode* srcCurr = src.pHead;
        for (; srcCurr->pNext != nullptr; curr = curr->pNext, srcCurr = srcCurr->pNext) {
            GraphicSinglyNode* tmp = new GraphicSinglyNode;
            tmp->makeCopy(*srcCurr->pNext);
            curr->setNext(tmp);
            curr->aNext.copyAttribute(srcCurr->aNext);
            refer[srcCurr->pNext] = curr->pNext;
        }
        for (GraphicSinglyNode* curr : src.separatedNodes) {
            separatedNodes.push_back(refer[curr]);
        }
    }
}

void GraphicSinglyLinkedList::copyAttributes(const GraphicSinglyLinkedList &src) {
    std::map<GraphicSinglyNode*, GraphicSinglyNode*> refer;
    GraphicSinglyNode* curr = pHead;
    GraphicSinglyNode* srcCurr = src.pHead;
    for (; srcCurr != nullptr; curr = curr->pNext, srcCurr = srcCurr->pNext) {
        curr->makeCopy(*srcCurr);
        curr->aNext.copyAttribute(srcCurr->aNext);
        refer[srcCurr->pNext] = curr->pNext;
    }
    separatedNodes.clear();
    for (GraphicSinglyNode* curr : src.separatedNodes) {
        separatedNodes.push_back(refer[curr]);
    }
}

void GraphicSinglyLinkedList::destroy() {
    core.destroy();
    while (pHead != nullptr) {
        GraphicSinglyNode* tmp = pHead;
        pHead = pHead->pNext;
        delete tmp;
    }
    for (auto node : separatedNodes) {
        delete node;
    }
    separatedNodes.clear();
}
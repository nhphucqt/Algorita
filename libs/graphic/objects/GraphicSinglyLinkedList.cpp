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

void GraphicSinglyLinkedList::initialize(int initSize) { // Randomly initialize
    std::vector<int> vals;
    for (int i = 0; i < initSize; ++i) {
        vals.push_back(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
    }
    initialize(vals);
}

void GraphicSinglyLinkedList::initialize(std::vector<int> vals) { // Initialize with given values
    core.initialize(vals);
    Animate::queueOfScenes.pushToNewScene(std::bind(&animateInitialize, this, vals));
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

void GraphicSinglyLinkedList::pushFront(int val) {
    core.pushFront(val);
    Animate::queueOfScenes.pushToNewScene(std::bind(&animatePushFront, this, val));
}

bool GraphicSinglyLinkedList::animatePushFront(int val) {
    if (pHead == nullptr) {
        pHead = new GraphicSinglyNode(Graphic::SLL_ORG_X, Graphic::SLL_ORG_Y, Graphic::NODE_SIZE, false, val);
        Animate::queueOfScenes.pushFadeInToNewKthScene(1, pHead);
    } else {
        GraphicSinglyNode* newNode = new GraphicSinglyNode(Graphic::SLL_ORG_X, Graphic::SLL_ORG_Y + Graphic::SLL_NODE_DIST, Graphic::NODE_SIZE, false, val, pHead);
        pHead = newNode;
        Animate::queueOfScenes.pushFadeInToNewKthScene(1, newNode);
        newNode->aNext.appear();
        Animate::queueOfScenes.pushSlideInToNewKthScene(2, &newNode->aNext);
        Animate::queueOfScenes.addBlankSceneToKth(3);
        for (GraphicSinglyNode* curr = pHead->pNext; curr != nullptr; curr = curr->pNext) {
            Animate::queueOfScenes.pushTransformToKthScene(3, curr, Graphic::SLL_NODE_DIST, 0);
        }
        Animate::queueOfScenes.pushDisplaceToKthScene(3, pHead, Graphic::SLL_ORG_X, Graphic::SLL_ORG_Y);
    }
    return true;
}

void GraphicSinglyLinkedList::pushBack(int val) {
    core.pushBack(val);
    Animate::queueOfScenes.pushToNewScene(std::bind(&animatePushBack, this, val));
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
        Animate::queueOfScenes.pushUnfocusToKthScene(Kth, newNode);
        Animate::queueOfScenes.pushUnfocusToKthScene(Kth, &curr->aNext);
    }
    return true;
}

void GraphicSinglyLinkedList::pushAtKth(int k, int val) {
    if (k == 0) {
        pushFront(val);
    } else if (core.size() == k) {
        // std::cerr << "PushAtKth -> PushBack " << val << '\n';
        pushBack(val);
    } else {
        core.pushAtKth(k, val);
        Animate::queueOfScenes.pushToNewScene(std::bind(&animatePushAtKth, this, k, val));
    }
}

bool GraphicSinglyLinkedList::animatePushAtKth(int k, int val) {
    GraphicSinglyNode* curr = pHead;
    for (; --k; curr = curr->pNext);
    assert(curr != nullptr);
    GraphicSinglyNode* newNode = new GraphicSinglyNode(curr->pNext->x, curr->pNext->y + Graphic::NODE_DIST, Graphic::NODE_SIZE, false, val, curr->pNext);
    Animate::queueOfScenes.pushFadeInToNewKthScene(1, newNode);
    registerNode(newNode);
    newNode->aNext.appear();
    Animate::queueOfScenes.pushSlideInToNewKthScene(2, &newNode->aNext);
    Animate::queueOfScenes.pushRedirectToNewKthScene(3, curr, newNode);
    Animate::queueOfScenes.pushToNewKthScene(4, std::bind(&unRegisterNode, this, newNode));
    Animate::queueOfScenes.addBlankSceneToKth(5);
    for (GraphicSinglyNode* curr2 = curr->pNext; curr2 != nullptr; curr2 = curr2->pNext) {
        Animate::queueOfScenes.pushTransformToKthScene(5, curr2, Graphic::NODE_DIST, 0);
    }
    Animate::queueOfScenes.pushDisplaceToKthScene(5, newNode, curr->x + Graphic::NODE_DIST, curr->y);
    return true;
}

bool GraphicSinglyLinkedList::popFront() {
    if (!core.popFront()) {
        return false;
    }
    Animate::queueOfScenes.pushToNewScene(std::bind(&animatePopFront, this));
    return true;
}

bool GraphicSinglyLinkedList::animatePopFront() {
    assert(pHead != nullptr);
    registerNode(pHead);
    Animate::queueOfScenes.pushFadeOutToNewKthScene(1, pHead);
    Animate::queueOfScenes.pushFadeOutToKthScene(1, &pHead->aNext);
    Animate::queueOfScenes.pushToNewKthScene(2, std::bind(&unRegisterAndDeleteNode, this, pHead));
    Animate::queueOfScenes.pushToNewKthScene(3, std::bind(&transformAllNodes, this, -Graphic::SLL_NODE_DIST, 0));
    pHead = pHead->pNext;
    return true;
}

bool GraphicSinglyLinkedList::popBack() {
    if (core.empty()) {
        return false;
    }
    if (core.size() == 1) {
        return popFront();
    }
    if (!core.popBack()) {
        return false;
    }
    Animate::queueOfScenes.pushToNewScene(std::bind(&animatePopBack, this));
    return true;
}

bool GraphicSinglyLinkedList::animatePopBack() {
    assert(pHead != nullptr);
    assert(pHead->pNext != nullptr);
    GraphicSinglyNode* curr = pHead;
    for (; curr->pNext->pNext != nullptr; curr = curr->pNext);
    registerNode(curr->pNext);
    Animate::queueOfScenes.pushSlideOutToNewKthScene(1, &curr->aNext);
    Animate::queueOfScenes.pushFadeOutToNewKthScene(2, curr->pNext);
    Animate::queueOfScenes.pushToNewKthScene(3, std::bind(&unRegisterAndDeleteNode, this, curr->pNext));
    Animate::queueOfScenes.pushToNewKthScene(4, [curr]() {
        curr->unSetNext();
        return true;
    });
    return true;
}

bool GraphicSinglyLinkedList::popAtKth(int k) {
    if (k == 0) {
        return popFront();
    }
    if (k == core.size()-1) {
        return popBack();
    }
    if (!core.popAtKth(k)) {
        return false;
    }
    Animate::queueOfScenes.pushToNewScene(std::bind(&animatePopAtKth, this, k));
    return true;
}

bool GraphicSinglyLinkedList::animatePopAtKth(int k) {
    assert(pHead != nullptr);
    GraphicSinglyNode* curr = pHead;
    for (; --k; curr = curr->pNext);
    assert(curr != nullptr);
    assert(curr->pNext != nullptr);
    Animate::queueOfScenes.pushTransformToNewKthScene(1, curr->pNext, 0, Graphic::SLL_NODE_DIST);
    Animate::queueOfScenes.pushRedirectToKthScene(1, curr, curr->pNext->pNext);
    // Animate::queueOfScenes.pushRedirectToNewKthScene(2, curr, curr->pNext->pNext);
    registerNode(curr->pNext);
    Animate::queueOfScenes.pushFadeOutToNewKthScene(2, curr->pNext);
    Animate::queueOfScenes.pushFadeOutToKthScene(2, &curr->pNext->aNext);
    Animate::queueOfScenes.pushToNewKthScene(3, std::bind(&unRegisterAndDeleteNode, this, curr->pNext));
    curr->pNext = curr->pNext->pNext;
    Animate::queueOfScenes.pushToNewKthScene(4, std::bind(&transformAllNodesFrom, this, -Graphic::SLL_NODE_DIST, 0, curr->pNext));
    return true;
}

bool GraphicSinglyLinkedList::search(int val) {
    Animate::queueOfScenes.pushToNewScene(std::bind(&animateSearch, this, val));
    return core.search(val);
}

bool GraphicSinglyLinkedList::animateSearch(int val) {
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        if (curr->nVal == val) {
            Animate::queueOfScenes.pushFocusToNewKthScene(1, curr);
            
        }
    }
}

void GraphicSinglyLinkedList::draw() {
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        curr->draw();
    }
    for (auto curr = separatedNodes.begin(); curr != separatedNodes.end(); ++curr) {
        (*curr)->draw();
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
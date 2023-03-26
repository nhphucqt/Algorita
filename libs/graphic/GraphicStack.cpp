#include "GraphicStack.h"

GraphicStack::GraphicStack() {
    pHead = nullptr;
}

bool GraphicStack::transformAllNodes(int Tx, int Ty) {
    // std::cerr << "transformAllNodes\n";
    Animate::queueOfScenes.addBlankSceneToKth(1);
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        Animate::queueOfScenes.pushTransformToKthScene(1, curr, Tx, Ty);
    }
    return true;
}

void GraphicStack::push(int val) {
    // std::cerr << "push\n";
    assert(Core::NODE_MIN_VALUE <= val && val <= Core::NODE_MAX_VALUE);
    core.push(val);
    if (pHead == nullptr) {
        pHead = new GraphicSinglyNode(Graphic::STACK_ORG_X, Graphic::STACK_ORG_Y, Graphic::NODE_SIZE, false, val);
        Animate::queueOfScenes.pushFadeInToNewScene(pHead);
    } else {
        Animate::queueOfScenes.pushToNewScene(
            std::bind(&transformAllNodes, this, 0, Graphic::STACK_NODE_DIST)
        );
        Animate::queueOfScenes.pushToNewScene(
            std::bind(&realPush, this, val)
        );
    }
}

bool GraphicStack::realPush(int val) { // ALWAYS PUSH TO NEW SCENE
    // std::cerr << "realPush\n";
    GraphicSinglyNode* newNode = new GraphicSinglyNode(Graphic::STACK_ORG_X, Graphic::STACK_ORG_Y, Graphic::NODE_SIZE, false, val, pHead);
    pHead = newNode;
    Animate::queueOfScenes.pushFadeInToNewKthScene(1, pHead);
    Animate::queueOfScenes.pushFadeInToKthScene(1, &pHead->aNext);
    return true;
}

bool GraphicStack::pop() {
    if (core.pop()) {
        Animate::queueOfScenes.pushToNewScene(
            std::bind(&animatePop, this)
        );
        return true;
    } else {
        return false;
    }
}

bool GraphicStack::animatePop() {
    // std::cerr << "animatePop\n";
    assert(pHead != nullptr);
    // std::cerr << "pop\n";
    Animate::queueOfScenes.pushFadeOutToNewKthScene(1, pHead);
    Animate::queueOfScenes.pushFadeOutToKthScene(1, &pHead->aNext);
    Animate::queueOfScenes.pushToNewKthScene(2, std::bind(&realPop, this));
    return true;
}

bool GraphicStack::realPop() { // ALWAYS PUSH TO NEW SCENE
    // std::cerr << "realPop " << pHead << '\n';
    assert(pHead != nullptr);
    GraphicSinglyNode* tmp = pHead;
    pHead = pHead->pNext;
    delete tmp;
    Animate::queueOfScenes.pushToNewKthScene(1, std::bind(&transformAllNodes, this, 0, -Graphic::STACK_NODE_DIST));
    return true;
}


void GraphicStack::draw() {
    for (GraphicSinglyNode* curr = pHead; curr != nullptr; curr = curr->pNext) {
        // std::cerr << curr->val.content << ' ' << curr->x << ' ' << curr->y << '\n';
        curr->draw();
    }
    // std::cerr << "---------------------------\n";
}

void GraphicStack::destroy() {
    core.destroy();
    while (pHead != nullptr) {
        GraphicSinglyNode* tmp = pHead;
        pHead = pHead->pNext;
        delete tmp;
    }
}
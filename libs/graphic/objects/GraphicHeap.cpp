#include "GraphicHeap.h"

GraphicBinaryTreeNode* GraphicHeap::getRoot() {
    return heapNodes.empty() ? nullptr : heapNodes[0];
}

int GraphicHeap::getSize() {
    return heapNodes.size();
}

void GraphicHeap::realPush(GraphicBinaryTreeNode* newNode) {
    newNode->setSubText(cf::num2str(heapNodes.size()));
    heapNodes.push_back(newNode);
}

void GraphicHeap::realPop() {
    heapNodes.pop_back();
}

void GraphicHeap::resetColorAllNodes() {
    for (int i = 0; i < (int)heapNodes.size(); ++i) {
        heapNodes[i]->resetColor();
    }
}

void GraphicHeap::resetTransAllNodes(GraphicBinaryTreeNode* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    pRoot->resetTrans();
    pRoot->getLeftArrow()->resetTrans();
    pRoot->getRightArrow()->resetTrans();
    resetTransAllNodes(pRoot->getLeft());
    resetTransAllNodes(pRoot->getRight());
}

void GraphicHeap::resetTransAllNodes() {
    resetTransAllNodes(getRoot());
}

void GraphicHeap::resetCurPosAllNodes(GraphicBinaryTreeNode* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    pRoot->resetCurPos();
    pRoot->getLeftArrow()->resetCurAB();
    pRoot->getRightArrow()->resetCurAB();
    resetCurPosAllNodes(pRoot->getLeft());
    resetCurPosAllNodes(pRoot->getRight());
}

void GraphicHeap::resetCurPosAllNodes() {
    resetCurPosAllNodes(getRoot());
}

int GraphicHeap::getPar(int id) {
    return (id - 1) / 2;
}

bool GraphicHeap::hasLeft(int id) {
    return getLeft(id) < (int)heapNodes.size();
}

bool GraphicHeap::hasRight(int id) {
    return getRight(id) < (int)heapNodes.size();
}

int GraphicHeap::getLeft(int id) {
    return id * 2 + 1;
}

int GraphicHeap::getRight(int id) {
    return id * 2 + 2;
}

bool GraphicHeap::isPar(int x, int y) {
    return getPar(y) == x;
}

bool GraphicHeap::cmp(int x, int y) {
    if (!isReversed) {
        return x <= y; // par <= child
    } else {
        return x >= y; // par >= child
    }
}

bool GraphicHeap::cmp(GraphicBinaryTreeNode* a, GraphicBinaryTreeNode* b) {
    return cmp(a->nVal, b->nVal);
}

void GraphicHeap::swapParChild(int par, int child) {
    assert(getPar(child) == par);
    if (par != 0) {
        int grandPar = getPar(par);
        if (par & 1) { // Left Child
            heapNodes[grandPar]->assignLeft(heapNodes[child]);
        } else {
            heapNodes[grandPar]->assignRight(heapNodes[child]);
        }
    }
    GraphicBinaryTreeNode* tmpLeft = heapNodes[par]->getLeft();
    GraphicBinaryTreeNode* tmpRight = heapNodes[par]->getRight();
    heapNodes[par]->assignLeft(heapNodes[child]->getLeft());
    heapNodes[par]->assignRight(heapNodes[child]->getRight());
    if (child & 1) { // Left Child
        heapNodes[child]->assignLeft(heapNodes[par]);
        heapNodes[child]->assignRight(tmpRight);
    } else {
        heapNodes[child]->assignRight(heapNodes[par]);
        heapNodes[child]->assignLeft(tmpLeft);
    }
    std::swap(heapNodes[child]->refLeftArrow(), heapNodes[par]->refLeftArrow());
    std::swap(heapNodes[child]->refRightArrow(), heapNodes[par]->refRightArrow());
    std::swap(heapNodes[par], heapNodes[child]);
}

void GraphicHeap::swapTwoNodes(int nodeA, int nodeB) {
    if (nodeA == nodeB) {
        return;
    }
    if (isPar(nodeA, nodeB)) {
        swapParChild(nodeA, nodeB);
    } else if (isPar(nodeB, nodeA)) {
        swapParChild(nodeB, nodeA);
    } else {
        int parA = nodeA == 0 ? -1 : getPar(nodeA);
        int parB = nodeB == 0 ? -1 : getPar(nodeB);
        if (parA != -1) {
            if (nodeA & 1) {
                heapNodes[parA]->assignLeft(heapNodes[nodeB]);
            } else {
                heapNodes[parA]->assignRight(heapNodes[nodeB]);
            }
        }
        if (parB != -1) {
            if (nodeB & 1) {
                heapNodes[parB]->assignLeft(heapNodes[nodeA]);
            } else {
                heapNodes[parB]->assignRight(heapNodes[nodeA]);
            }
        }
        GraphicBinaryTreeNode* aLeft = heapNodes[nodeA]->getLeft();
        GraphicBinaryTreeNode* aRight = heapNodes[nodeA]->getRight();
        heapNodes[nodeA]->assignLeft(heapNodes[nodeB]->getLeft());
        heapNodes[nodeA]->assignRight(heapNodes[nodeB]->getRight());
        heapNodes[nodeB]->assignLeft(aLeft);
        heapNodes[nodeB]->assignRight(aRight);
        std::swap(heapNodes[nodeA]->refLeftArrow(), heapNodes[nodeB]->refLeftArrow());
        std::swap(heapNodes[nodeA]->refRightArrow(), heapNodes[nodeB]->refRightArrow());
        std::swap(heapNodes[nodeA], heapNodes[nodeB]);
    }
}

GraphicHeap::GraphicHeap(bool _isReversed) {
    heapNodes.clear();
    nodes.clear();
    isReversed = _isReversed;
}

void GraphicHeap::showEdgeOfTree(GraphicBinaryTreeNode* pRoot, ListOfOperationsGroups* ALOG) {
    if (pRoot->getLeft() != nullptr) {
        ALOG->animateFadeIn(pRoot->getLeftArrow());
        ALOG->animateSlideIn(pRoot->getLeftArrow());
        showEdgeOfTree(pRoot->getLeft(), ALOG);
    }
    if (pRoot->getRight() != nullptr) {
        ALOG->animateFadeIn(pRoot->getRightArrow());
        ALOG->animateSlideIn(pRoot->getRightArrow());
        showEdgeOfTree(pRoot->getRight(), ALOG);
    }
}

void GraphicHeap::showEdgeOfTree(ListOfOperationsGroups* ALOG) {
    if (getRoot() == nullptr) {
        return;
    }
    showEdgeOfTree(getRoot(), ALOG);
}

ExitStatus GraphicHeap::initialize(int initSize, ListOfOperationsGroups* ALOG) { // Randomly initialize 
    if (initSize < 0 || initSize > Core::MAX_NUM_HEAP_ELM) {
        return ExitMess::FAIL_HEAP_SIZE_OOB;
    }
    std::vector<int> vals;
    for (int i = Core::NODE_MIN_VALUE; i <= Core::NODE_MAX_VALUE; ++i) {
        vals.push_back(i);
    }
    std::random_shuffle(vals.begin(), vals.end());
    vals.resize(initSize);
    return initialize(vals, ALOG);
}

ExitStatus GraphicHeap::initialize(std::vector<int> vals, ListOfOperationsGroups* ALOG) { // Initialize with given values
    if ((int)vals.size() > Core::MAX_NUM_HEAP_ELM) {
        return ExitMess::FAIL_HEAP_SIZE_OOB;
    }
    for (int i = 0; i < (int)vals.size(); ++i) {
        if (vals[i] < Core::NODE_MIN_VALUE || vals[i] > Core::NODE_MAX_VALUE) {
            return ExitMess::FAIL_VALUE_OOB;
        }
    }

    ALOG->clearGroup();
    ALOG->resetCode();
    destroy();

    if (!vals.empty()) {
        realPush(new GraphicBinaryTreeNode(
            Graphic::BST_ORG_X, 
            Graphic::BST_ORG_Y,
            Graphic::NODE_SIZE_SMALL,
            Graphic::NODE_BORDER_WIDTH_SMALL, 
            false,
            Gfont::defaultFontSmall,
            vals[0],
            ""
        ));

        for (int i = 1; i < (int)vals.size(); ++i) {
            if (i & 1) {
                realPush(new GraphicBinaryTreeNode(
                    heapNodes[getPar(i)]->getNewTransPos().x + heapNodes[getPar(i)]->size/2 - Graphic::BST_HORIZONTAL_MARGIN - Graphic::NODE_SIZE_SMALL,
                    heapNodes[getPar(i)]->getNewTransPos().y + heapNodes[getPar(i)]->size + Graphic::BST_VERTICAL_MARGIN,
                    Graphic::NODE_SIZE_SMALL,
                    Graphic::NODE_BORDER_WIDTH_SMALL, 
                    false,
                    Gfont::defaultFontSmall,
                    vals[i],
                    ""
                ));
                heapNodes[getPar(i)]->setLeft(heapNodes[i]);
            } else {
                realPush(new GraphicBinaryTreeNode(
                    heapNodes[getPar(i)]->getNewTransPos().x + heapNodes[getPar(i)]->size/2 + Graphic::BST_HORIZONTAL_MARGIN, 
                    heapNodes[getPar(i)]->getNewTransPos().y + heapNodes[getPar(i)]->size + Graphic::BST_VERTICAL_MARGIN,
                    Graphic::NODE_SIZE_SMALL,
                    Graphic::NODE_BORDER_WIDTH_SMALL, 
                    false,
                    Gfont::defaultFontSmall,
                    vals[i],
                    ""
                ));
                heapNodes[getPar(i)]->setRight(heapNodes[i]);
            }

            int id = i;
            while (id > 0 && !cmp(heapNodes[getPar(id)], heapNodes[id])) {
                swapTwoNodes(getPar(id), id);
                id = getPar(id);
            }
        }
        ALOG->addNewGroup();
        for (int i = 0; i < getSize(); ++i) {
            ALOG->animateFadeIn(heapNodes[i]);
            heapNodes[i]->setSubText(cf::num2str(i));
        }
        balanceTreeLayout(ALOG);

        ALOG->addNewGroup();
        showEdgeOfTree(ALOG);
    } else {
        ALOG->addNewGroup();
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicHeap::initialize(std::string strVals, ListOfOperationsGroups* ALOG) { // Initialize with given values
    ExitStatus status;
    std::vector<int> vals;
    status = User::input2vector(strVals, vals, Valid::DIGIT + " ,\r\n");
    if (!status.success) {
        return status;
    }
    return initialize(vals, ALOG);
}

void GraphicHeap::applyTransToAllNodes(GraphicBinaryTreeNode* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    pRoot->applyTrans();
    if (pRoot->getLeft() != nullptr) {
        pRoot->getLeftArrow()->applyTransAB();
        applyTransToAllNodes(pRoot->getLeft());
    }
    if (pRoot->getRight() != nullptr) {
        pRoot->getRightArrow()->applyTransAB();
        applyTransToAllNodes(pRoot->getRight());
    }
}

void GraphicHeap::applyTransToAllNodes() {
    applyTransToAllNodes(getRoot());
}

void GraphicHeap::buildTransOfSubTree(GraphicBinaryTreeNode* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    buildTransOfSubTree(pRoot->getLeft());
    buildTransOfSubTree(pRoot->getRight());
    pRoot->solveLeftCollision();
    pRoot->solveRightCollision();
    pRoot->upateDimens();
    if (pRoot == this->getRoot()) {
        pRoot->updateTransFromPos(Vector2{(float)Graphic::BST_ORG_X, (float)Graphic::BST_ORG_Y});
    }
}

void GraphicHeap::buildTransOfAllNodes(GraphicBinaryTreeNode* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    if (pRoot->getLeft() != nullptr) {
        pRoot->getLeft()->addTrans(pRoot->getTrans());
        pRoot->getLeftArrow()->updateTransFromPos(GraphicBinaryTreeNode::getPosition(pRoot, pRoot->getLeft()));
        buildTransOfAllNodes(pRoot->getLeft());
    }
    if (pRoot->getRight() != nullptr) {
        pRoot->getRight()->addTrans(pRoot->getTrans());
        pRoot->getRightArrow()->updateTransFromPos(GraphicBinaryTreeNode::getPosition(pRoot, pRoot->getRight()));
        buildTransOfAllNodes(pRoot->getRight());
    }
}

void GraphicHeap::buildTransOfTree() {
    buildTransOfSubTree(getRoot());
    buildTransOfAllNodes(getRoot());
}

void GraphicHeap::animateTransformAllNodes(GraphicBinaryTreeNode* pRoot, ListOfOperationsGroups* ALOG) {
    if (pRoot == nullptr) {
        return;
    }
    if (pRoot->isTrans()) {
        ALOG->animateTransform(pRoot, pRoot->getCurPos().x, pRoot->getCurPos().y, pRoot->getTrans().x, pRoot->getTrans().y);
    }
    if (pRoot->getLeft() != nullptr) {
        if (pRoot->getLeftArrow()->isTransA()) {
            ALOG->animateTransform(&pRoot->getLeftArrow()->pA, pRoot->getLeftArrow()->curA.x, pRoot->getLeftArrow()->curA.y, pRoot->getLeftArrow()->transA.x, pRoot->getLeftArrow()->transA.y);
        }
        if (pRoot->getLeftArrow()->isTransB()) {
            ALOG->animateTransform(&pRoot->getLeftArrow()->pB, pRoot->getLeftArrow()->curB.x, pRoot->getLeftArrow()->curB.y, pRoot->getLeftArrow()->transB.x, pRoot->getLeftArrow()->transB.y);
        }
        animateTransformAllNodes(pRoot->getLeft(), ALOG);
    }
    if (pRoot->getRight() != nullptr) {
        if (pRoot->getRightArrow()->isTransA()) {
            ALOG->animateTransform(&pRoot->getRightArrow()->pA, pRoot->getRightArrow()->curA.x, pRoot->getRightArrow()->curA.y, pRoot->getRightArrow()->transA.x, pRoot->getRightArrow()->transA.y);
        }
        if (pRoot->getRightArrow()->isTransB()) {
            ALOG->animateTransform(&pRoot->getRightArrow()->pB, pRoot->getRightArrow()->curB.x, pRoot->getRightArrow()->curB.y, pRoot->getRightArrow()->transB.x, pRoot->getRightArrow()->transB.y);
        }
        animateTransformAllNodes(pRoot->getRight(), ALOG);
    }
}

void GraphicHeap::balanceTreeLayout(ListOfOperationsGroups* ALOG) {
    applyTransToAllNodes();
    resetTransAllNodes();
    buildTransOfTree();
    animateTransformAllNodes(getRoot(), ALOG);
}

ExitStatus GraphicHeap::push(int val, ListOfOperationsGroups* ALOG) {
    assert((int)heapNodes.size() <= Core::MAX_NUM_HEAP_ELM);
    if ((int)heapNodes.size() == Core::MAX_NUM_HEAP_ELM) {
        return ExitMess::FAIL_HEAP_REACH_MAX_SIZE;
    }
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }

    ALOG->clearGroup();
    if (!isReversed) {
        ALOG->loadCode(CPath::HEAP_MIN_PUSH);
    } else {
        ALOG->loadCode(CPath::HEAP_MAX_PUSH);
    }
    reset();

    if (getRoot() == nullptr) {
        GraphicBinaryTreeNode* newNode = new GraphicBinaryTreeNode(
            Graphic::BST_ORG_X, 
            Graphic::BST_ORG_Y,
            Graphic::NODE_SIZE_SMALL,
            Graphic::NODE_BORDER_WIDTH_SMALL, 
            false,
            Gfont::defaultFontSmall,
            val,
            ""
        );
        realPush(newNode);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateFadeIn(newNode);
        ALOG->animateNodeFromNormalToIter(newNode);
    } else {
        int id = heapNodes.size();
        int par = getPar(id);
        GraphicBinaryTreeNode* newNode = nullptr;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0,1});
        if (id & 1) { // Left Child
            newNode = new GraphicBinaryTreeNode(
                heapNodes[par]->getNewTransPos().x + heapNodes[par]->size/2 - Graphic::BST_HORIZONTAL_MARGIN - Graphic::NODE_SIZE_SMALL, 
                heapNodes[par]->getNewTransPos().y + heapNodes[par]->size + Graphic::BST_VERTICAL_MARGIN,
                Graphic::NODE_SIZE_SMALL,
                Graphic::NODE_BORDER_WIDTH_SMALL, 
                false,
                Gfont::defaultFontSmall,
                val,
                ""
            );
            heapNodes[par]->setLeft(newNode);
            ALOG->animateFadeIn(heapNodes[par]->getLeftArrow());
            ALOG->animateSlideIn(heapNodes[par]->getLeftArrow());
        } else {
            newNode = new GraphicBinaryTreeNode(
                heapNodes[par]->getNewTransPos().x + heapNodes[par]->size/2 + Graphic::BST_HORIZONTAL_MARGIN, 
                heapNodes[par]->getNewTransPos().y + heapNodes[par]->size + Graphic::BST_VERTICAL_MARGIN,
                Graphic::NODE_SIZE_SMALL,
                Graphic::NODE_BORDER_WIDTH_SMALL, 
                false,
                Gfont::defaultFontSmall,
                val,
                ""
            );
            heapNodes[par]->setRight(newNode);
            ALOG->animateFadeIn(heapNodes[par]->getRightArrow());
            ALOG->animateSlideIn(heapNodes[par]->getRightArrow());
        }
        ALOG->animateFadeIn(newNode);
        ALOG->animateNodeFromNormalToIter(newNode);
        balanceTreeLayout(ALOG);
        realPush(newNode);
        int tmp = heapNodes[id]->nVal;
        if (id > 0 && !cmp(heapNodes[getPar(id)]->nVal, tmp)) {
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({2});
        }
        while (id > 0 && !cmp(heapNodes[getPar(id)]->nVal, tmp)) {
            ALOG->animateNodeFromNormalToNearIter(heapNodes[getPar(id)]);

            swapTwoNodes(getPar(id), id);
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({3});
            balanceTreeLayout(ALOG);
            ALOG->animateTransText(&heapNodes[id]->sub, cf::num2str(getPar(id)), cf::num2str(id));
            ALOG->animateTransText(&heapNodes[getPar(id)]->sub, cf::num2str(id), cf::num2str(getPar(id)));

            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({2});
            ALOG->animateNodeFromNearIterToNormal(heapNodes[id]);

            id = getPar(id);
        }
    }

    ALOG->addNewGroup();

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicHeap::getTop(ListOfOperationsGroups* ALOG) {
    if (getSize() == 0) {
        return ExitMess::FAIL_HEAP_EMPTY;
    }

    ALOG->clearGroup();
    if (!isReversed) {
        ALOG->loadCode(CPath::HEAP_MIN_GET_TOP);
    } else {
        ALOG->loadCode(CPath::HEAP_MAX_GET_TOP);
    }
    reset();

    if (heapNodes.size() == 1) {
        nodes.push_back(getRoot());
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateNodeFromNormalToIter(getRoot());
        
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        ALOG->animateFadeOut(getRoot());
        realPop();
    } else {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateNodeFromNormalToIter(getRoot());
        ALOG->animateNodeFromNormalToNearIter(heapNodes.back());

        swapTwoNodes(0, (int)heapNodes.size()-1);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        balanceTreeLayout(ALOG);
        ALOG->animateTransText(&heapNodes[0]->sub, cf::num2str((int)heapNodes.size()-1), cf::num2str(0));
        ALOG->animateTransText(&heapNodes.back()->sub, cf::num2str(0), cf::num2str((int)heapNodes.size()-1));

        nodes.push_back(heapNodes.back());
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1,2});
        ALOG->animateFadeOut(heapNodes.back());
        ALOG->animateNodeFromNearIterToIter(heapNodes[0]);
        if (((int)heapNodes.size()-1) & 1) {
            ALOG->animateSlideOut(heapNodes[getPar((int)heapNodes.size()-1)]->getLeftArrow());
        } else {
            ALOG->animateSlideOut(heapNodes[getPar((int)heapNodes.size()-1)]->getRightArrow());
        }
        if (((int)heapNodes.size()-1) & 1) {
            heapNodes[getPar((int)heapNodes.size()-1)]->setLeft(nullptr);
        } else {
            heapNodes[getPar((int)heapNodes.size()-1)]->setRight(nullptr);
        }
        realPop();
        balanceTreeLayout(ALOG);

        int id = 0;
        while ((hasLeft(id) && !cmp(heapNodes[id], heapNodes[getLeft(id)])) || (hasRight(id) && !cmp(heapNodes[id], heapNodes[getRight(id)]))) {
            int child = -1;
            if (hasLeft(id) && hasRight(id)) {
                if (cmp(heapNodes[getLeft(id)], heapNodes[getRight(id)])) {
                    swapTwoNodes(id, getLeft(id));
                    child = getLeft(id);
                } else {
                    swapTwoNodes(id, getRight(id));
                    child = getRight(id);
                }
            } else {
                if (hasLeft(id)) {
                    swapTwoNodes(id, getLeft(id));
                    child = getLeft(id);
                } else {
                    swapTwoNodes(id, getRight(id));
                    child = getRight(id);
                }
            }

            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({3});
            ALOG->animateNodeFromNormalToNearIter(heapNodes[id]);

            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({4});
            balanceTreeLayout(ALOG);
            ALOG->animateTransText(&heapNodes[id]->sub, cf::num2str(child), cf::num2str(id));
            ALOG->animateTransText(&heapNodes[child]->sub, cf::num2str(id), cf::num2str(child));

            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({4});
            ALOG->animateNodeFromNearIterToNormal(heapNodes[id]);

            id = child;
        }
    }

    ALOG->addNewGroup();

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicHeap::remove(int id, ListOfOperationsGroups* ALOG) {
    if (getSize() == 0) {
        return ExitMess::FAIL_HEAP_EMPTY;
    }
    if (id < 0 || id >= getSize()) {
        return ExitStatus(false, "Position is out of bounds: Allow from 0 to " + cf::num2str(getSize()-1));
    }

    if (id == 0) {
        return getTop(ALOG);
    }

    ALOG->clearGroup();
    if (!isReversed) {
        ALOG->loadCode(CPath::HEAP_MIN_REMOVE);
    } else {
        ALOG->loadCode(CPath::HEAP_MAX_REMOVE);
    }
    reset();

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({0});
    ALOG->animateNodeFromNormalToIter(heapNodes[id]);
    
    int curVal = 0;
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({0});
    if (!isReversed) {
        ALOG->animateAssignValue(heapNodes[id], heapNodes[id]->nVal, getRoot()->nVal-1);
        curVal = getRoot()->nVal - 1;
    } else {
        ALOG->animateAssignValue(heapNodes[id], heapNodes[id]->nVal, getRoot()->nVal+1);
        curVal = getRoot()->nVal + 1;
    }
    
    if (id > 0 && !cmp(heapNodes[getPar(id)]->nVal, curVal)) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
    }
    while (id > 0 && !cmp(heapNodes[getPar(id)]->nVal, curVal)) {
        ALOG->animateNodeFromNormalToNearIter(heapNodes[getPar(id)]);

        swapTwoNodes(getPar(id), id);
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        balanceTreeLayout(ALOG);
        ALOG->animateTransText(&heapNodes[id]->sub, cf::num2str(getPar(id)), cf::num2str(id));
        ALOG->animateTransText(&heapNodes[getPar(id)]->sub, cf::num2str(id), cf::num2str(getPar(id)));

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({1});
        ALOG->animateNodeFromNearIterToNormal(heapNodes[id]);

        id = getPar(id);
    }
    
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({2});
    ALOG->animateNodeFromNormalToNearIter(heapNodes.back());

    swapTwoNodes(0, (int)heapNodes.size()-1);
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({2});
    balanceTreeLayout(ALOG);
    ALOG->animateTransText(&heapNodes[0]->sub, cf::num2str((int)heapNodes.size()-1), cf::num2str(0));
    ALOG->animateTransText(&heapNodes.back()->sub, cf::num2str(0), cf::num2str((int)heapNodes.size()-1));

    nodes.push_back(heapNodes.back());
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({2});
    ALOG->animateFadeOut(heapNodes.back());
    ALOG->animateNodeFromNearIterToIter(heapNodes[0]);
    if (((int)heapNodes.size()-1) & 1) {
        ALOG->animateSlideOut(heapNodes[getPar((int)heapNodes.size()-1)]->getLeftArrow());
    } else {
        ALOG->animateSlideOut(heapNodes[getPar((int)heapNodes.size()-1)]->getRightArrow());
    }
    if (((int)heapNodes.size()-1) & 1) {
        heapNodes[getPar((int)heapNodes.size()-1)]->setLeft(nullptr);
    } else {
        heapNodes[getPar((int)heapNodes.size()-1)]->setRight(nullptr);
    }
    realPop();
    balanceTreeLayout(ALOG);

    while ((hasLeft(id) && !cmp(heapNodes[id], heapNodes[getLeft(id)])) || (hasRight(id) && !cmp(heapNodes[id], heapNodes[getRight(id)]))) {
        int child = -1;
        if (hasLeft(id) && hasRight(id)) {
            if (cmp(heapNodes[getLeft(id)], heapNodes[getRight(id)])) {
                swapTwoNodes(id, getLeft(id));
                child = getLeft(id);
            } else {
                swapTwoNodes(id, getRight(id));
                child = getRight(id);
            }
        } else {
            if (hasLeft(id)) {
                swapTwoNodes(id, getLeft(id));
                child = getLeft(id);
            } else {
                swapTwoNodes(id, getRight(id));
                child = getRight(id);
            }
        }

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        ALOG->animateNodeFromNormalToNearIter(heapNodes[id]);

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        balanceTreeLayout(ALOG);
        ALOG->animateTransText(&heapNodes[id]->sub, cf::num2str(getRight(id)), cf::num2str(id));
        ALOG->animateTransText(&heapNodes[child]->sub, cf::num2str(id), cf::num2str(child));

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        ALOG->animateNodeFromNearIterToNormal(heapNodes[id]);

        id = child;
    }

    ALOG->addNewGroup();

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicHeap::animGetSize(ListOfOperationsGroups* ALOG) {
    ALOG->clearGroup();
    if (!isReversed) {
        ALOG->loadCode(CPath::HEAP_MIN_GET_SIZE);
    } else {
        ALOG->loadCode(CPath::HEAP_MAX_GET_SIZE);
    }
    reset();

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({0});

    ALOG->build();

    return ExitStatus(true, "The size of the Heap is " + cf::num2str(getSize()));
}

void GraphicHeap::draw(GraphicBinaryTreeNode* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    pRoot->draw();
    draw(pRoot->getLeft());
    draw(pRoot->getRight());
}

void GraphicHeap::draw() {
    draw(getRoot());
    for (GraphicBinaryTreeNode* pNode : nodes) {
        pNode->draw();
    }
}


void GraphicHeap::clearSaparated() {
    for (GraphicBinaryTreeNode* node : nodes) {
        delete node;
    }
    nodes.clear();
}

void GraphicHeap::reset() {
    clearSaparated();
    resetColorAllNodes();
    resetTransAllNodes();
    resetCurPosAllNodes();
}

void GraphicHeap::destroy(GraphicBinaryTreeNode* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    destroy(pRoot->getLeft());
    destroy(pRoot->getRight());
    delete pRoot;
}


void GraphicHeap::destroy() {
    reset();
    destroy(getRoot());
    heapNodes.clear();
}
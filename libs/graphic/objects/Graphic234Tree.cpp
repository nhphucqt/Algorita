#include "Graphic234Tree.h"

void Graphic234Tree::resetColorAllNodes(Graphic234Node* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    pRoot->resetColor();
    for (int i = 0; i < pRoot->getNumArrow(); ++i) {
        pRoot->getArrow(i)->resetColor();
    }
    for (int i = 0; i < pRoot->getNumChild(); ++i) {
        resetColorAllNodes(pRoot->getChild(i));
    }
}

void Graphic234Tree::resetColorAllNodes() {
    resetColorAllNodes(pRoot);
}

void Graphic234Tree::resetTransAllNodes(Graphic234Node* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    pRoot->resetTrans();
    for (int i = 0; i < pRoot->getNumArrow(); ++i) {
        pRoot->getArrow(i)->resetTrans();
    }
    for (int i = 0; i < pRoot->getNumChild(); ++i) {
        resetTransAllNodes(pRoot->getChild(i));
    }
}

void Graphic234Tree::resetTransAllNodes() {
    resetTransAllNodes(pRoot);
}

void Graphic234Tree::resetCurPosAllNodes(Graphic234Node* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    pRoot->resetCurPos();
    for (int i = 0; i < pRoot->getNumArrow(); ++i) {
        pRoot->getArrow(i)->resetCurAB();
    }
    for (int i = 0; i < pRoot->getNumChild(); ++i) {
        resetCurPosAllNodes(pRoot->getChild(i));
    }
}

void Graphic234Tree::resetCurPosAllNodes() {
    resetCurPosAllNodes(pRoot);
}

Graphic234Tree::Graphic234Tree() {
    pRoot = nullptr;
    _size = 0;
}

void Graphic234Tree::realPush(Graphic234Node* pRoot, int val, ListOfOperationsGroups* ALOG) {
    if (pRoot->getNumChild() == 0) {
        for (int i = 0; i < pRoot->getNumVals(); ++i) {
            if (pRoot->getVal(i)->nVal == val) {
                return;
            }
        }
        GraphicTransNode* newNode = new GraphicTransNode(
            pRoot->getNewTransPos().x, 
            pRoot->getNewTransPos().y, 
            Graphic::NODE_SIZE_SMALL,
            Graphic::NODE_BORDER_WIDTH_SMALL, 
            true,
            Gfont::defaultFontSmall,
            val,
            ""
        );
        _size++;
        pRoot->pushVal(newNode);
        ALOG->animateFadeIn(newNode);
        return;
    }
    int p = 0;
    while (p < pRoot->getNumVals() && pRoot->getVal(p)->nVal < val) {
        p++;
    }
    if (p < pRoot->getNumVals() && pRoot->getVal(p)->nVal == val) {
        return;
    }
    if (pRoot->getChild(p)->getNumVals() == 3) {
        Graphic234Node* pLeft = pRoot->getChild(p);
        Graphic234Node* pRight = new Graphic234Node(
            pRoot->getChild(p)->getNewTransPos().x,
            pRoot->getChild(p)->getNewTransPos().y
        );

        pRoot->pushVal(pLeft->getVal(1));
        pRoot->pushChild(pRight, p+1);

        pRight->pushVal(pLeft->getVal(2));
        if (pLeft->getNumChild() > 0) {
            pRight->pushArrow(pLeft->getArrow(2));
            pRight->pushArrow(pLeft->getArrow(3));
            pRight->pushChild(pLeft->getChild(2));
            pRight->pushChild(pLeft->getChild(3));
        }

        std::pair<Vector2, Vector2> nodePair = Graphic234Node::getPosition(pRoot, pRight, p+1);
        GraphicArrow* aRight = new GraphicArrow(Graphic::ARROW_LINE_WIDTH_SMALL, nodePair.first, nodePair.second);
        pRoot->pushArrow(aRight, p+1);

        pLeft->popBackVal();
        pLeft->popBackVal();
        if (pLeft->getNumChild() > 0) {
            pLeft->popBackChild();
            pLeft->popBackChild();
            pLeft->popBackArrow();
            pLeft->popBackArrow();
        }
        if (pRoot->getVal(p)->nVal < val) {
            p++;
        }
        if (p < pRoot->getNumVals() && pRoot->getVal(p)->nVal == val) {
            return;
        }
    }
    realPush(pRoot->getChild(p), val, ALOG);
}


void Graphic234Tree::realPush(int val, ListOfOperationsGroups* ALOG) {
    if (pRoot == nullptr) {
        pRoot = new Graphic234Node(
            Graphic::T234_ORG_X, 
            Graphic::T234_ORG_Y
        );
    }
    if (pRoot->getNumVals() == 3) {
        Graphic234Node* newLeft = new Graphic234Node(
            Graphic::T234_ORG_X,
            Graphic::T234_ORG_Y
        );
        Graphic234Node* newRight = new Graphic234Node(
            Graphic::T234_ORG_X,
            Graphic::T234_ORG_Y
        );
        newLeft->pushVal(pRoot->getVal(0));
        if (pRoot->getNumChild() > 0) {
            newLeft->pushArrow(pRoot->getArrow(0));
            newLeft->pushArrow(pRoot->getArrow(1));
            newLeft->pushChild(pRoot->getChild(0));
            newLeft->pushChild(pRoot->getChild(1));
        }

        newRight->pushVal(pRoot->getVal(2));
        if (pRoot->getNumChild() > 0) {
            newRight->pushArrow(pRoot->getArrow(2));
            newRight->pushArrow(pRoot->getArrow(3));
            newRight->pushChild(pRoot->getChild(2));
            newRight->pushChild(pRoot->getChild(3));
        }

        pRoot->clearArrows();
        pRoot->clearChild();
        pRoot->keepMiddle();
        pRoot->pushChild(newLeft);
        pRoot->pushChild(newRight);
        std::pair<Vector2, Vector2> nodePair = Graphic234Node::getPosition(pRoot, newLeft, 0);
        GraphicArrow* aLeft = new GraphicArrow(Graphic::ARROW_LINE_WIDTH_SMALL, nodePair.first, nodePair.second);
        pRoot->pushArrow(aLeft);
        nodePair = Graphic234Node::getPosition(pRoot, newRight, 1);
        GraphicArrow* aRight = new GraphicArrow(Graphic::ARROW_LINE_WIDTH_SMALL, nodePair.first, nodePair.second);
        pRoot->pushArrow(aRight);
    }

    realPush(pRoot, val, ALOG);
}

void Graphic234Tree::showEdgeOfTree(Graphic234Node* pRoot, ListOfOperationsGroups* ALOG) {
    for (int i = 0; i < pRoot->getNumChild(); ++i) {
        ALOG->animateFadeIn(pRoot->getArrow(i));
        ALOG->animateSlideIn(pRoot->getArrow(i));
        showEdgeOfTree(pRoot->getChild(i), ALOG);
    }
}

void Graphic234Tree::showEdgeOfTree(ListOfOperationsGroups* ALOG) {
    if (pRoot == nullptr) {
        return;
    }
    showEdgeOfTree(pRoot, ALOG);
}

ExitStatus Graphic234Tree::initialize(int initSize, ListOfOperationsGroups* ALOG) { // Randomly initialize 
    if (initSize < 0 || initSize > Core::MAX_NUM_234_ELM) {
        return ExitMess::FAIL_234_SIZE_OOB;
    }
    std::vector<int> vals;
    for (int i = Core::NODE_MIN_VALUE; i <= Core::NODE_MAX_VALUE; ++i) {
        vals.push_back(i);
    }
    std::random_shuffle(vals.begin(), vals.end());
    vals.resize(initSize);
    return initialize(vals, ALOG);
}

ExitStatus Graphic234Tree::initialize(std::vector<int> vals, ListOfOperationsGroups* ALOG) { // Initialize with given values
    if ((int)vals.size() > Core::MAX_NUM_234_ELM) {
        return ExitMess::FAIL_234_SIZE_OOB;
    }
    for (int i = 0; i < (int)vals.size(); ++i) {
        if (vals[i] < Core::NODE_MIN_VALUE || vals[i] > Core::NODE_MAX_VALUE) {
            return ExitMess::FAIL_VALUE_OOB;
        }
    }

    ALOG->clearGroup();
    ALOG->resetCode();
    destroy();

    ALOG->addNewGroup();
    if (!vals.empty()) {
        for (int i = 0; i < (int)vals.size(); ++i) {
            realPush(vals[i], ALOG);
        }
    }
    balanceTreeLayout(ALOG);

    ALOG->addNewGroup();
    showEdgeOfTree(ALOG);

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus Graphic234Tree::initialize(std::string strVals, ListOfOperationsGroups* ALOG) { // Initialize with given values
    ExitStatus status;
    std::vector<int> vals;
    status = User::input2vector(strVals, vals, Valid::DIGIT + " ,\r\n");
    if (!status.success) {
        return status;
    }
    return initialize(vals, ALOG);
}

void Graphic234Tree::applyTransToAllNodes(Graphic234Node* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    pRoot->applyTrans();
    assert(pRoot->getNumArrow() == pRoot->getNumChild());
    for (int i = 0; i < pRoot->getNumArrow(); ++i) {
        pRoot->getArrow(i)->applyTransAB();
        applyTransToAllNodes(pRoot->getChild(i));
    }
}

void Graphic234Tree::applyTransToAllNodes() {
    applyTransToAllNodes(pRoot);
}

void Graphic234Tree::buildTransOfSubTree(Graphic234Node* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    for (int i = 0; i < pRoot->getNumChild(); ++i) {
        buildTransOfSubTree(pRoot->getChild(i));
    }
    pRoot->solveChildCollision();
    pRoot->upateDimens();
    if (pRoot == this->pRoot) {
        pRoot->updateTransFromPos(Vector2{(float)Graphic::T234_ORG_X, (float)Graphic::T234_ORG_Y});
    }
}

void Graphic234Tree::buildTransOfAllNodes(Graphic234Node* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    for (int i = 0; i < pRoot->getNumChild(); ++i) {
        pRoot->getChild(i)->addTrans(pRoot->getTrans());
        pRoot->getArrow(i)->updateTransFromPos(Graphic234Node::getPosition(pRoot, pRoot->getChild(i), i));
        buildTransOfAllNodes(pRoot->getChild(i));
    }
}

void Graphic234Tree::buildTransOfTree() {
    buildTransOfSubTree(pRoot);
    buildTransOfAllNodes(pRoot);
}

void Graphic234Tree::animateTransformAllNodes(Graphic234Node* pRoot, ListOfOperationsGroups* ALOG) {
    if (pRoot == nullptr) {
        return;
    }
    if (pRoot->isTrans()) {
        ALOG->animateTransform(pRoot, pRoot->getCurPos().x, pRoot->getCurPos().y, pRoot->getTrans().x, pRoot->getTrans().y);
    }
    for (int i = 0; i < pRoot->getNumVals(); ++i) {
        if (pRoot->getVal(i)->isTrans()) {
            ALOG->animateTransform(pRoot->getVal(i), pRoot->getVal(i)->getCurPos().x, pRoot->getVal(i)->getCurPos().y, pRoot->getVal(i)->getTrans().x, pRoot->getVal(i)->getTrans().y);
        }
    }
    for (int i = 0; i < pRoot->getNumChild(); ++i) {
        if (pRoot->getArrow(i)->isTransA()) {
            ALOG->animateTransform(&pRoot->getArrow(i)->pA, pRoot->getArrow(i)->curA.x, pRoot->getArrow(i)->curA.y, pRoot->getArrow(i)->transA.x, pRoot->getArrow(i)->transA.y);
        }
        if (pRoot->getArrow(i)->isTransB()) {
            ALOG->animateTransform(&pRoot->getArrow(i)->pB, pRoot->getArrow(i)->curB.x, pRoot->getArrow(i)->curB.y, pRoot->getArrow(i)->transB.x, pRoot->getArrow(i)->transB.y);
        }
        animateTransformAllNodes(pRoot->getChild(i), ALOG);
    }
}

void Graphic234Tree::balanceTreeLayout(ListOfOperationsGroups* ALOG) {
    applyTransToAllNodes();
    resetTransAllNodes();
    buildTransOfTree();
    animateTransformAllNodes(pRoot, ALOG);
}

void Graphic234Tree::push(Graphic234Node* pRoot, int val, ListOfOperationsGroups* ALOG) {
    if (pRoot->getNumChild() == 0) {
        for (int i = 0; i < pRoot->getNumVals(); ++i) {
            if (pRoot->getVal(i)->nVal == val) {
                return;
            }
        }
        GraphicTransNode* newNode = new GraphicTransNode(
            pRoot->getNewTransPos().x, 
            pRoot->getNewTransPos().y, 
            Graphic::NODE_SIZE_SMALL,
            Graphic::NODE_BORDER_WIDTH_SMALL, 
            true,
            Gfont::defaultFontSmall,
            val,
            ""
        );
        _size++;
        pRoot->pushVal(newNode);
        ALOG->addNewGroup();
        ALOG->animateFadeIn(newNode);
        balanceTreeLayout(ALOG);
        return;
    }
    int p = 0;
    while (p < pRoot->getNumVals() && pRoot->getVal(p)->nVal < val) {
        p++;
    }
    if (p < pRoot->getNumVals() && pRoot->getVal(p)->nVal == val) {
        return;
    }
    if (pRoot->getChild(p)->getNumVals() == 3) {
        Graphic234Node* pLeft = pRoot->getChild(p);
        Graphic234Node* pRight = new Graphic234Node(
            pRoot->getChild(p)->getNewTransPos().x,
            pRoot->getChild(p)->getNewTransPos().y
        );

        pRoot->pushVal(pLeft->getVal(1));
        pRoot->pushChild(pRight, p+1);

        pRight->pushVal(pLeft->getVal(2));
        if (pLeft->getNumChild() > 0) {
            pRight->pushArrow(pLeft->getArrow(2));
            pRight->pushArrow(pLeft->getArrow(3));
            pRight->pushChild(pLeft->getChild(2));
            pRight->pushChild(pLeft->getChild(3));
        }

        std::pair<Vector2, Vector2> nodePair = Graphic234Node::getPosition(pRoot, pRight, p+1);
        GraphicArrow* aRight = new GraphicArrow(Graphic::ARROW_LINE_WIDTH_SMALL, nodePair.first, nodePair.second);
        pRoot->pushArrow(aRight, p+1);

        pLeft->popBackVal();
        pLeft->popBackVal();
        if (pLeft->getNumChild() > 0) {
            pLeft->popBackChild();
            pLeft->popBackChild();
            pLeft->popBackArrow();
            pLeft->popBackArrow();
        }

        ALOG->addNewGroup();
        ALOG->animateFadeIn(aRight);
        ALOG->animateSlideIn(aRight);
        balanceTreeLayout(ALOG);

        if (pRoot->getVal(p)->nVal < val) {
            p++;
        }
        if (p < pRoot->getNumVals() && pRoot->getVal(p)->nVal == val) {
            return;
        }
    }
    push(pRoot->getChild(p), val, ALOG);
}


ExitStatus Graphic234Tree::push(int val, ListOfOperationsGroups* ALOG) {
    assert(_size <= Core::MAX_NUM_234_ELM);
    if (_size == Core::MAX_NUM_234_ELM) {
        return ExitMess::FAIL_HEAP_REACH_MAX_SIZE;
    }
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }

    ALOG->clearGroup();
    ALOG->resetCode();
    reset();

    if (pRoot == nullptr) {
        pRoot = new Graphic234Node(
            Graphic::T234_ORG_X, 
            Graphic::T234_ORG_Y
        );
    }
    if (pRoot->getNumVals() == 3) {
        Graphic234Node* newLeft = new Graphic234Node(
            Graphic::T234_ORG_X,
            Graphic::T234_ORG_Y
        );
        Graphic234Node* newRight = new Graphic234Node(
            Graphic::T234_ORG_X,
            Graphic::T234_ORG_Y
        );
        newLeft->pushVal(pRoot->getVal(0));
        if (pRoot->getNumChild() > 0) {
            newLeft->pushArrow(pRoot->getArrow(0));
            newLeft->pushArrow(pRoot->getArrow(1));
            newLeft->pushChild(pRoot->getChild(0));
            newLeft->pushChild(pRoot->getChild(1));
        }

        newRight->pushVal(pRoot->getVal(2));
        if (pRoot->getNumChild() > 0) {
            newRight->pushArrow(pRoot->getArrow(2));
            newRight->pushArrow(pRoot->getArrow(3));
            newRight->pushChild(pRoot->getChild(2));
            newRight->pushChild(pRoot->getChild(3));
        }

        pRoot->clearArrows();
        pRoot->clearChild();
        pRoot->keepMiddle();
        pRoot->pushChild(newLeft);
        pRoot->pushChild(newRight);
        std::pair<Vector2, Vector2> nodePair = Graphic234Node::getPosition(pRoot, newLeft, 0);
        GraphicArrow* aLeft = new GraphicArrow(Graphic::ARROW_LINE_WIDTH_SMALL, nodePair.first, nodePair.second);
        pRoot->pushArrow(aLeft);
        nodePair = Graphic234Node::getPosition(pRoot, newRight, 1);
        GraphicArrow* aRight = new GraphicArrow(Graphic::ARROW_LINE_WIDTH_SMALL, nodePair.first, nodePair.second);
        pRoot->pushArrow(aRight);

        ALOG->addNewGroup();
        ALOG->animateFadeIn(aLeft);
        ALOG->animateSlideIn(aLeft);
        ALOG->animateFadeIn(aRight);
        ALOG->animateSlideIn(aRight);
        balanceTreeLayout(ALOG);
    }

    push(pRoot, val, ALOG);
    ALOG->addNewGroup();

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus Graphic234Tree::remove(int val, ListOfOperationsGroups* ALOG) {
    

    // ALOG->build();

    return ExitMess::SUCCESS;
}

void Graphic234Tree::draw(Graphic234Node* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    pRoot->draw();
    for (int i = 0; i < pRoot->getNumChild(); ++i) {
        draw(pRoot->getChild(i));
    }
}

void Graphic234Tree::draw() {
    draw(pRoot);
    for (GraphicTransNode* pNode : nodes) {
        pNode->draw();
    }
    for (Graphic234Node* pNode : nodes234) {
        pNode->draw();
    }
}


void Graphic234Tree::clearSaparated() {
    for (GraphicTransNode* node : nodes) {
        delete node;
    }
    for (Graphic234Node* node : nodes234) {
        delete node;
    }
    nodes.clear();
    nodes234.clear();
}

void Graphic234Tree::reset() {
    clearSaparated();
    resetColorAllNodes();
    resetTransAllNodes();
    resetCurPosAllNodes();
}

void Graphic234Tree::destroy(Graphic234Node* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    for (int i = 0; i < pRoot->getNumChild(); ++i) {
        destroy(pRoot->getChild(i));
    }
    delete pRoot;
}


void Graphic234Tree::destroy() {
    reset();
    destroy(pRoot);
    _size = 0;
    pRoot = nullptr;   
}
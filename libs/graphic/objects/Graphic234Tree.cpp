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
                ALOG->addNewGroup();
                ALOG->backGroup()->setHighlightLines({1});
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
        ALOG->backGroup()->setHighlightLines({2,3});
        ALOG->animateFadeIn(newNode);
        ALOG->animateNodeFromNormalToIter(newNode);
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

        GraphicTransNode* midNode = pLeft->getVal(1);

        pRoot->pushVal(midNode);
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
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateNodeFromNormalToIter(midNode);
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

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({5});
    for (int i = 0; i < pRoot->getNumVals(); ++i) {
        ALOG->animateNodeFromIterToNearIter(pRoot->getVal(i));
    }
    for (int i = 0; i < pRoot->getChild(p)->getNumVals(); ++i) {
        ALOG->animateNodeFromNormalToIter(pRoot->getChild(p)->getVal(i));
    }
    ALOG->animateArrowSlideFromNormalToIter(pRoot->getArrow(p));
    ALOG->animateSlideColorIn(pRoot->getArrow(p));

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
    ALOG->loadCode(CPath::T234_PUSH);
    reset();

    if (pRoot == nullptr) {
        pRoot = new Graphic234Node(
            Graphic::T234_ORG_X, 
            Graphic::T234_ORG_Y
        );
    } else {
        ALOG->addNewGroup();
        for (int i = 0; i < pRoot->getNumVals(); ++i) {
            ALOG->animateNodeFromNormalToIter(pRoot->getVal(i));
        }
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
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateNodeFromIterToNormal(newLeft->getVal(0));
        ALOG->animateNodeFromIterToNormal(newRight->getVal(0));
        ALOG->animateFadeIn(aLeft);
        ALOG->animateSlideIn(aLeft);
        ALOG->animateFadeIn(aRight);
        ALOG->animateSlideIn(aRight);
        balanceTreeLayout(ALOG);
    }

    push(pRoot, val, ALOG);

    ALOG->build();

    return ExitMess::SUCCESS;
}

void Graphic234Tree::search(Graphic234Node* pRoot, int val, ListOfOperationsGroups* ALOG) {
    for (int i = 0; i < pRoot->getNumVals(); ++i) {
        ALOG->animateNodeFromNormalToIter(pRoot->getVal(i));
    }
    int p = 0;
    while (p < pRoot->getNumVals() && val > pRoot->getVal(p)->nVal) {
        p++;
    }
    if (p < pRoot->getNumVals() && val == pRoot->getVal(p)->nVal) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({0});
        ALOG->animateNodeFromIterToFocus(pRoot->getVal(p));
    } else {
        ALOG->addNewGroup();
        for (int i = 0; i < pRoot->getNumVals(); ++i) {
            ALOG->animateNodeFromIterToNearIter(pRoot->getVal(i));
        }
        if (pRoot->getNumChild() == 0) {
            ALOG->backGroup()->setHighlightLines({1});
        } else {
            ALOG->backGroup()->setHighlightLines({3});
            for (int i = 0; i < pRoot->getChild(p)->getNumVals(); ++i) {
                ALOG->animateNodeFromIterToNearIter(pRoot->getChild(p)->getVal(i));
            } 
            ALOG->animateArrowSlideFromNormalToIter(pRoot->getArrow(p));
            ALOG->animateSlideColorIn(pRoot->getArrow(p));
            search(pRoot->getChild(p), val, ALOG);
        }
    }
}


ExitStatus Graphic234Tree::search(int val, ListOfOperationsGroups* ALOG) {
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::T234_SEARCH);
    reset();
    
    ALOG->addNewGroup();
    search(pRoot, val, ALOG);

    return ExitMess::SUCCESS;
}

int Graphic234Tree::getMostLeft(Graphic234Node* pRoot) {
    if (pRoot->getNumChild() == 0) {
        return pRoot->getVal(0)->nVal;
    }
    return getMostLeft(pRoot->getChild(0));
}

int Graphic234Tree::getMostRight(Graphic234Node* pRoot) {
    if (pRoot->getNumChild() == 0) {
        return pRoot->getVal(pRoot->getNumVals()-1)->nVal;
    }
    return getMostRight(pRoot->getChild(pRoot->getNumChild()-1));
}

void Graphic234Tree::remove(Graphic234Node* pRoot, int val, ListOfOperationsGroups* ALOG) {
    int p = 0;
    while (p < pRoot->getNumVals() && val > pRoot->getVal(p)->nVal) {
        p++;
    }
    for (int i = 0; i < pRoot->getNumVals(); ++i) {
        ALOG->animateNodeFromNormalToIter(pRoot->getVal(i));
    }
    if (p < pRoot->getNumVals() && val == pRoot->getVal(p)->nVal) {
        if (pRoot->getNumChild() == 0) {
            if (pRoot == this->pRoot) {
                nodes.push_back(pRoot->getVal(p));
                pRoot->popVal(p);
                if (pRoot->getNumVals() == 0) {
                    delete pRoot;
                    this->pRoot = nullptr;
                }
                ALOG->addNewGroup();
                ALOG->backGroup()->setHighlightLines({0,1});
                ALOG->animateFadeOut(nodes.back());
                balanceTreeLayout(ALOG);
            } else if (pRoot->getNumVals() > 1) {
                nodes.push_back(pRoot->getVal(p));
                pRoot->popVal(p);
                ALOG->addNewGroup();
                ALOG->backGroup()->setHighlightLines({0,1});
                ALOG->animateFadeOut(nodes.back());
                balanceTreeLayout(ALOG);
            } 
            _size--;
        } else {
            if (pRoot->getChild(p)->getNumVals() > 1) {
                Graphic234Node* leftChild = pRoot->getChild(p);
                int newVal = getMostRight(leftChild);
                // int newVal = leftChild->getVal(leftChild->getNumVals()-1)->nVal;
                ALOG->addNewGroup();
                ALOG->backGroup()->setHighlightLines({4});
                ALOG->animateAssignValue(pRoot->getVal(p), val, newVal);

                ALOG->addNewGroup();
                ALOG->backGroup()->setHighlightLines({5});
                for (int i = 0; i < pRoot->getNumVals(); ++i) {
                    ALOG->animateNodeFromIterToNearIter(pRoot->getVal(i));
                }
                ALOG->animateArrowSlideFromNormalToIter(pRoot->getArrow(p));
                ALOG->animateSlideColorIn(pRoot->getArrow(p));

                remove(leftChild, newVal, ALOG);

                for (int i = 0; i < pRoot->getNumVals(); ++i) {
                    ALOG->animateNodeFromNearIterToIter(pRoot->getVal(i));
                }
                ALOG->animateArrowSlideFromIterToNormal(pRoot->getArrow(p));
                ALOG->animateSlideColorOut(pRoot->getArrow(p));
            } else if (pRoot->getChild(p+1)->getNumVals() > 1) {
                Graphic234Node* rightChild = pRoot->getChild(p+1);
                int newVal = getMostLeft(rightChild);
                // int newVal = rightChild->getVal(0)->nVal;
                ALOG->addNewGroup();
                ALOG->backGroup()->setHighlightLines({4});
                ALOG->animateAssignValue(pRoot->getVal(p), val, newVal);

                ALOG->addNewGroup();
                ALOG->backGroup()->setHighlightLines({5});
                for (int i = 0; i < pRoot->getNumVals(); ++i) {
                    ALOG->animateNodeFromIterToNearIter(pRoot->getVal(i));
                }
                ALOG->animateArrowSlideFromNormalToIter(pRoot->getArrow(p+1));
                ALOG->animateSlideColorIn(pRoot->getArrow(p+1));

                remove(rightChild, newVal, ALOG);

                for (int i = 0; i < pRoot->getNumVals(); ++i) {
                    ALOG->animateNodeFromNearIterToIter(pRoot->getVal(i));
                }
                ALOG->animateArrowSlideFromIterToNormal(pRoot->getArrow(p+1));
                ALOG->animateSlideColorOut(pRoot->getArrow(p+1));
            } else {
                Graphic234Node* leftChild = pRoot->getChild(p);
                Graphic234Node* rightChild = pRoot->getChild(p+1);
                GraphicTransNode* midVal = pRoot->getVal(p);
                leftChild->pushVal(pRoot->getVal(p));
                leftChild->pushVal(rightChild->getVal(0));
                pRoot->popVal(p);
                rightChild->popBackVal();

                if (leftChild->getNumChild() > 0) {
                    leftChild->pushArrow(rightChild->getArrow(0));
                    leftChild->pushArrow(rightChild->getArrow(1));
                    leftChild->pushChild(rightChild->getChild(0));
                    leftChild->pushChild(rightChild->getChild(1));

                    rightChild->popBackArrow();
                    rightChild->popBackArrow();
                    rightChild->popBackChild();
                    rightChild->popBackChild();
                }

                arrows.push_back(pRoot->getArrow(p+1));
                pRoot->popArrow(p+1);
                pRoot->popChild(p+1);
                delete rightChild;

                ALOG->addNewGroup();
                ALOG->backGroup()->setHighlightLines({7});
                ALOG->animateNodeFromIterToNormal(midVal);
                ALOG->animateSlideOut(arrows.back());
                if (pRoot == this->pRoot && pRoot->getNumVals() == 0) {
                    ALOG->backGroup()->setHighlightLines({7,8});
                    arrows.push_back(pRoot->getArrow(0));
                    pRoot->popBackArrow();
                    ALOG->animateSlideOut(arrows.back());

                    this->pRoot = leftChild;
                    delete pRoot;
                }
                balanceTreeLayout(ALOG);

                if (this->pRoot != leftChild) {
                    ALOG->addNewGroup();
                    ALOG->backGroup()->setHighlightLines({8});
                    for (int i = 0; i < pRoot->getNumVals(); ++i) {
                        ALOG->animateNodeFromIterToNearIter(pRoot->getVal(i));
                    }
                    ALOG->animateArrowSlideFromNormalToIter(pRoot->getArrow(p));
                    ALOG->animateSlideColorIn(pRoot->getArrow(p));
                }

                remove(leftChild, val, ALOG);

                if (this->pRoot != leftChild) {
                    for (int i = 0; i < pRoot->getNumVals(); ++i) {
                        ALOG->animateNodeFromNearIterToIter(pRoot->getVal(i));
                    }
                    ALOG->animateArrowSlideFromIterToNormal(pRoot->getArrow(p));
                    ALOG->animateSlideColorOut(pRoot->getArrow(p));
                }
            }
        }
    } else if (pRoot->getNumChild() > 0) {
        Graphic234Node* pChild = pRoot->getChild(p);
        if (pChild->getNumVals() == 1) {
            if (p > 0 && pRoot->getChild(p-1)->getNumVals() > 1) {
                Graphic234Node* leftSibling = pRoot->getChild(p-1);

                GraphicTransNode* tmpVal_pRoot = pRoot->getVal(p-1);
                GraphicTransNode* tmpVal_leftSibling = leftSibling->getVal(leftSibling->getNumVals()-1);

                pChild->pushVal(pRoot->getVal(p-1));
                pRoot->popVal(p-1);
                pRoot->pushVal(leftSibling->getVal(leftSibling->getNumVals()-1));
                leftSibling->popBackVal();

                if (pChild->getNumChild() > 0) {
                    pChild->pushArrow(leftSibling->getArrow(leftSibling->getNumArrow()-1), 0);
                    leftSibling->popBackArrow();
                    pChild->pushChild(leftSibling->getChild(leftSibling->getNumChild()-1), 0);
                    leftSibling->popBackChild();
                }

                ALOG->addNewGroup();
                ALOG->backGroup()->setHighlightLines({11});
                ALOG->animateNodeFromIterToNormal(tmpVal_pRoot);
                ALOG->animateNodeFromNormalToIter(tmpVal_leftSibling);
                balanceTreeLayout(ALOG);
            } else if (p < pRoot->getNumChild()-1 && pRoot->getChild(p+1)->getNumVals() > 1) {
                Graphic234Node* rightSibling = pRoot->getChild(p+1);

                GraphicTransNode* tmpVal_pRoot = pRoot->getVal(p);
                GraphicTransNode* tmpVal_rightSibling = rightSibling->getVal(0);

                pChild->pushVal(pRoot->getVal(p));
                pRoot->popVal(p);
                pRoot->pushVal(rightSibling->getVal(0));
                rightSibling->popVal(0);

                if (pChild->getNumChild() > 0) {
                    pChild->pushArrow(rightSibling->getArrow(0));
                    rightSibling->popArrow(0);
                    pChild->pushChild(rightSibling->getChild(0));
                    rightSibling->popChild(0);
                }

                ALOG->addNewGroup();
                ALOG->backGroup()->setHighlightLines({11});
                ALOG->animateNodeFromIterToNormal(tmpVal_pRoot);
                ALOG->animateNodeFromNormalToIter(tmpVal_rightSibling);
                balanceTreeLayout(ALOG);
            } else if (p > 0) {
                Graphic234Node* leftSibling = pRoot->getChild(p-1);

                GraphicTransNode* tmpVal_pRoot = pRoot->getVal(p-1);

                pChild->pushVal(pRoot->getVal(p-1));
                pChild->pushVal(leftSibling->getVal(0));
                pRoot->popVal(p-1);
                leftSibling->popVal(0);

                if (pChild->getNumChild() > 0) {
                    pChild->pushArrow(leftSibling->getArrow(1), 0);
                    pChild->pushArrow(leftSibling->getArrow(0), 0);
                    pChild->pushChild(leftSibling->getChild(1), 0);
                    pChild->pushChild(leftSibling->getChild(0), 0);

                    leftSibling->popBackArrow();
                    leftSibling->popBackArrow();
                    leftSibling->popBackChild();
                    leftSibling->popBackChild();
                }

                arrows.push_back(pRoot->getArrow(p-1));
                pRoot->popArrow(p-1);
                pRoot->popChild(p-1);
                delete leftSibling;

                ALOG->addNewGroup();
                ALOG->backGroup()->setHighlightLines({12});
                ALOG->animateNodeFromIterToNormal(tmpVal_pRoot);
                ALOG->animateSlideOut(arrows.back());
                if (pRoot == this->pRoot && pRoot->getNumVals() == 0) {
                    arrows.push_back(pRoot->getArrow(0));
                    pRoot->popBackArrow();
                    ALOG->animateSlideOut(arrows.back());

                    this->pRoot = pChild;
                    delete pRoot;
                }
                balanceTreeLayout(ALOG);

                p--;
            } else {
                Graphic234Node* rightSibling = pRoot->getChild(p+1);

                GraphicTransNode* tmpVal_pRoot = pRoot->getVal(p);

                pChild->pushVal(pRoot->getVal(p));
                pChild->pushVal(rightSibling->getVal(0));
                pRoot->popVal(p);
                rightSibling->popVal(0);

                if (pChild->getNumChild() > 0) {
                    pChild->pushArrow(rightSibling->getArrow(0));
                    pChild->pushArrow(rightSibling->getArrow(1));
                    pChild->pushChild(rightSibling->getChild(0));
                    pChild->pushChild(rightSibling->getChild(1));

                    rightSibling->popBackArrow();
                    rightSibling->popBackArrow();
                    rightSibling->popBackChild();
                    rightSibling->popBackChild();
                }

                arrows.push_back(pRoot->getArrow(p+1));
                pRoot->popArrow(p+1);
                pRoot->popChild(p+1);
                delete rightSibling;

                ALOG->addNewGroup();
                ALOG->backGroup()->setHighlightLines({12});
                ALOG->animateNodeFromIterToNormal(tmpVal_pRoot);
                ALOG->animateSlideOut(arrows.back());
                if (pRoot == this->pRoot && pRoot->getNumVals() == 0) {
                    arrows.push_back(pRoot->getArrow(0));
                    pRoot->popBackArrow();
                    ALOG->animateSlideOut(arrows.back());

                    this->pRoot = pChild;
                    delete pRoot;
                }
                balanceTreeLayout(ALOG);
            }
        }

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({13});
        if (this->pRoot != pChild) {
            for (int i = 0; i < pRoot->getNumVals(); ++i) {
                ALOG->animateNodeFromIterToNearIter(pRoot->getVal(i));
            }
            ALOG->animateArrowSlideFromNormalToIter(pRoot->getArrow(p));
            ALOG->animateSlideColorIn(pRoot->getArrow(p));
        }

        remove(pChild, val, ALOG);

        if (this->pRoot != pChild) {
            for (int i = 0; i < pRoot->getNumVals(); ++i) {
                ALOG->animateNodeFromNearIterToIter(pRoot->getVal(i));
            }
            ALOG->animateArrowSlideFromIterToNormal(pRoot->getArrow(p));
            ALOG->animateSlideColorOut(pRoot->getArrow(p));
        }
    }

    ALOG->addNewGroup();
    for (int i = 0; i < pRoot->getNumVals(); ++i) {
        ALOG->animateNodeFromIterToNormal(pRoot->getVal(i));
    }
}

ExitStatus Graphic234Tree::remove(int val, ListOfOperationsGroups* ALOG) {
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::T234_REMOVE);
    reset();

    if (pRoot == nullptr) {
        ALOG->addNewGroup();
        return ExitMess::SUCCESS;
    }

    assert(pRoot->getNumVals() > 0);

    ALOG->addNewGroup();
    remove(pRoot, val, ALOG);

    ALOG->build();

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
    for (GraphicArrow* arrow : arrows) {
        arrow->draw();
    }
    draw(pRoot);
    for (GraphicTransNode* pNode : nodes) {
        pNode->draw();
    }
}


void Graphic234Tree::clearSaparated() {
    for (GraphicTransNode* node : nodes) {
        delete node;
    }
    nodes.clear();
}

void Graphic234Tree::clearArrows() {
    for (GraphicArrow* arrow : arrows) {
        delete arrow;
    }
    arrows.clear();
}

void Graphic234Tree::reset() {
    clearSaparated();
    clearArrows();
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
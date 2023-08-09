#include "GraphicAVLTree.h"

void GraphicAVLTree::resetColorAllNodes(GraphicBinaryTreeNode* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    pRoot->resetColor();
    pRoot->getLeftArrow()->resetColor();
    pRoot->getRightArrow()->resetColor();
    resetColorAllNodes(pRoot->getLeft());
    resetColorAllNodes(pRoot->getRight());
}


void GraphicAVLTree::resetColorAllNodes() {
    resetColorAllNodes(pRoot);
}

void GraphicAVLTree::resetTransAllNodes(GraphicBinaryTreeNode* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    pRoot->resetTrans();
    pRoot->getLeftArrow()->resetTrans();
    pRoot->getRightArrow()->resetTrans();
    resetTransAllNodes(pRoot->getLeft());
    resetTransAllNodes(pRoot->getRight());
}

void GraphicAVLTree::resetTransAllNodes() {
    resetTransAllNodes(pRoot);
}

void GraphicAVLTree::resetCurPosAllNodes(GraphicBinaryTreeNode* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    pRoot->resetCurPos();
    pRoot->getLeftArrow()->resetCurAB();
    pRoot->getRightArrow()->resetCurAB();
    resetCurPosAllNodes(pRoot->getLeft());
    resetCurPosAllNodes(pRoot->getRight());
}

void GraphicAVLTree::resetCurPosAllNodes() {
    resetCurPosAllNodes(pRoot);
}

GraphicAVLTree::GraphicAVLTree() {
    pRoot = nullptr;
    _size = 0;
}

GraphicBinaryTreeNode* GraphicAVLTree::realRotateLeft(GraphicBinaryTreeNode* pNode) {
    GraphicBinaryTreeNode* pRight = pNode->getRight();
    GraphicBinaryTreeNode* pLeftOfRight = pRight->getLeft();
    pRight->setLeft(pNode);
    pNode->setRight(pLeftOfRight);
    updateHeight(pNode);
    updateHeight(pRight);
    return pRight;
}

GraphicBinaryTreeNode* GraphicAVLTree::realRotateRight(GraphicBinaryTreeNode* pNode) {
    GraphicBinaryTreeNode* pLeft = pNode->getLeft();
    GraphicBinaryTreeNode* pRightOfLeft = pLeft->getRight();
    pLeft->setRight(pNode);
    pNode->setLeft(pRightOfLeft);
    updateHeight(pNode);
    updateHeight(pLeft);
    return pLeft;
}

GraphicBinaryTreeNode* GraphicAVLTree::realPush(GraphicBinaryTreeNode* pRoot, int val, ListOfOperationsGroups* ALOG) {
    if (pRoot->nVal == val) {
        return pRoot;
    }
    if (val < pRoot->nVal) {
        if (pRoot->getLeft() == nullptr) {
            pRoot->setLeft(new GraphicBinaryTreeNode(
                pRoot->getNewTransPos().x + pRoot->size/2 - Graphic::BST_HORIZONTAL_MARGIN - Graphic::NODE_SIZE_SMALL, 
                pRoot->getNewTransPos().y + pRoot->size + Graphic::BST_VERTICAL_MARGIN,
                // Graphic::BST_ORG_X,
                // Graphic::BST_ORG_Y,
                Graphic::NODE_SIZE_SMALL,
                Graphic::NODE_BORDER_WIDTH_SMALL, 
                false,
                Gfont::defaultFontSmall,
                val,
                ""
            ));
            _size++;
            pRoot->getLeft()->updateLevel(1);
            ALOG->animateFadeIn(pRoot->getLeft());
        } else {
            pRoot->setLeft(realPush(pRoot->getLeft(), val, ALOG));
        }
    } else {
        if (pRoot->getRight() == nullptr) {
            pRoot->setRight(new GraphicBinaryTreeNode(
                pRoot->getNewTransPos().x + pRoot->size/2 + Graphic::BST_HORIZONTAL_MARGIN, 
                pRoot->getNewTransPos().y + pRoot->size + Graphic::BST_VERTICAL_MARGIN,
                // Graphic::BST_ORG_X,
                // Graphic::BST_ORG_Y,
                Graphic::NODE_SIZE_SMALL,
                Graphic::NODE_BORDER_WIDTH_SMALL, 
                false,
                Gfont::defaultFontSmall,
                val,
                ""
            ));
            _size++;
            pRoot->getRight()->updateLevel(1);
            ALOG->animateFadeIn(pRoot->getRight());
        } else {
            pRoot->setRight(realPush(pRoot->getRight(), val, ALOG));
        }
    }

    int balanceFactor = getBalanceFactor(pRoot);
    if (balanceFactor < -1) { // Right
        if (getBalanceFactor(pRoot->getRight()) > 0) { // Left
            pRoot->setRight(realRotateRight(pRoot->getRight()));
        }
        pRoot = realRotateLeft(pRoot);
    } else if (balanceFactor > 1) { // Left
        if (getBalanceFactor(pRoot->getLeft()) < 0) { // Right
            pRoot->setLeft(realRotateLeft(pRoot->getLeft()));
        }
        pRoot = realRotateRight(pRoot);
    }
    updateHeight(pRoot);
    return pRoot;
}

void GraphicAVLTree::realPush(int val, ListOfOperationsGroups* ALOG) {
    if (pRoot == nullptr) {
        pRoot = new GraphicBinaryTreeNode(
            Graphic::BST_ORG_X, 
            Graphic::BST_ORG_Y,
            Graphic::NODE_SIZE_SMALL,
            Graphic::NODE_BORDER_WIDTH_SMALL, 
            false,
            Gfont::defaultFontSmall,
            val,
            ""
        );
        pRoot->updateLevel(1);
        ALOG->animateFadeIn(pRoot);
    } else {
        pRoot = realPush(pRoot, val, ALOG);
    }
}

void GraphicAVLTree::showEdgeOfTree(GraphicBinaryTreeNode* pRoot, ListOfOperationsGroups* ALOG) {
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

void GraphicAVLTree::showEdgeOfTree(ListOfOperationsGroups* ALOG) {
    if (pRoot == nullptr) {
        return;
    }
    showEdgeOfTree(pRoot, ALOG);
}

ExitStatus GraphicAVLTree::initialize(int initSize, ListOfOperationsGroups* ALOG) { // Randomly initialize 
    if (initSize < 0 || initSize > Core::MAX_NUM_AVL_ELM) {
        return ExitMess::FAIL_AVL_SIZE_OOB;
    }
    std::vector<int> vals;
    for (int i = Core::NODE_MIN_VALUE; i <= Core::NODE_MAX_VALUE; ++i) {
        vals.push_back(i);
    }
    std::random_shuffle(vals.begin(), vals.end());
    vals.resize(initSize);
    return initialize(vals, ALOG);
}

ExitStatus GraphicAVLTree::initialize(std::vector<int> vals, ListOfOperationsGroups* ALOG) { // Initialize with given values
    if ((int)vals.size() > Core::MAX_NUM_AVL_ELM) {
        return ExitMess::FAIL_AVL_SIZE_OOB;
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
        ALOG->addNewGroup();
        for (int i = 0; i < (int)vals.size(); ++i) {
            realPush(vals[i], ALOG);
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

ExitStatus GraphicAVLTree::initialize(std::string strVals, ListOfOperationsGroups* ALOG) { // Initialize with given values
    ExitStatus status;
    std::vector<int> vals;
    status = User::input2vector(strVals, vals, Valid::DIGIT + " ,\r\n");
    if (!status.success) {
        return status;
    }
    return initialize(vals, ALOG);
}

void GraphicAVLTree::applyTransToAllNodes(GraphicBinaryTreeNode* pRoot) {
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

void GraphicAVLTree::applyTransToAllNodes() {
    applyTransToAllNodes(pRoot);
}

void GraphicAVLTree::buildTransOfSubTree(GraphicBinaryTreeNode* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    buildTransOfSubTree(pRoot->getLeft());
    buildTransOfSubTree(pRoot->getRight());
    pRoot->solveLeftCollision();
    pRoot->solveRightCollision();
    pRoot->upateDimens();
    if (pRoot == this->pRoot) {
        pRoot->updateTransFromPos(Vector2{(float)Graphic::BST_ORG_X, (float)Graphic::BST_ORG_Y});
    }
}

void GraphicAVLTree::buildTransOfAllNodes(GraphicBinaryTreeNode* pRoot) {
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

void GraphicAVLTree::buildTransOfTree() {
    buildTransOfSubTree(pRoot);
    buildTransOfAllNodes(pRoot);
}

void GraphicAVLTree::animateTransformAllNodes(GraphicBinaryTreeNode* pRoot, ListOfOperationsGroups* ALOG) {
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

void GraphicAVLTree::balanceTreeLayout(ListOfOperationsGroups* ALOG) {
    applyTransToAllNodes();
    resetTransAllNodes();
    buildTransOfTree();
    animateTransformAllNodes(pRoot, ALOG);
}


int GraphicAVLTree::getHeight(GraphicBinaryTreeNode* pNode) {
    return pNode == nullptr ? 0 : pNode->getLevel();
}

int GraphicAVLTree::getBalanceFactor(GraphicBinaryTreeNode* pNode) {
    return pNode == nullptr ? 0 : getHeight(pNode->getLeft()) - getHeight(pNode->getRight());
}

void GraphicAVLTree::updateHeight(GraphicBinaryTreeNode* pNode) {
    pNode->updateLevel(std::max(getHeight(pNode->getLeft()), getHeight(pNode->getRight())) + 1);
}

GraphicBinaryTreeNode* GraphicAVLTree::rotateLeft(GraphicBinaryTreeNode* pNode, ListOfOperationsGroups* ALOG) {
    GraphicBinaryTreeNode* pRight = pNode->getRight();
    GraphicBinaryTreeNode* pLeftOfRight = pRight->getLeft();
    pRight->setLeft(pNode);
    pNode->setRight(pLeftOfRight);
    updateHeight(pNode);
    updateHeight(pRight);

    if (pLeftOfRight == nullptr) {
        ALOG->animateFadeOut(pNode->getRightArrow());
        ALOG->animateSlideOut(pNode->getRightArrow());
        ALOG->animateFadeIn(pRight->getLeftArrow());
        ALOG->animateSlideIn(pRight->getLeftArrow());
    } 

    return pRight;
}

GraphicBinaryTreeNode* GraphicAVLTree::rotateRight(GraphicBinaryTreeNode* pNode, ListOfOperationsGroups* ALOG) {
    GraphicBinaryTreeNode* pLeft = pNode->getLeft();
    GraphicBinaryTreeNode* pRightOfLeft = pLeft->getRight();
    pLeft->setRight(pNode);
    pNode->setLeft(pRightOfLeft);
    updateHeight(pNode);
    updateHeight(pLeft);

    if (pRightOfLeft == nullptr) {
        ALOG->animateFadeOut(pNode->getLeftArrow());
        ALOG->animateSlideOut(pNode->getLeftArrow());
        ALOG->animateFadeIn(pLeft->getRightArrow());
        ALOG->animateSlideIn(pLeft->getRightArrow());
    } 

    return pLeft;
}

void GraphicAVLTree::checkAndRebalanceTreeFactor(GraphicBinaryTreeNode*& pRoot, ListOfOperationsGroups* ALOG) {
    int balanceFactor = getBalanceFactor(pRoot);
    if (balanceFactor < -1) { // Right
        if (getBalanceFactor(pRoot->getRight()) > 0) { // Left
            ALOG->addNewGroup();
            pRoot->setRight(rotateRight(pRoot->getRight(), ALOG));
            balanceTreeLayout(ALOG);
        }
        ALOG->addNewGroup();
        GraphicBinaryTreeNode* tmp = rotateLeft(pRoot, ALOG);
        ALOG->animateNodeFromIterToNormal(pRoot);
        ALOG->animateNodeFromNormalToIter(tmp);
        pRoot = tmp;
    } else if (balanceFactor > 1) {
        if (getBalanceFactor(pRoot->getLeft()) < 0) { // Right
            ALOG->addNewGroup();
            pRoot->setLeft(rotateLeft(pRoot->getLeft(), ALOG));
            balanceTreeLayout(ALOG);
        }
        ALOG->addNewGroup();
        GraphicBinaryTreeNode* tmp = rotateRight(pRoot, ALOG);
        ALOG->animateNodeFromIterToNormal(pRoot);
        ALOG->animateNodeFromNormalToIter(tmp);
        pRoot = tmp;
    }
    updateHeight(pRoot);
}

GraphicBinaryTreeNode* GraphicAVLTree::push(GraphicBinaryTreeNode* pRoot, int val, ListOfOperationsGroups* ALOG) {
    ALOG->animateNodeFromNormalToIter(pRoot);

    if (val == pRoot->nVal) {
        return pRoot;
    }

    if (val < pRoot->nVal) {
        if (pRoot->getLeft() == nullptr) {
            GraphicBinaryTreeNode* newNode = new GraphicBinaryTreeNode(
                pRoot->getNewTransPos().x + pRoot->size/2 - Graphic::BST_HORIZONTAL_MARGIN - Graphic::NODE_SIZE_SMALL, 
                pRoot->getNewTransPos().y + pRoot->size + Graphic::BST_VERTICAL_MARGIN,
                Graphic::NODE_SIZE_SMALL,
                Graphic::NODE_BORDER_WIDTH_SMALL, 
                false,
                Gfont::defaultFontSmall,
                val,
                ""
            );
            _size++;

            newNode->updateLevel(1);
            pRoot->setLeft(newNode);

            ALOG->addNewGroup();
            ALOG->animateFadeIn(newNode);
            ALOG->animateFadeIn(pRoot->getLeftArrow());
            ALOG->animateSlideIn(pRoot->getLeftArrow());

            balanceTreeLayout(ALOG);
        } else {
            ALOG->addNewGroup();
            ALOG->animateNodeFromIterToNearIter(pRoot);
            ALOG->animateArrowSlideFromNormalToIter(pRoot->getLeftArrow());
            ALOG->animateSlideColorIn(pRoot->getLeftArrow());

            pRoot->setLeft(push(pRoot->getLeft(), val, ALOG));
            balanceTreeLayout(ALOG);

            ALOG->addNewGroup();
            ALOG->animateNodeFromIterToNormal(pRoot->getLeft());
            ALOG->animateNodeFromNearIterToIter(pRoot);
            ALOG->animateArrowSlideFromIterToNormal(pRoot->getLeftArrow());
            ALOG->animateSlideColorOut(pRoot->getLeftArrow());
        }
    } else {
        if (pRoot->getRight() == nullptr) {
            GraphicBinaryTreeNode* newNode = new GraphicBinaryTreeNode(
                pRoot->getNewTransPos().x + pRoot->size/2 + Graphic::BST_HORIZONTAL_MARGIN, 
                pRoot->getNewTransPos().y + pRoot->size + Graphic::BST_VERTICAL_MARGIN,
                Graphic::NODE_SIZE_SMALL,
                Graphic::NODE_BORDER_WIDTH_SMALL, 
                false,
                Gfont::defaultFontSmall,
                val,
                ""
            );
            _size++;

            newNode->updateLevel(1);
            pRoot->setRight(newNode);

            ALOG->addNewGroup();
            ALOG->animateFadeIn(newNode);
            ALOG->animateFadeIn(pRoot->getRightArrow());
            ALOG->animateSlideIn(pRoot->getRightArrow());

            balanceTreeLayout(ALOG);
        } else {
            ALOG->addNewGroup();
            ALOG->animateNodeFromIterToNearIter(pRoot);
            ALOG->animateArrowSlideFromNormalToIter(pRoot->getRightArrow());
            ALOG->animateSlideColorIn(pRoot->getRightArrow());

            pRoot->setRight(push(pRoot->getRight(), val, ALOG));
            balanceTreeLayout(ALOG);

            ALOG->addNewGroup();
            ALOG->animateNodeFromIterToNormal(pRoot->getRight());
            ALOG->animateNodeFromNearIterToIter(pRoot);
            ALOG->animateArrowSlideFromIterToNormal(pRoot->getRightArrow());
            ALOG->animateSlideColorOut(pRoot->getRightArrow());
        }
    }

    checkAndRebalanceTreeFactor(pRoot, ALOG);

    return pRoot;
}

ExitStatus GraphicAVLTree::push(int val, ListOfOperationsGroups* ALOG) {
    assert(_size <= Core::MAX_NUM_AVL_ELM);
    if (_size == Core::MAX_NUM_AVL_ELM) {
        return ExitMess::FAIL_AVL_REACH_MAX_SIZE;
    }
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }

    ALOG->clearGroup();
    ALOG->resetCode();
    reset();

    if (pRoot == nullptr) {
        pRoot = new GraphicBinaryTreeNode(
            Graphic::BST_ORG_X, 
            Graphic::BST_ORG_Y,
            Graphic::NODE_SIZE_SMALL,
            Graphic::NODE_BORDER_WIDTH_SMALL, 
            false,
            Gfont::defaultFontSmall,
            val,
            ""
        );
        pRoot->updateLevel(1);
        ALOG->addNewGroup();
        ALOG->animateFadeIn(pRoot);
        ALOG->animateNodeFromNormalToFocus(pRoot);
    } else {
        ALOG->addNewGroup();
        pRoot = push(pRoot, val, ALOG);
        balanceTreeLayout(ALOG);

        ALOG->addNewGroup();
        ALOG->animateNodeFromIterToNormal(pRoot);
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

void GraphicAVLTree::search(GraphicBinaryTreeNode* pRoot, int val, ListOfOperationsGroups* ALOG) {
    if (pRoot == nullptr) {
        ALOG->addNewGroup();
        return;
    }

    if (pRoot->nVal == val) {
        ALOG->animateNodeFromNormalToFocus(pRoot);

        ALOG->addNewGroup();
        return;
    }

    ALOG->animateNodeFromNormalToIter(pRoot);

    ALOG->addNewGroup();
    ALOG->animateNodeFromIterToNearIter(pRoot);
    if (val < pRoot->nVal) {
        if (pRoot->getLeft() != nullptr) {
            ALOG->animateArrowSlideFromNormalToIter(pRoot->getLeftArrow());
            ALOG->animateSlideColorIn(pRoot->getLeftArrow());
        }
        search(pRoot->getLeft(), val, ALOG);

        ALOG->animateNodeFromNearIterToIter(pRoot);
        if (pRoot->getLeft() != nullptr) {
            ALOG->animateArrowSlideFromIterToNormal(pRoot->getLeftArrow());
            ALOG->animateSlideColorOut(pRoot->getLeftArrow());
        }
    } else {
        if (pRoot->getRight() != nullptr) {
            ALOG->animateArrowSlideFromNormalToIter(pRoot->getRightArrow());
            ALOG->animateSlideColorIn(pRoot->getRightArrow());
        }
        search(pRoot->getRight(), val, ALOG);

        ALOG->animateNodeFromNearIterToIter(pRoot);
        if (pRoot->getRight() != nullptr) {
            ALOG->animateArrowSlideFromIterToNormal(pRoot->getRightArrow());
            ALOG->animateSlideColorOut(pRoot->getRightArrow());
        }
    }

    ALOG->addNewGroup();
    ALOG->animateNodeFromIterToNormal(pRoot);
}

ExitStatus GraphicAVLTree::search(int val, ListOfOperationsGroups* ALOG) {
    if (val < Core::NODE_MIN_VALUE || val > Core::NODE_MAX_VALUE) {
        return ExitMess::FAIL_VALUE_OOB;
    }

    ALOG->clearGroup();
    ALOG->resetCode();
    reset();

    ALOG->addNewGroup();
    search(pRoot, val, ALOG);

    ALOG->build();

    return ExitMess::SUCCESS;
}

GraphicBinaryTreeNode* GraphicAVLTree::removeAtRight(GraphicBinaryTreeNode* pRoot, int val, GraphicBinaryTreeNode* orgNode, ListOfOperationsGroups* ALOG) {
    ALOG->animateNodeFromNormalToIter(pRoot);

    if (pRoot->getLeft() == nullptr) {
        nodes.push_back(pRoot);
        ALOG->addNewGroup();
        ALOG->animateAssignValue(orgNode, orgNode->nVal, pRoot->nVal);
        ALOG->animateFadeOut(pRoot);
        if (pRoot->getRight() != nullptr) {
            ALOG->animateNodeFromNormalToIter(pRoot->getRight());
            ALOG->animateSlideOut(pRoot->getRightArrow());
        }
        return pRoot->getRight();
    } 

    ALOG->addNewGroup();

    ALOG->animateNodeFromIterToNearIter(pRoot);
    ALOG->animateSlideColorIn(pRoot->getLeftArrow());
    ALOG->animateArrowSlideFromNormalToIter(pRoot->getLeftArrow());

    pRoot->setLeft(removeAtRight(pRoot->getLeft(), val, orgNode, ALOG));
    if (pRoot->getLeft() == nullptr) {
        ALOG->animateSlideOut(pRoot->getLeftArrow());
    }
    balanceTreeLayout(ALOG);

    ALOG->addNewGroup();
    ALOG->animateNodeFromNearIterToIter(pRoot);
    if (pRoot->getLeft() != nullptr) {
        ALOG->animateNodeFromIterToNormal(pRoot->getLeft());
        ALOG->animateSlideColorOut(pRoot->getLeftArrow());
        ALOG->animateArrowSlideFromIterToNormal(pRoot->getLeftArrow());
    }

    checkAndRebalanceTreeFactor(pRoot, ALOG);

    return pRoot;
}

GraphicBinaryTreeNode* GraphicAVLTree::remove(GraphicBinaryTreeNode* pRoot, int val, ListOfOperationsGroups* ALOG) {
    if (pRoot->nVal == val) {
        ALOG->animateNodeFromNormalToRefer(pRoot);
        _size--;
        if (pRoot->getRight() == nullptr) {
            nodes.push_back(pRoot);
            ALOG->addNewGroup();
            ALOG->animateFadeOut(pRoot);
            if (pRoot->getLeft() != nullptr) {
                ALOG->animateSlideOut(pRoot->getLeftArrow());
            }

            return pRoot->getLeft();
        } else {
            ALOG->addNewGroup();
            ALOG->animateSlideColorIn(pRoot->getRightArrow());
            ALOG->animateArrowSlideFromNormalToIter(pRoot->getRightArrow());

            pRoot->setRight(removeAtRight(pRoot->getRight(), val, pRoot, ALOG));
            if (pRoot->getRight() == nullptr) {
                ALOG->animateSlideOut(pRoot->getRightArrow());
            }
            balanceTreeLayout(ALOG);

            ALOG->addNewGroup();
            ALOG->animateNodeFromReferToIter(pRoot);
            if (pRoot->getRight() != nullptr) {
                ALOG->animateNodeFromIterToNormal(pRoot->getRight());
                ALOG->animateSlideColorOut(pRoot->getRightArrow());
                ALOG->animateArrowSlideFromIterToNormal(pRoot->getRightArrow());
            }
        }
    } else {
        ALOG->animateNodeFromNormalToIter(pRoot);
        if (val < pRoot->nVal) {
            if (pRoot->getLeft() != nullptr) {
                ALOG->addNewGroup();
                ALOG->animateNodeFromIterToNearIter(pRoot);
                ALOG->animateSlideColorIn(pRoot->getLeftArrow());
                ALOG->animateArrowSlideFromNormalToIter(pRoot->getLeftArrow());

                pRoot->setLeft(remove(pRoot->getLeft(), val, ALOG));
                if (pRoot->getLeft() == nullptr) {
                    ALOG->animateSlideOut(pRoot->getLeftArrow());
                }
                balanceTreeLayout(ALOG);

                ALOG->addNewGroup();
                ALOG->animateNodeFromNearIterToIter(pRoot);
                if (pRoot->getLeft() != nullptr) {
                    ALOG->animateNodeFromIterToNormal(pRoot->getLeft());
                    ALOG->animateSlideColorOut(pRoot->getLeftArrow());
                    ALOG->animateArrowSlideFromIterToNormal(pRoot->getLeftArrow());
                }
            }
        } else {
            if (pRoot->getRight() != nullptr) {
                ALOG->addNewGroup();
                ALOG->animateNodeFromIterToNearIter(pRoot);
                ALOG->animateSlideColorIn(pRoot->getRightArrow());
                ALOG->animateArrowSlideFromNormalToIter(pRoot->getRightArrow());

                pRoot->setRight(remove(pRoot->getRight(), val, ALOG));
                if (pRoot->getRight() == nullptr) {
                    ALOG->animateSlideOut(pRoot->getRightArrow());
                }
                balanceTreeLayout(ALOG);

                ALOG->addNewGroup();
                ALOG->animateNodeFromNearIterToIter(pRoot);
                if (pRoot->getRight() != nullptr) {
                    ALOG->animateNodeFromIterToNormal(pRoot->getRight());
                    ALOG->animateSlideColorOut(pRoot->getRightArrow());
                    ALOG->animateArrowSlideFromIterToNormal(pRoot->getRightArrow());
                }
            }
        }
    }

    checkAndRebalanceTreeFactor(pRoot, ALOG);

    return pRoot;
}

ExitStatus GraphicAVLTree::remove(int val, ListOfOperationsGroups* ALOG) {

    ALOG->clearGroup();
    ALOG->resetCode();
    reset();

    if (pRoot == nullptr) {
        return ExitMess::SUCCESS;
    }

    ALOG->addNewGroup();
    pRoot = remove(pRoot, val, ALOG);
    balanceTreeLayout(ALOG);
    ALOG->addNewGroup();
    ALOG->animateNodeFromIterToNormal(pRoot);

    ALOG->build();

    return ExitMess::SUCCESS;
}


void GraphicAVLTree::draw(GraphicBinaryTreeNode* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    pRoot->draw();
    draw(pRoot->getLeft());
    draw(pRoot->getRight());
}

void GraphicAVLTree::draw() {
    draw(pRoot);
    for (GraphicBinaryTreeNode* pNode : nodes) {
        pNode->draw();
    }
}


void GraphicAVLTree::clearSaparated() {
    for (GraphicBinaryTreeNode* node : nodes) {
        delete node;
    }
    nodes.clear();
}

void GraphicAVLTree::reset() {
    clearSaparated();
    resetColorAllNodes();
    resetTransAllNodes();
    resetCurPosAllNodes();
}

void GraphicAVLTree::destroy(GraphicBinaryTreeNode* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    destroy(pRoot->getLeft());
    destroy(pRoot->getRight());
    delete pRoot;
}


void GraphicAVLTree::destroy() {
    reset();
    destroy(pRoot);
    pRoot = nullptr;
    _size = 0;
}
#include "GraphicAVLTree.h"

void GraphicAVLTree::resetColorAllNodes(GraphicBinaryTreeNode* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    pRoot->resetColor();
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

ExitStatus GraphicAVLTree::initialize(ListOfOperationsGroups* ALOG) {
    ALOG->clearGroup();
    ALOG->resetCode();

    destroy();

    ALOG->addNewGroup();
    ALOG->animateDelay();

    ALOG->build();

    return ExitMess::SUCCESS;
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
    if (pLeftOfRight == nullptr) {
        pRight->setLeft(pNode);
    } else {
        pRight->updateLeft(pNode);
    }
    pNode->updateRight(pLeftOfRight);
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
    if (pRightOfLeft == nullptr) {
        pLeft->setRight(pNode);
    } else {
        pLeft->updateRight(pNode);
    }    
    pNode->updateLeft(pRightOfLeft);
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

GraphicBinaryTreeNode* GraphicAVLTree::push(GraphicBinaryTreeNode* pRoot, int val, ListOfOperationsGroups* ALOG) {
    ALOG->animateNodeFromNormalToIter(pRoot);

    if (val == pRoot->nVal) {
        ALOG->addNewGroup();
        ALOG->animateNodeFromIterToNormal(pRoot);

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

            ALOG->animateNodeFromNormalToFocus(newNode);

            balanceTreeLayout(ALOG);
        } else {
            ALOG->addNewGroup();
            ALOG->animateNodeFromIterToNearIter(pRoot);
            ALOG->animateArrowSlideFromNormalToIter(pRoot->getLeftArrow());
            ALOG->animateSlideColorIn(pRoot->getLeftArrow());

            pRoot->updateLeft(push(pRoot->getLeft(), val, ALOG));

            balanceTreeLayout(ALOG);
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

            ALOG->animateNodeFromNormalToFocus(newNode);

            balanceTreeLayout(ALOG);
        } else {
            ALOG->addNewGroup();
            ALOG->animateNodeFromIterToNearIter(pRoot);
            ALOG->animateArrowSlideFromNormalToIter(pRoot->getRightArrow());
            ALOG->animateSlideColorIn(pRoot->getRightArrow());

            pRoot->updateRight(push(pRoot->getRight(), val, ALOG));
            
            balanceTreeLayout(ALOG);
            ALOG->animateNodeFromNearIterToIter(pRoot);
            ALOG->animateArrowSlideFromIterToNormal(pRoot->getRightArrow());
            ALOG->animateSlideColorOut(pRoot->getRightArrow());
        }
    }

    int balanceFactor = getBalanceFactor(pRoot);
    if (balanceFactor < -1) { // Right
        if (getBalanceFactor(pRoot->getRight()) > 0) { // Left
            ALOG->addNewGroup();
            pRoot->updateRight(rotateRight(pRoot->getRight(), ALOG));
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
            pRoot->updateLeft(rotateLeft(pRoot->getLeft(), ALOG));
            balanceTreeLayout(ALOG);
        }
        ALOG->addNewGroup();
        GraphicBinaryTreeNode* tmp = rotateRight(pRoot, ALOG);
        ALOG->animateNodeFromIterToNormal(pRoot);
        ALOG->animateNodeFromNormalToIter(tmp);
        pRoot = tmp;
    }
    ALOG->addNewGroup();
    ALOG->animateNodeFromIterToNormal(pRoot);
    updateHeight(pRoot);

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
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

void GraphicAVLTree::search(GraphicBinaryTreeNode* pRoot, int val, ListOfOperationsGroups* ALOG) {
    if (pRoot == nullptr) {
        return;
    }

    if (pRoot->nVal == val) {
        ALOG->animateNodeFromNormalToFocus(pRoot);
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
    } else {
        if (pRoot->getRight() != nullptr) {
            ALOG->animateArrowSlideFromNormalToIter(pRoot->getRightArrow());
            ALOG->animateSlideColorIn(pRoot->getRightArrow());
        }
        search(pRoot->getRight(), val, ALOG);
    }
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
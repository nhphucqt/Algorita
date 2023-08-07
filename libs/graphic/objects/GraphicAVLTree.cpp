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
    if (pRoot->getLeft() != nullptr) {
        pRoot->getLeft()->applyTrans();
        pRoot->getLeftArrow()->applyTransAB();
        applyTransToAllNodes(pRoot->getLeft());
    }
    if (pRoot->getRight() != nullptr) {
        pRoot->getRight()->applyTrans();
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
}

void GraphicAVLTree::buildTransOfAllNodes(GraphicBinaryTreeNode* pRoot) {

    if (pRoot == nullptr) {
        return;
    }
    // std::cerr << " >> " << pRoot->nVal << ' ' << pRoot->getTrans().x << ' ' << pRoot->getTrans().y << '\n';
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
    std::cerr << "animateTransformAllNodes - IN -- " << pRoot->nVal << '\n';
    if (pRoot->isTrans()) {
        std::cerr << " >> " << pRoot->nVal << ' ' << pRoot->getTrans().x << ' ' << pRoot->getTrans().y << '\n';
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
    std::cerr << "animateTransformAllNodes - OUT -- " << pRoot->nVal << '\n';
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

// GraphicBinaryTreeNode* GraphicAVLTree::rotateLeft(GraphicBinaryTreeNode* pNode) {
//         GraphicBinaryTreeNode* pRight = pNode->getRight();
//         GraphicBinaryTreeNode* pLeftOfRight = pRight->getLeft();
//         pRight->updateLeft(pNode);
//         pNode->updateRight(pLeftOfRight);
//         updateHeight(pNode);
//         updateHeight(pRight);

//         pRight->updateTransFromPos(pNode->getNewTransPos());
//         pRight->solveLeftCollision();
//         pRight->solveRightCollision();

//         if (pRight->getLeft() != nullptr) {
//             pRight->getLeft()->solve
//         }

//         return pRight;
//     }

// GraphicBinaryTreeNode* GraphicAVLTree::rotateRight(GraphicBinaryTreeNode* pNode) {
//     GraphicBinaryTreeNode* pLeft = pNode->getLeft();
//     GraphicBinaryTreeNode* pRightOfLeft = pLeft->getRight();
//     pLeft->updateRight(pNode);
//     pNode->updateLeft(pRightOfLeft);
//     updateHeight(pNode);
//     updateHeight(pLeft);
//     return pLeft;
// }

void GraphicAVLTree::push(GraphicBinaryTreeNode* pRoot, int val, ListOfOperationsGroups* ALOG) {
    if (pRoot == nullptr) {
        return;
    }

    if (val == pRoot->nVal) {
        ALOG->addNewGroup();
        ALOG->animateDelay();
        return;
    }

    // std::cerr << " >> " << pRoot->nVal << ' ' << pRoot->getTrans().x << ' ' << pRoot->getTrans().y << '\n';

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

            pRoot->setLeft(newNode);

            ALOG->addNewGroup();
            ALOG->animateFadeIn(newNode);
            ALOG->animateFadeIn(pRoot->getLeftArrow());
            ALOG->animateSlideIn(pRoot->getLeftArrow());
            balanceTreeLayout(ALOG);
        } else {
            push(pRoot->getLeft(), val, ALOG);
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

            pRoot->setRight(newNode);

            ALOG->addNewGroup();
            ALOG->animateFadeIn(newNode);
            ALOG->animateFadeIn(pRoot->getRightArrow());
            ALOG->animateSlideIn(pRoot->getRightArrow());
            balanceTreeLayout(ALOG);
        } else {
            push(pRoot->getRight(), val, ALOG);
        }
    }
}

ExitStatus GraphicAVLTree::push(int val, ListOfOperationsGroups* ALOG) {

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
        ALOG->addNewGroup();
        ALOG->animateFadeIn(pRoot);
    } else {
        push(pRoot, val, ALOG);
    }

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
}
#include "GraphicBinaryTreeNode.h"

float GraphicBinaryTreeNode::BinaryNodeDimens::getWidth() {
    return leftWidth + rightWidth;
}


GraphicBinaryTreeNode::GraphicBinaryTreeNode() 
: GraphicNode() {

}

GraphicBinaryTreeNode::GraphicBinaryTreeNode(float _x, float _y, float _s, float _bs, bool _sqr, Font* font, int _v, const std::string &_subtext) 
: GraphicNode(_x, _y, _s, _bs, _sqr, font, _v, _subtext) {
    curPos = Vector2{_x,_y};
    pLeft = pRight = nullptr;
    trans = Z_VECT;
    dim = BinaryNodeDimens(0.0f, size, size);
    if (isSqr) {
        outerShapeIn = std::bind(&cf::outerSqur, &size, std::placeholders::_1);
        outerShapeOut = std::bind(&cf::outerSqur, &size, std::placeholders::_1);
    } else { // circle
        outerShapeIn = std::bind(&cf::outerCirc, &size, std::placeholders::_1);
        outerShapeOut = std::bind(&cf::outerCirc, &size, std::placeholders::_1);
    }
}

GraphicBinaryTreeNode::GraphicBinaryTreeNode(float _x, float _y, float _s, bool _sqr, int _v, const std::string &_subtext) 
: GraphicBinaryTreeNode(_x, _y, _s, Graphic::NODE_BORDER_WIDTH, _sqr, Gfont::defaultFont, _v, _subtext) {}

GraphicBinaryTreeNode::GraphicBinaryTreeNode(float _x, float _y, float _s, bool _sqr, int _v)
: GraphicBinaryTreeNode(_x, _y, _s, Graphic::NODE_BORDER_WIDTH, _sqr, Gfont::defaultFont, _v, "") {}

void GraphicBinaryTreeNode::setLeft(GraphicBinaryTreeNode* pNode) {
    if (pLeft == nullptr) {
        if (pNode != nullptr) {
            std::pair<Vector2, Vector2> nodePair = getPosition(this, pNode);
            aLeft = GraphicArrow(Graphic::ARROW_LINE_WIDTH_SMALL, nodePair.first, nodePair.second);
        } else {
            aLeft = GraphicArrow();
        }
    }
    pLeft = pNode;
}

void GraphicBinaryTreeNode::setRight(GraphicBinaryTreeNode* pNode) {
    if (pRight == nullptr) {
        if (pNode != nullptr) {
            std::pair<Vector2, Vector2> nodePair = getPosition(this, pNode);
            aRight = GraphicArrow(Graphic::ARROW_LINE_WIDTH_SMALL, nodePair.first, nodePair.second);
        } else {
            aRight = GraphicArrow();
        }
    }
    pRight = pNode;
}

GraphicBinaryTreeNode* GraphicBinaryTreeNode::getLeft() {
    return pLeft;
}

GraphicBinaryTreeNode* GraphicBinaryTreeNode::getRight() {
    return pRight;
}

GraphicArrow* GraphicBinaryTreeNode::getLeftArrow() {
    return &aLeft;
}

GraphicArrow* GraphicBinaryTreeNode::getRightArrow() {
    return &aRight;
}

GraphicBinaryTreeNode::BinaryNodeDimens GraphicBinaryTreeNode::getDimens() {
    return dim;
}

void GraphicBinaryTreeNode::upateDimens() {
    if (pLeft == nullptr) {
        dim.leftWidth = 0;
    } else {
        dim.leftWidth = Graphic::BST_HORIZONTAL_MARGIN + pLeft->dim.getWidth() - size/2;
    }
    if (pRight == nullptr) {
        dim.rightWidth = size;
    } else {
        dim.rightWidth = Graphic::BST_HORIZONTAL_MARGIN + pRight->dim.getWidth() + size/2;
    }
    if (pLeft == nullptr && pRight == nullptr) {
        dim.height = size;
    } else {
        dim.height = 0;
        if (pLeft != nullptr) {
            dim.height = std::max(dim.height, pLeft->dim.height);
        }
        if (pRight != nullptr) {
            dim.height = std::max(dim.height, pRight->dim.height);
        }
    }
    assert(dim.height >= 0);
    assert(dim.leftWidth >= 0);
    assert(dim.rightWidth >= 0);
}

bool GraphicBinaryTreeNode::isColisionInLeft() {
    if (pLeft != nullptr) {
        float curX = pLeft->getNewTransPos().x + pLeft->getDimens().rightWidth;
        float limX = getNewTransPos().x + size/2 - Graphic::BST_HORIZONTAL_MARGIN;

        float curY = pLeft->getNewTransPos().y;
        float limY = getNewTransPos().y + size + Graphic::BST_VERTICAL_MARGIN;

        if (fabs(curX-limX) > Geo::EPS || fabs(curY-limY) > Geo::EPS) {
            return true;
        }
    }
    return false;
}

bool GraphicBinaryTreeNode::isColisionInRight() {
    if (pRight != nullptr) {
        float curX = pRight->getNewTransPos().x - pRight->getDimens().leftWidth;
        float limX = getNewTransPos().x + size/2 + Graphic::BST_HORIZONTAL_MARGIN;

        float curY = pRight->getNewTransPos().y;
        float limY = getNewTransPos().y + size + Graphic::BST_VERTICAL_MARGIN;

        if (fabs(curX-limX) > Geo::EPS || fabs(curY-limY) > Geo::EPS) {
            return true;
        }
    }
    return false;
}

Vector2 GraphicBinaryTreeNode::getLeftCollision() {
    float curX = pLeft->getNewTransPos().x + pLeft->getDimens().rightWidth;
    float limX = getNewTransPos().x + size/2 - Graphic::BST_HORIZONTAL_MARGIN;

    float curY = pLeft->getNewTransPos().y;
    float limY = getNewTransPos().y + size + Graphic::BST_VERTICAL_MARGIN;

    return Vector2{limX - curX, limY - curY};
}

Vector2 GraphicBinaryTreeNode::getRightCollision() {
    float curX = pRight->getNewTransPos().x - pRight->getDimens().leftWidth;
    float limX = getNewTransPos().x + size/2 + Graphic::BST_HORIZONTAL_MARGIN;

    float curY = pRight->getNewTransPos().y;
    float limY = getNewTransPos().y + size + Graphic::BST_VERTICAL_MARGIN;

    return Vector2{limX - curX, limY - curY};
}

void GraphicBinaryTreeNode::solveLeftCollision() {
    if (isColisionInLeft()) {
        pLeft->addTrans(getLeftCollision());
    }
}

void GraphicBinaryTreeNode::solveRightCollision() {
    if (isColisionInRight()) {
        pRight->addTrans(getRightCollision());
    }
}

Vector2 GraphicBinaryTreeNode::getCurPos() {
    return curPos;
}

void GraphicBinaryTreeNode::resetCurPos() {
    curPos = Vector2{x, y};
}

bool GraphicBinaryTreeNode::isTrans() {
    return fabs(trans.x) > Geo::EPS || fabs(trans.y) > Geo::EPS;
}

Vector2 GraphicBinaryTreeNode::getTrans() {
    return trans;
}

Vector2 GraphicBinaryTreeNode::getNewTransPos() {
    return curPos + trans;
}


void GraphicBinaryTreeNode::addTrans(Vector2 v) {
    trans += v;
}

void GraphicBinaryTreeNode::addTrans(float x, float y) {
    trans += Vector2{x, y};
}

void GraphicBinaryTreeNode::updateTransFromPos(Vector2 p) {
    trans = p - curPos;
}

void GraphicBinaryTreeNode::applyTrans() {
    curPos += trans;
}


void GraphicBinaryTreeNode::resetTrans() {
    trans = Z_VECT;
}

int GraphicBinaryTreeNode::getLevel() {
    return level;
}

void GraphicBinaryTreeNode::updateLevel(int newLevel) {
    level = newLevel;
}

void GraphicBinaryTreeNode::draw() {
    aLeft.draw();
    aRight.draw();
    GraphicNode::draw();
}

std::pair<Vector2, Vector2> GraphicBinaryTreeNode::getPosition(GraphicBinaryTreeNode* nodeA, GraphicBinaryTreeNode* nodeB) {
    Vector2 newA, newB;
    Vector2 cA = nodeA->getNewTransPos() + toSqrVector2(nodeA->size/2);
    Vector2 cB = nodeB->getNewTransPos() + toSqrVector2(nodeB->size/2);
    if (fabs(cA.x - cB.x) < Geo::EPS && fabs(cA.y - cB.y) < Geo::EPS) {
        return std::pair{cA, cB};
    }
    newA = cA + nodeA->outerShapeOut(cB - cA);
    newB = cB + nodeB->outerShapeIn(cA - cB);
    return std::pair{newA, newB};
}
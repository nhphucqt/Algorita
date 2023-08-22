#include "Graphic234Node.h"

Graphic234Node::Graphic234Node() {

}

Graphic234Node::Graphic234Node(float _x, float _y) {
    x = _x; y = _y;
    curPos = Vector2{_x,_y};
    trans = Z_VECT;
    dim = NodeDimens(0, 0);
}

Graphic234Node::~Graphic234Node() {
    for (auto val : pVals) {
        delete val;
    }
    for (auto arrow : aChild) {
        delete arrow;
    }
}

void Graphic234Node::pushVal(GraphicTransNode* pNode) {
    pVals.push_back(pNode);
    pVals.sort([&](GraphicTransNode* a, GraphicTransNode* b) {
        return a->nVal < b->nVal;
    });
}

void Graphic234Node::popBackVal() {
    pVals.pop_back();
}


void Graphic234Node::pushChild(Graphic234Node* pNode) {
    pChild.push_back(pNode);
}

void Graphic234Node::pushChild(Graphic234Node* pNode, int pos) {
    auto it = pChild.begin();
    while (pos--) it++;
    pChild.insert(it, pNode);
}

void Graphic234Node::popBackChild() {
    pChild.pop_back();
}

void Graphic234Node::pushArrow(GraphicArrow* pArrow) {
    aChild.push_back(pArrow);
}

void Graphic234Node::pushArrow(GraphicArrow* pArrow, int pos) {
    auto it = aChild.begin();
    while (pos--) it++;
    aChild.insert(it, pArrow);
}

void Graphic234Node::popBackArrow() {
    aChild.pop_back();
}

int Graphic234Node::getNumChild() {
    return pChild.size();
}

int Graphic234Node::getNumVals() {
    return pVals.size();
}

GraphicTransNode* Graphic234Node::getVal(int i) {
    auto it = pVals.begin();
    while (i--) it++;
    return *it;
}

Graphic234Node* Graphic234Node::getChild(int i) {
    auto it = pChild.begin();
    while (i--) it++;
    return *it;
}

int Graphic234Node::getNumArrow() {
    return aChild.size();
}

GraphicArrow* Graphic234Node::getArrow(int i) {
    auto it = aChild.begin();
    while (i--) it++;
    return *it;
}

void Graphic234Node::keepMiddle() {
    assert(getNumVals() == 3);
    pVals.pop_front();
    pVals.pop_back();
}

void Graphic234Node::clearArrows() {
    aChild.clear();
}

void Graphic234Node::clearChild() {
    pChild.clear();
}


Graphic234Node::NodeDimens Graphic234Node::getDimens() {
    return dim;
}

void Graphic234Node::upateDimens() {
    if (pVals.empty()) {
        dim = NodeDimens(0,0);
        return;
    }
    dim.height = pVals.front()->size;
    dim.width = pVals.front()->size * getNumVals() - pVals.front()->bsize * (getNumVals()-1);
    float sumWidth = 0;
    float maxHeight = 0;

    if (getNumChild() > 0) {
        for (Graphic234Node* child : pChild) {
            sumWidth += child->getDimens().width;
            maxHeight = std::max(maxHeight, child->getDimens().height);
        }
        sumWidth += (getNumChild()-1) * Graphic::T234_HORIZONTAL_MARGIN;
    }
    dim.width = std::max(dim.width, sumWidth);
    if (getNumChild() > 0) {
        dim.height += Graphic::T234_VERTICAL_MARGIN + maxHeight;
    }
    
    assert(dim.height >= 0);
    assert(dim.width >= 0);
}

void Graphic234Node::solveChildCollision() {
    float width = 0;
    float height = 0;

    if (getNumChild() > 0) {
        for (Graphic234Node* child : pChild) {
            width += child->getDimens().width;
            height = std::max(height, child->getDimens().height);
        }
        width += (getNumChild()-1) * Graphic::T234_HORIZONTAL_MARGIN;
    }
    int siz = getNumVals() * pVals.front()->size - (getNumVals()-1) * pVals.front()->bsize;

    for (int i = 0; i < getNumVals(); ++i) {
        auto val = getVal(i);
        val->updateTransFromPos(getNewTransPos() + Vector2{i * (getVal(0)->size - getVal(0)->bsize), 0});
    }

    float posX = getNewTransPos().x + siz/2 - width/2;
    float posY = getNewTransPos().y + pVals.front()->size + Graphic::T234_VERTICAL_MARGIN;
    for (auto child : pChild) {
        float w = child->getNumVals() * child->getVal(0)->size - (child->getNumVals()-1) * child->getVal(0)->bsize;
        child->updateTransFromPos(Vector2{posX + child->getDimens().width/2 - w/2, posY});
        posX += child->getDimens().width + Graphic::T234_HORIZONTAL_MARGIN;
    }
}

Vector2 Graphic234Node::getCurPos() {
    return curPos;
}

void Graphic234Node::resetCurPos() {
    curPos = Vector2{x, y};
    for (int i = 0; i < getNumVals(); ++i) {
        getVal(i)->resetCurPos();
    }
}

bool Graphic234Node::isTrans() {
    return fabs(trans.x) > Geo::EPS || fabs(trans.y) > Geo::EPS;
}

Vector2 Graphic234Node::getTrans() {
    return trans;
}

Vector2 Graphic234Node::getNewTransPos() {
    return curPos + trans;
}


void Graphic234Node::addTrans(Vector2 v) {
    trans += v;
    for (int i = 0; i < getNumVals(); ++i) {
        getVal(i)->addTrans(v);
    }
}

void Graphic234Node::addTrans(float x, float y) {
    trans += Vector2{x, y};
    for (int i = 0; i < getNumVals(); ++i) {
        getVal(i)->addTrans(x, y);
    }
}

void Graphic234Node::updateTransFromPos(Vector2 p) {
    trans = p - curPos;
    for (int i = 0; i < getNumVals(); ++i) {
        getVal(i)->updateTransFromPos({p.x + i * (getVal(i)->size - getVal(i)->bsize), p.y});
    }
}

void Graphic234Node::applyTrans() {
    curPos += trans;
    for (auto val : pVals) {
        val->applyTrans();
    }
}

void Graphic234Node::resetTrans() {
    trans = Z_VECT;
    for (auto val : pVals) {
        val->resetTrans();
    }
}

void Graphic234Node::resetColor() {
    for (auto val : pVals) {
        val->resetColor();
    }
}

void Graphic234Node::draw() {
    for (auto arrow : aChild) {
        arrow->draw();
    }
    for (auto val : pVals) {
        val->draw();
    }
}

std::pair<Vector2, Vector2> Graphic234Node::getPosition(Graphic234Node* nodeA, Graphic234Node* nodeB, int p) {
    Vector2 newA = {
        nodeA->getNewTransPos().x + p * (nodeA->getVal(0)->size - nodeA->getVal(0)->bsize),
        nodeA->getNewTransPos().y + nodeA->getVal(0)->size
    };
    assert(nodeB->getNumVals() > 0);
    Vector2 newB = {
        nodeB->getNewTransPos().x + (nodeB->getNumVals() * nodeB->getVal(0)->size - (nodeB->getNumVals()-1) * nodeB->getVal(0)->bsize) / 2,
        nodeB->getNewTransPos().y
    };
    return std::pair{newA, newB};
}
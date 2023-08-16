#include "GraphicTrieNode.h"

GraphicTrieNode::GraphicTrieNode() 
: GraphicNode() {

}

GraphicTrieNode::GraphicTrieNode(float _x, float _y, float _s, float _bs, bool _sqr, Font* font, int _v, const std::string &_subtext) 
: GraphicNode(_x, _y, _s, _bs, _sqr, font, _v, _subtext) {
    curPos = Vector2{_x,_y};
    for (int i = 0; i < NUM_CHAR; ++i) {
        pChild[i] = nullptr;
        aChild[i] = new GraphicArrow();
    }
    trans = Z_VECT;
    dim = TrieNodeDimens(size, size);
    _isLeaf = false;
    if (isSqr) {
        outerShapeIn = std::bind(&cf::outerSqur, &size, std::placeholders::_1);
        outerShapeOut = std::bind(&cf::outerSqur, &size, std::placeholders::_1);
    } else { // circle
        outerShapeIn = std::bind(&cf::outerCirc, &size, std::placeholders::_1);
        outerShapeOut = std::bind(&cf::outerCirc, &size, std::placeholders::_1);
    }
}

GraphicTrieNode::GraphicTrieNode(float _x, float _y, float _s, float _bs, bool _sqr, Font* font, std::string str, const std::string &_subtext)
: GraphicNode(_x, _y, _s, _bs, _sqr, font, str, _subtext) {
    curPos = Vector2{_x,_y};
    for (int i = 0; i < NUM_CHAR; ++i) {
        pChild[i] = nullptr;
        aChild[i] = new GraphicArrow();
    }
    trans = Z_VECT;
    dim = TrieNodeDimens(size, size);
    _isLeaf = false;
    if (isSqr) {
        outerShapeIn = std::bind(&cf::outerSqur, &size, std::placeholders::_1);
        outerShapeOut = std::bind(&cf::outerSqur, &size, std::placeholders::_1);
    } else { // circle
        outerShapeIn = std::bind(&cf::outerCirc, &size, std::placeholders::_1);
        outerShapeOut = std::bind(&cf::outerCirc, &size, std::placeholders::_1);
    }
}


GraphicTrieNode::GraphicTrieNode(float _x, float _y, float _s, bool _sqr, int _v, const std::string &_subtext) 
: GraphicTrieNode(_x, _y, _s, Graphic::NODE_BORDER_WIDTH, _sqr, Gfont::defaultFont, _v, _subtext) {}

GraphicTrieNode::GraphicTrieNode(float _x, float _y, float _s, bool _sqr, int _v)
: GraphicTrieNode(_x, _y, _s, Graphic::NODE_BORDER_WIDTH, _sqr, Gfont::defaultFont, _v, "") {}

GraphicTrieNode::~GraphicTrieNode() {
    for (int i = 0; i < NUM_CHAR; ++i) {
        delete aChild[i];
    }
}


void GraphicTrieNode::setChild(int i, GraphicTrieNode* pNode) {
    if (pChild[i] == nullptr) {
        if (pNode != nullptr) {
            std::pair<Vector2, Vector2> nodePair = getPosition(this, pNode);
            *aChild[i] = GraphicArrow(Graphic::ARROW_LINE_WIDTH_SMALL, nodePair.first, nodePair.second);
        } else {
            *aChild[i] = GraphicArrow();
        }
    }
    pChild[i] = pNode;
}

void GraphicTrieNode::assignChild(char c, GraphicTrieNode* pNode) {
    pChild[c-MIN_CHAR] = pNode;
}

GraphicTrieNode* GraphicTrieNode::getChild(int i) {
    return pChild[i];
}

GraphicArrow*& GraphicTrieNode::refArrow(int i) {
    return aChild[i];
}


GraphicArrow* GraphicTrieNode::getArrow(int i) {
    return aChild[i];
}

GraphicTrieNode::TrieNodeDimens GraphicTrieNode::getDimens() {
    return dim;
}

void GraphicTrieNode::upateDimens() {
    int numChild = 0;
    dim.height = 0;
    dim.width = 0;
    for (int i = 0; i < NUM_CHAR; ++i) {
        if (pChild[i] != nullptr) {
            numChild++;
            dim.width += pChild[i]->getDimens().width;
            dim.height = std::max(dim.height, pChild[i]->getDimens().height);
        }
    }
    if (numChild > 0) {
        dim.width += Graphic::TRIE_HORIZONTAL_MARGIN * (numChild - 1);
        dim.height += Graphic::TRIE_VERTICAL_MARGIN + size;
    } else {
        dim.width = size;
        dim.height = size;
    }
    
    assert(dim.height >= 0);
    assert(dim.width >= 0);
}

void GraphicTrieNode::solveChildCollision() {
    float sumWidth = 0;
    int numChild = 0;
    for (int i = 0; i < NUM_CHAR; ++i) {
        if (pChild[i] != nullptr) {
            sumWidth += pChild[i]->getDimens().width;
            numChild++;
        }
    }
    if (numChild == 0) {
        return;
    }
    sumWidth += (numChild - 1) * Graphic::TRIE_HORIZONTAL_MARGIN;
    float leftPos = getNewTransPos().x + size/2 - sumWidth/2;
    float yPos = getNewTransPos().y + size + Graphic::TRIE_VERTICAL_MARGIN;
    for (int i = 0; i < NUM_CHAR; ++i) {
        if (pChild[i] != nullptr) {
            float xPos = leftPos + pChild[i]->getDimens().width/2 - pChild[i]->size/2;
            pChild[i]->updateTransFromPos(Vector2{xPos, yPos});
            leftPos += pChild[i]->getDimens().width + Graphic::TRIE_HORIZONTAL_MARGIN;
        }
    }
}

Vector2 GraphicTrieNode::getCurPos() {
    return curPos;
}

void GraphicTrieNode::resetCurPos() {
    curPos = Vector2{x, y};
}

bool GraphicTrieNode::isTrans() {
    return fabs(trans.x) > Geo::EPS || fabs(trans.y) > Geo::EPS;
}

Vector2 GraphicTrieNode::getTrans() {
    return trans;
}

Vector2 GraphicTrieNode::getNewTransPos() {
    return curPos + trans;
}


void GraphicTrieNode::addTrans(Vector2 v) {
    trans += v;
}

void GraphicTrieNode::addTrans(float x, float y) {
    trans += Vector2{x, y};
}

void GraphicTrieNode::updateTransFromPos(Vector2 p) {
    trans = p - curPos;
}

void GraphicTrieNode::applyTrans() {
    curPos += trans;
}

void GraphicTrieNode::resetTrans() {
    trans = Z_VECT;
}

bool GraphicTrieNode::isLeaf() {
    return _isLeaf;
}

void GraphicTrieNode::setLeaf() {
    _isLeaf = true;
}

bool GraphicTrieNode::isRealLeaf() {
    for (int i = 0; i < NUM_CHAR; ++i) {
        if (pChild[i] != nullptr) {
            return false;
        }
    }
    return true;
}


void GraphicTrieNode::draw() {
    for (int i = 0; i < NUM_CHAR; ++i) {
        aChild[i]->draw();
    }
    GraphicNode::draw();
}

std::pair<Vector2, Vector2> GraphicTrieNode::getPosition(GraphicTrieNode* nodeA, GraphicTrieNode* nodeB) {
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
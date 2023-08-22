#include "GraphicTrie.h"

void GraphicTrie::resetColorAllNodes(GraphicTrieNode* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    pRoot->resetColor();
    for (int i = 0; i < GraphicTrieNode::NUM_CHAR; ++i) {
        pRoot->getArrow(i)->resetColor();
        resetColorAllNodes(pRoot->getChild(i));
    }
}

void GraphicTrie::resetColorAllNodes() {
    resetColorAllNodes(pRoot);
}

void GraphicTrie::resetTransAllNodes(GraphicTrieNode* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    pRoot->resetTrans();
    for (int i = 0; i < GraphicTrieNode::NUM_CHAR; ++i) {
        pRoot->getArrow(i)->resetTrans();
        resetTransAllNodes(pRoot->getChild(i));
    }
}

void GraphicTrie::resetTransAllNodes() {
    resetTransAllNodes(pRoot);
}

void GraphicTrie::resetCurPosAllNodes(GraphicTrieNode* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    pRoot->resetCurPos();
    for (int i = 0; i < GraphicTrieNode::NUM_CHAR; ++i) {
        pRoot->getArrow(i)->resetCurAB();
        resetCurPosAllNodes(pRoot->getChild(i));
    }
}

void GraphicTrie::resetCurPosAllNodes() {
    resetCurPosAllNodes(pRoot);
}

GraphicTrie::GraphicTrie() {
    pRoot = nullptr;
    _size = 0;
}

void GraphicTrie::realPush(std::string s, ListOfOperationsGroups* ALOG) {
    GraphicTrieNode* cur = pRoot;
    for (int i = 0; i < (int)s.size(); ++i) {
        int c = s[i] - GraphicTrieNode::MIN_CHAR;
        if (cur->getChild(c) == nullptr) {
            cur->setChild(c, new GraphicTrieNode(
                cur->getNewTransPos().x,
                cur->getNewTransPos().y + cur->size + Graphic::TRIE_VERTICAL_MARGIN,
                Graphic::NODE_SIZE_SMALL,
                Graphic::NODE_BORDER_WIDTH_SMALL, 
                false,
                Gfont::defaultFontSmall,
                std::string{s[i]},
                ""
            ));
        }
        cur = cur->getChild(c);
        ALOG->animateFadeIn(cur);
    }
    if (!cur->isLeaf()) {
        cur->setLeaf();
        cur->val.assign(cur->val.content + "*");
        _size++;
    }
}

void GraphicTrie::showEdgeOfTree(GraphicTrieNode* pRoot, ListOfOperationsGroups* ALOG) {
    for (int i = 0; i < GraphicTrieNode::NUM_CHAR; ++i) {
        if (pRoot->getChild(i) != nullptr) {
            ALOG->animateFadeIn(pRoot->getArrow(i));
            ALOG->animateSlideIn(pRoot->getArrow(i));
            showEdgeOfTree(pRoot->getChild(i), ALOG);
        }
    }
}

void GraphicTrie::showEdgeOfTree(ListOfOperationsGroups* ALOG) {
    if (pRoot == nullptr) {
        return;
    }
    showEdgeOfTree(pRoot, ALOG);
}

ExitStatus GraphicTrie::initialize(int initSize, ListOfOperationsGroups* ALOG) { // Randomly initialize 
    if (initSize < 0 || initSize > Core::MAX_NUM_TRIE_ELM) {
        return ExitMess::FAIL_TRIE_SIZE_OOB;
    }
    std::vector<std::string> vals;
    for (int i = 0; i < initSize; ++i) {
        vals.push_back(cf::getRandomString(GetRandomValue(1, Core::MAX_LEN_TRIE_ELM)));
    }
    return initialize(vals, ALOG);
}

ExitStatus GraphicTrie::initialize(std::vector<std::string> vals, ListOfOperationsGroups* ALOG) { // Initialize with given values
    if ((int)vals.size() > Core::MAX_NUM_TRIE_ELM) {
        return ExitMess::FAIL_TRIE_SIZE_OOB;
    }
    for (int i = 0; i < (int)vals.size(); ++i) {
        if ((int)vals[i].size() < 1 || (int)vals[i].size() > Core::MAX_LEN_TRIE_ELM) {
            return ExitMess::FAIL_TRIE_LEN_OOB;
        }
        for (char c : vals[i]) {
            if (c < 'a' || c > 'z') {
                return ExitMess::FAIL_CHAR_OOB;
            }
        }
    }

    ALOG->clearGroup();
    ALOG->resetCode();
    destroy();
   
    pRoot = new GraphicTrieNode(
        Graphic::TRIE_ORG_X, 
        Graphic::TRIE_ORG_Y,
        Graphic::NODE_SIZE_SMALL,
        Graphic::NODE_BORDER_WIDTH_SMALL, 
        false,
        Gfont::defaultFontSmall,
        "",
        ""
    );
    ALOG->addNewGroup();
    ALOG->animateFadeIn(pRoot);

    if (!vals.empty()) {    
        for (int i = 0; i < (int)vals.size(); ++i) {
            realPush(vals[i], ALOG);
        }
        balanceTreeLayout(ALOG);

        ALOG->addNewGroup();
        showEdgeOfTree(ALOG);
    }

    ALOG->build();

    // std::cerr << " >> INITIALIZE done\n"; 
    return ExitMess::SUCCESS;
}

ExitStatus GraphicTrie::initialize(std::string strVals, ListOfOperationsGroups* ALOG) { // Initialize with given values
    ExitStatus status;
    std::vector<std::string> vals;
    status = User::input2vector(strVals, vals, Valid::LOWERCASE_ALPHABET + " ,\r\n");
    if (!status.success) {
        return status;
    }
    return initialize(vals, ALOG);
}

void GraphicTrie::applyTransToAllNodes(GraphicTrieNode* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    pRoot->applyTrans();
    for (int i = 0; i < GraphicTrieNode::NUM_CHAR; ++i) {
        if (pRoot->getChild(i) != nullptr) {
            pRoot->getArrow(i)->applyTransAB();
            applyTransToAllNodes(pRoot->getChild(i));
        }
    }
}

void GraphicTrie::applyTransToAllNodes() {
    applyTransToAllNodes(pRoot);
}

void GraphicTrie::buildTransOfSubTree(GraphicTrieNode* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    for (int i = 0; i < GraphicTrieNode::NUM_CHAR; ++i) {
        buildTransOfSubTree(pRoot->getChild(i));
    }
    pRoot->solveChildCollision();
    pRoot->upateDimens();
    if (pRoot == this->pRoot) {
        pRoot->updateTransFromPos(Vector2{(float)Graphic::TRIE_ORG_X, (float)Graphic::TRIE_ORG_Y});
    }
}

void GraphicTrie::buildTransOfAllNodes(GraphicTrieNode* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    for (int i = 0; i < GraphicTrieNode::NUM_CHAR; ++i) {
        if (pRoot->getChild(i) != nullptr) {
            pRoot->getChild(i)->addTrans(pRoot->getTrans());
            pRoot->getArrow(i)->updateTransFromPos(GraphicTrieNode::getPosition(pRoot, pRoot->getChild(i)));
            buildTransOfAllNodes(pRoot->getChild(i));
        }
    }
}

void GraphicTrie::buildTransOfTree() {
    buildTransOfSubTree(pRoot);
    buildTransOfAllNodes(pRoot);
}

void GraphicTrie::animateTransformAllNodes(GraphicTrieNode* pRoot, ListOfOperationsGroups* ALOG) {
    if (pRoot == nullptr) {
        return;
    }
    if (pRoot->isTrans()) {
        ALOG->animateTransform(pRoot, pRoot->getCurPos().x, pRoot->getCurPos().y, pRoot->getTrans().x, pRoot->getTrans().y);
    }
    for (int i = 0; i < GraphicTrieNode::NUM_CHAR; ++i) {
        if (pRoot->getChild(i) != nullptr) {
            if (pRoot->getArrow(i)->isTransA()) {
                ALOG->animateTransform(&pRoot->getArrow(i)->pA, pRoot->getArrow(i)->curA.x, pRoot->getArrow(i)->curA.y, pRoot->getArrow(i)->transA.x, pRoot->getArrow(i)->transA.y);
            }
            if (pRoot->getArrow(i)->isTransB()) {
                ALOG->animateTransform(&pRoot->getArrow(i)->pB, pRoot->getArrow(i)->curB.x, pRoot->getArrow(i)->curB.y, pRoot->getArrow(i)->transB.x, pRoot->getArrow(i)->transB.y);
            }
            animateTransformAllNodes(pRoot->getChild(i), ALOG);
        }
    }
}

void GraphicTrie::balanceTreeLayout(ListOfOperationsGroups* ALOG) {
    applyTransToAllNodes();
    resetTransAllNodes();
    buildTransOfTree();
    animateTransformAllNodes(pRoot, ALOG);
}

ExitStatus GraphicTrie::push(std::string s, ListOfOperationsGroups* ALOG) {
    assert(_size <= Core::MAX_NUM_TRIE_ELM);
    if (_size == Core::MAX_NUM_TRIE_ELM) {
        return ExitMess::FAIL_TRIE_REACH_MAX_SIZE;
    }
    if ((int)s.size() < 1 || (int)s.size() > Core::MAX_LEN_TRIE_ELM) {
        return ExitMess::FAIL_TRIE_LEN_OOB;
    }
    for (char c : s) {
        if (c < 'a' || c > 'z') {
            return ExitMess::FAIL_CHAR_OOB;
        }
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::TRIE_PUSH);
    reset();
    
    GraphicTrieNode* cur = pRoot;
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({0});
    ALOG->animateNodeFromNormalToIter(cur);
    for (int i = 0; i < (int)s.size(); ++i) {
        // std::cerr << s[i] << '\n';
        int c = s[i] - GraphicTrieNode::MIN_CHAR;
        if (cur->getChild(c) == nullptr) {
            GraphicTrieNode* newNode = new GraphicTrieNode(
                cur->getNewTransPos().x,
                cur->getNewTransPos().y + cur->size + Graphic::TRIE_VERTICAL_MARGIN,
                Graphic::NODE_SIZE_SMALL,
                Graphic::NODE_BORDER_WIDTH_SMALL, 
                false,
                Gfont::defaultFontSmall,
                std::string{s[i]},
                ""
            );
            cur->setChild(c, newNode);

            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({2,3});
            ALOG->animateFadeIn(newNode);
            ALOG->animateFadeIn(cur->getArrow(c));
            ALOG->animateSlideIn(cur->getArrow(c));
            balanceTreeLayout(ALOG);
        }

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({4});
        ALOG->animateNodeFromIterToNearIter(cur);
        ALOG->animateSlideColorIn(cur->getArrow(c));
        ALOG->animateArrowSlideFromNormalToIter(cur->getArrow(c));
        cur = cur->getChild(c);
        ALOG->animateNodeFromNormalToIter(cur);
    }
    if (!cur->isLeaf()) {
        _size++;
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({5});
        ALOG->animateTransText(&cur->val, cur->val.content, cur->val.content + "*");
        cur->setLeaf();
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicTrie::search(std::string s, ListOfOperationsGroups* ALOG) {
    if ((int)s.size() < 1 || (int)s.size() > Core::MAX_LEN_TRIE_ELM) {
        return ExitMess::FAIL_TRIE_LEN_OOB;
    }
    for (char c : s) {
        if (c < 'a' || c > 'z') {
            return ExitMess::FAIL_CHAR_OOB;
        }
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::TRIE_SEARCH);
    reset();

    GraphicTrieNode* cur = pRoot;
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({0});
    ALOG->animateNodeFromNormalToIter(cur);

    for (int i = 0; i < (int)s.size(); ++i) {
        int c = s[i] - GraphicTrieNode::MIN_CHAR;
        if (cur->getChild(c) == nullptr) {
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({2});
            ALOG->animateNodeFromIterToNearIter(cur);

            ALOG->build();

            return ExitMess::SUCCESS;
        } else {
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({3});
            ALOG->animateNodeFromIterToNearIter(cur);
            ALOG->animateSlideColorIn(cur->getArrow(c));
            ALOG->animateArrowSlideFromNormalToIter(cur->getArrow(c));
            cur = cur->getChild(c); 
            ALOG->animateNodeFromNormalToIter(cur);
        }
    }

    if (cur->isLeaf()) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({4});
        ALOG->animateNodeFromIterToFocus(cur);
    } else {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({4});
        ALOG->animateNodeFromIterToNearIter(cur);
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

bool GraphicTrie::remove(GraphicTrieNode* pRoot, int i, const std::string& s, ListOfOperationsGroups* ALOG) {
    ALOG->animateNodeFromNormalToIter(pRoot);

    if (i == (int)s.size()) {
        if (!pRoot->isLeaf()) {
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({1});
            ALOG->animateNodeFromIterToNormal(pRoot);
            return false;
        }

        _size--;

        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({2});
        ALOG->animateNodeFromIterToNormal(pRoot);
        ALOG->animateTransText(&pRoot->val, pRoot->val.content, pRoot->val.content.substr(0,1));

        if (pRoot->isRealLeaf()) {
            nodes.push_back(pRoot);
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({3,4});
            ALOG->animateFadeOut(pRoot);
            return true;
        } else {
            return false;
        }
    }

    int c = s[i] - GraphicTrieNode::MIN_CHAR;
    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({6});

    if (pRoot->getChild(c) == nullptr) {
        ALOG->addNewGroup();
        ALOG->backGroup()->setHighlightLines({7});
        return false;
    }

    ALOG->addNewGroup();
    ALOG->backGroup()->setHighlightLines({8});
    ALOG->animateNodeFromIterToNearIter(pRoot);
    ALOG->animateSlideColorIn(pRoot->getArrow(c));
    ALOG->animateArrowSlideFromNormalToIter(pRoot->getArrow(c));

    bool flag = remove(pRoot->getChild(c), i+1, s, ALOG);
    ALOG->animateSlideColorOut(pRoot->getArrow(c));
    ALOG->animateArrowSlideFromIterToNormal(pRoot->getArrow(c));
    ALOG->animateNodeFromNearIterToIter(pRoot);

    if (flag) {
        ALOG->animateSlideOut(pRoot->getArrow(c));
        pRoot->setChild(c, nullptr);

        if (pRoot != this->pRoot && pRoot->isRealLeaf() && !pRoot->isLeaf()) {
            nodes.push_back(pRoot);
            ALOG->addNewGroup();
            ALOG->backGroup()->setHighlightLines({9,10});
            ALOG->animateFadeOut(pRoot);
            return true;
        }

    }
    ALOG->addNewGroup();
    ALOG->animateNodeFromIterToNormal(pRoot);
    return false;
}


ExitStatus GraphicTrie::remove(std::string s, ListOfOperationsGroups* ALOG) {
    if ((int)s.size() < 1 || (int)s.size() > Core::MAX_LEN_TRIE_ELM) {
        return ExitMess::FAIL_TRIE_LEN_OOB;
    }
    for (char c : s) {
        if (c < 'a' || c > 'z') {
            return ExitMess::FAIL_CHAR_OOB;
        }
    }

    ALOG->clearGroup();
    ALOG->loadCode(CPath::TRIE_REMOVE);
    reset();

    ALOG->addNewGroup();
    remove(pRoot, 0, s, ALOG);
    balanceTreeLayout(ALOG);

    ALOG->build();

    return ExitMess::SUCCESS;
}


void GraphicTrie::draw(GraphicTrieNode* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    // std::cerr << " >> GraphicTrie::draw() -> " << pRoot << '\n';
    pRoot->draw();
    for (int i = 0; i < GraphicTrieNode::NUM_CHAR; ++i) {
        draw(pRoot->getChild(i));
    }
}

void GraphicTrie::draw() {
    draw(pRoot);
    for (GraphicTrieNode* pNode : nodes) {
        pNode->draw();
    }
}


void GraphicTrie::clearSaparated() {
    for (GraphicTrieNode* node : nodes) {
        delete node;
    }
    nodes.clear();
}

void GraphicTrie::reset() {
    clearSaparated();
    resetColorAllNodes();
    resetTransAllNodes();
    resetCurPosAllNodes();
}

void GraphicTrie::destroy(GraphicTrieNode* pRoot) {
    if (pRoot == nullptr) {
        return;
    }
    for (int i = 0; i < GraphicTrieNode::NUM_CHAR; ++i) {
        destroy(pRoot->getChild(i));
    }
    delete pRoot;
}


void GraphicTrie::destroy() {
    reset();
    destroy(pRoot);
    pRoot = nullptr;
    _size = 0;
}
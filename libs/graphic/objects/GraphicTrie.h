#ifndef GRAPHIC_TRIE_H
#define GRAPHIC_TRIE_H

#include <list>

#include "../../global.h"
#include "../../core/ExitStatus.h"
#include "GraphicTrieNode.h"
#include "../../animation/OperationsGroups.h"
#include "../../animation/ListOfOperationsGroups.h"
#include "../../core/userfunc.h"
#include "../../core/ccppfunc.h"

class GraphicTrie {
private:
    GraphicTrieNode* pRoot;
    int _size;

    std::list<GraphicTrieNode*> nodes;

    void resetColorAllNodes(GraphicTrieNode* pRoot);
    void resetColorAllNodes();
    void resetTransAllNodes(GraphicTrieNode* pRoot);
    void resetTransAllNodes();
    void resetCurPosAllNodes(GraphicTrieNode* pRoot);
    void resetCurPosAllNodes();
    void clearSaparated();
    void reset();
    void destroy(GraphicTrieNode* pRoot);

    void realPush(std::string s, ListOfOperationsGroups* ALOG);

    void applyTransToAllNodes(GraphicTrieNode* pRoot);
    void applyTransToAllNodes();

    void buildTransOfSubTree(GraphicTrieNode* pRoot);
    void buildTransOfAllNodes(GraphicTrieNode* pRoot);
    void buildTransOfTree();
    void animateTransformAllNodes(GraphicTrieNode* pRoot, ListOfOperationsGroups* ALOG);
    void balanceTreeLayout(ListOfOperationsGroups* ALOG);

    void showEdgeOfTree(GraphicTrieNode* pRoot, ListOfOperationsGroups* ALOG);
    void showEdgeOfTree(ListOfOperationsGroups* ALOG);
 
    bool remove(GraphicTrieNode* pRoot, int i, const std::string& s, ListOfOperationsGroups* ALOG);

    void draw(GraphicTrieNode* pRoot);

public:
    GraphicTrie();

    ExitStatus initialize(int initSize, ListOfOperationsGroups* ALOG); // Randomly initialize
    ExitStatus initialize(std::vector<std::string> vals, ListOfOperationsGroups* ALOG); // Initialize with given values
    ExitStatus initialize(std::string strVals, ListOfOperationsGroups* ALOG); // Initialize with given values

    ExitStatus push(std::string s, ListOfOperationsGroups* ALOG);

    ExitStatus search(std::string s, ListOfOperationsGroups* ALOG);

    ExitStatus remove(std::string s, ListOfOperationsGroups* ALOG);

    void draw();

    void destroy();
};

#endif
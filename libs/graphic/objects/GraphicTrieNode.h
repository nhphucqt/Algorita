#ifndef GRAPHIC_TRIE_NODE_H
#define GRAPHIC_TRIE_NODE_H

#include <string>
#include "../../global.h"
#include "../../rcore/rVector2.h"
#include "GraphicNode.h"
#include "GraphicArrow.h"

class GraphicTrieNode : public GraphicNode {
public:
    static const int NUM_CHAR = 26;
    static const char MIN_CHAR = 'a';

    class TrieNodeDimens {
    public:
        float width, height;

        TrieNodeDimens() : width(0), height(0) {}
        TrieNodeDimens(float width, float height) : width(width), height(height) {}
    };
private:
    Vector2 curPos;
    GraphicTrieNode* pChild[NUM_CHAR];
    GraphicArrow* aChild[NUM_CHAR];
    Vector2 trans;
    TrieNodeDimens dim;
    bool _isLeaf;
    
public:
    GraphicTrieNode();
    GraphicTrieNode(float _x, float _y, float _s, float _bs, bool _sqr, Font* font, int _v, const std::string &_subtext);
    GraphicTrieNode(float _x, float _y, float _s, float _bs, bool _sqr, Font* font, std::string str, const std::string &_subtext);
    GraphicTrieNode(float _x, float _y, float _s, bool _sqr, int _v, const std::string &_subtext);
    GraphicTrieNode(float _x, float _y, float _s, bool _sqr, int _v);
    ~GraphicTrieNode();

    void setChild(int i, GraphicTrieNode* pNode);

    void assignChild(char c, GraphicTrieNode* pNode);

    GraphicTrieNode* getChild(int i);

    // void updateLeft(GraphicTrieNode* newLeft);
    // void updateRight(GraphicTrieNode* newRight);

    GraphicArrow* getArrow(int i);

    GraphicArrow*& refArrow(int i);

    Vector2 getCurPos();
    void resetCurPos();

    bool isTrans();
    Vector2 getTrans();
    Vector2 getNewTransPos();
    void addTrans(Vector2 v);
    void addTrans(float x, float y);
    void updateTransFromPos(Vector2 p);
    void applyTrans();
    void resetTrans();

    TrieNodeDimens getDimens();
    void upateDimens();
    void solveChildCollision();

    bool isLeaf();
    void setLeaf();

    bool isRealLeaf();

    void draw();

    static std::pair<Vector2, Vector2> getPosition(GraphicTrieNode* nodeA, GraphicTrieNode* nodeB);

};

#endif
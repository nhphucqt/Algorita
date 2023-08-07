#ifndef GRAPHIC_BINARY_TREE_NODE_H
#define GRAPHIC_BINARY_TREE_NODE_H

#include <string>
#include "../../global.h"
#include "../../rcore/rVector2.h"
#include "GraphicNode.h"
#include "GraphicArrow.h"

class GraphicBinaryTreeNode : public GraphicNode {
public:
    class BinaryNodeDimens {
    public:
        float leftWidth, rightWidth;
        float height;

        BinaryNodeDimens() : leftWidth(0), rightWidth(0), height(0) {}
        BinaryNodeDimens(float leftWidth, float rightWidth, float height) : leftWidth(leftWidth), rightWidth(rightWidth), height(height) {}

        float getWidth();
    };
private:
    Vector2 curPos;
    GraphicBinaryTreeNode* pLeft;
    GraphicBinaryTreeNode* pRight;
    GraphicArrow aLeft;
    GraphicArrow aRight;
    Vector2 trans;
    int level;
    BinaryNodeDimens dim;
    
public:
    GraphicBinaryTreeNode();
    GraphicBinaryTreeNode(float _x, float _y, float _s, float _bs, bool _sqr, Font* font, int _v, const std::string &_subtext);
    GraphicBinaryTreeNode(float _x, float _y, float _s, bool _sqr, int _v, const std::string &_subtext);
    GraphicBinaryTreeNode(float _x, float _y, float _s, bool _sqr, int _v);

    void setLeft(GraphicBinaryTreeNode* pNode);
    void setRight(GraphicBinaryTreeNode* pNode);

    GraphicBinaryTreeNode* getLeft();
    GraphicBinaryTreeNode* getRight();

    void updateLeft(GraphicBinaryTreeNode* newLeft);
    void updateRight(GraphicBinaryTreeNode* newRight);

    GraphicArrow* getLeftArrow();
    GraphicArrow* getRightArrow();

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

    BinaryNodeDimens getDimens();
    void upateDimens();
    bool isColisionInLeft();
    bool isColisionInRight();
    Vector2 getLeftCollision();
    Vector2 getRightCollision();
    void solveLeftCollision();
    void solveRightCollision();

    int getLevel();
    void updateLevel(int newLevel);

    void draw();

    static std::pair<Vector2, Vector2> getPosition(GraphicBinaryTreeNode* nodeA, GraphicBinaryTreeNode* nodeB);

};

#endif
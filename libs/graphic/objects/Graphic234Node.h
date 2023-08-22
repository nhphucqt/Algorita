#ifndef GRAPHIC_234_NODE_H
#define GRAPHIC_234_NODE_H

#include <string>
#include <list>
#include "../../global.h"
#include "../../rcore/rVector2.h"
#include "GraphicTransNode.h"
#include "GraphicArrow.h"

class Graphic234Node {
public:
    class NodeDimens {
    public:
        float width;
        float height;

        NodeDimens() : width(0), height(0) {}
        NodeDimens(float width, float height) : width(width), height(height) {}
    };
    float x, y;
private:
    Vector2 curPos;
    std::list<GraphicTransNode*> pVals;
    std::list<Graphic234Node*> pChild;
    std::list<GraphicArrow*> aChild;
    Vector2 trans;
    NodeDimens dim;
    
public:
    Graphic234Node();
    Graphic234Node(float _x, float _y);
    ~Graphic234Node();

    void pushVal(GraphicTransNode* pNode);
    void pushChild(Graphic234Node* pNode);
    void pushChild(Graphic234Node* pNode, int pos);
    void pushArrow(GraphicArrow* pArrow);
    void pushArrow(GraphicArrow* pArrow, int pos);

    void popBackArrow();
    void popBackChild();
    void popBackVal();

    int getNumVals();
    GraphicTransNode* getVal(int i);

    int getNumChild();
    Graphic234Node* getChild(int i);

    int getNumArrow();
    GraphicArrow* getArrow(int i);

    void keepMiddle();
    void clearArrows();
    void clearChild();

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

    NodeDimens getDimens();
    void upateDimens();
    void solveChildCollision();

    void resetColor();

    void draw();

    static std::pair<Vector2, Vector2> getPosition(Graphic234Node* nodeA, Graphic234Node* nodeB, int p);

};

#endif
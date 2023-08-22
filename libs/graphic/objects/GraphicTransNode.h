#ifndef GRAPHIC_TRANS_NODE_H
#define GRAPHIC_TRANS_NODE_H

#include <string>
#include "../../global.h"
#include "../../rcore/rVector2.h"
#include "GraphicNode.h"
#include "GraphicArrow.h"

class GraphicTransNode : public GraphicNode {
private:
    Vector2 curPos;
    Vector2 trans;
    
public:
    GraphicTransNode();
    GraphicTransNode(float _x, float _y, float _s, float _bs, bool _sqr, Font* font, int _v, const std::string &_subtext);
    GraphicTransNode(float _x, float _y, float _s, float _bs, bool _sqr, Font* font, std::string str, const std::string &_subtext);
    GraphicTransNode(float _x, float _y, float _s, bool _sqr, int _v, const std::string &_subtext);
    GraphicTransNode(float _x, float _y, float _s, bool _sqr, int _v);

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

    void draw();
};

#endif
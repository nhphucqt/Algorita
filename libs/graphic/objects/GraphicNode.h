#ifndef GRAPHIC_NODE_H
#define GRAPHIC_NODE_H

#include <cmath>
#include <assert.h>
#include <functional>

#include "../../conf_raylib.h"
#include "../../global.h"
#include "../../rcore/rColor.h"
#include "../../core/ccppfunc.h"
#include "../gui/StyledText.h"

class GraphicNode {
public:
    // Position
	float x, y; // graphic position

    // Shape and Dimension
	float size, bsize;
	bool isSqr; // 1 -> square | 0 -> circle

    // Color
    Color backColor, foreColor, bordColor;
    Color *pBackColor, *pForeColor, *pBordColor;
    float transparent;

    // Node value
    int nVal;
    StyledText val;
    StyledText sub, super;

    // Events
    bool isAppear;

    // Functors
    std::function<Vector2(Vector2)> outerShapeIn, outerShapeOut;

    // Constructors
    GraphicNode();
    GraphicNode(float _x, float _y, float _s, float _bs, bool _sqr, Font* font, int _v, const std::string &_subtext);
    GraphicNode(float _x, float _y, float _s, bool _sqr, int _v, const std::string &_subtext);
    GraphicNode(float _x, float _y, float _s, bool _sqr, int _v);

    // Methods
    Vector2 getCenter() const;

    void vanish();
    void appear();

    void transform(int Tx, int Ty);
    void displace(int Dx, int Dy);

    void setValue(int x);
    void setSubText(const std::string &_subtext);
    void setSuperText(const std::string &_supertext);

    void resetColor();
    void setDisabledColor();

    void draw();
};

#endif
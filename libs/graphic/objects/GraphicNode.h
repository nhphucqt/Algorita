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
    float lx, ly; // last graphic position

    // Shape and Dimension
	float size, bsize;
	bool isSqr; // 1 -> square | 0 -> circle

    // Color
    Color backColor, foreColor, bordColor;
    float transparent;

    // Node value
    int nVal;
    StyledText val;
    StyledText sub;

    // Events
    bool isAppear;

    // Functors
    std::function<Vector2(Vector2)> outerShapeIn, outerShapeOut;

    // Constructors
    GraphicNode();
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

    void resetColor();

    void draw();
};

#endif
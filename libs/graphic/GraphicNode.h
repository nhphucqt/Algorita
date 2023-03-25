#ifndef GRAPHIC_NODE_H
#define GRAPHIC_NODE_H

#include <cmath>
#include <assert.h>
#include <functional>

#include "../conf_raylib.h"
#include "../global.h"
#include "../rcore/rcolor.h"
#include "../core/ccppfunc.h"
#include "StyledText.h"

class GraphicNode {
public:
    // Position
    float cx, cy; // core position
	float x, y;   // graphic position

    // Shape and Dimension
	float size, bsize;
	bool isSqr; // 1 -> square | 0 -> circle

    // Color
    raylib::Color backColor[2], foreColor[2], bordColor[2];
    float transparent;

    // Node value
    int val;
    StyledText text;

    // Events
    bool isFocus;

    // Functors
    std::function<raylib::Vector2(raylib::Vector2)> outerShapeIn, outerShapeOut;

    // Constructors
    GraphicNode();
    GraphicNode(float _x, float _y, float _s, bool _sqr, int _v);

    // Methods
    raylib::Vector2 getCenter() const;
    void vanish();
    void appear();
    void setValue(int x);
    void draw();
};

#endif
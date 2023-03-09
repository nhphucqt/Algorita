#ifndef GRAPHIC_NODE_H
#define GRAPHIC_NODE_H

#include <cmath>
#include <assert.h>

namespace raylib {
    #include "raylib.h"
}
#include "../global.h"
#include "../rcore/rcolor.h"
#include "StyledText.h"

class GraphicNode {
public:
    // Position
	double x, y;
    double lx, ly;

    // Shape and Dimension
	int size, bsize;
	bool isSqr; // 1 -> square | 0 -> circle

    // Color
    raylib::Color backColor[2], foreColor[2], bordColor[2];
    double transparent;

    // Node value
    int val;
    StyledText text;

    // Events
    bool isFocus;

    // Constructors
    GraphicNode();
    GraphicNode(double _x, double _y, int _s, bool _sqr, int _v);

    // Methods
    void draw();
};



#endif
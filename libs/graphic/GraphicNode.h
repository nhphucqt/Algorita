#ifndef GRAPHIC_NODE_H
#define GRAPHIC_NODE_H

#include <cmath>

namespace raylib {
    #include "raylib.h"
}
#include "../global.h"
#include "../rcore/rcolor.h"

class GraphicNode {
public:
	double x, y;
    double lx, ly;
	int size, bsize;
    double transparent;
	bool isSqr; // 1 -> square | 0 -> circle
    bool isFocus;
    raylib::Color backColor[2], foreColor[2], bordColor[2];

    GraphicNode();
    GraphicNode(double _x, double _y, int _s, bool _sqr);
    void draw();
};



#endif
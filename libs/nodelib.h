#ifndef NODELIB_H
#define NODELIB_H

#include <cmath>
namespace raylib {
    #include "raylib.h"
}
#include "global.h"

class GraphicNode {
public:
	double x, y;
    double lx, ly;
	int size;
	raylib::Color currColor, trueColor;
    double transparent;
	bool isSqr; // 1 -> square | 0 -> circle

    GraphicNode();
    GraphicNode(double _x, double _y, int _s, raylib::Color _cc, raylib::Color _tc, bool _sqr);
    void draw();
};



#endif
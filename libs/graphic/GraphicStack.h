#ifndef GRAPHIC_STACK_H
#define GRAPHIC_STACK_H

#include <assert.h>
#include <iostream>
#include <functional>

#include "../global.h"
#include "../core/ccppfunc.h"
#include "GraphicSinglyNode.h"
#include "animation.h"

#include "../core/CoreStack.h"

class GraphicStack {
private:
    bool realPush(int val); // ALWAYS PUSH TO NEW SCENE

    bool animatePop(); // ALWAYS PUSH TO NEW SCENE
    bool realPop(); // ALWAYS PUSH TO NEW SCENE

    bool transformAllNodes(int Tx, int Ty);

public:
    GraphicSinglyNode* pHead;
    CoreStack core;

    GraphicStack();

    void push(int val);
    bool pop();

    void draw();

    void destroy();
};

#endif
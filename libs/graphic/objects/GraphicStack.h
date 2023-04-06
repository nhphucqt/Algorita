// #ifndef GRAPHIC_STACK_H
// #define GRAPHIC_STACK_H

// #include <assert.h>
// #include <iostream>
// #include <functional>

// #include "../../global.h"
// #include "../../core/ccppfunc.h"
// #include "GraphicSinglyNode.h"
// #include "../../animation/animation.h"

// #include "../../core/objects/CoreStack.h"

// class GraphicStack {
// private:
//     GraphicSinglyNode* pHead;
//     CoreStack core;
    
//     bool animatePush(int val); // ALWAYS PUSH TO NEW SCENE

//     bool animatePop_1(); // ALWAYS PUSH TO NEW SCENE
//     bool animatePop_2(); // ALWAYS PUSH TO NEW SCENE

//     bool transformAllNodes(int Tx, int Ty);

// public:

//     GraphicStack();

//     void push(int val);
//     bool pop();

//     void draw();

//     void destroy();
// };

// #endif
#ifndef VSTACK_H
#define VSTACK_H

#include <assert.h>
#include <iostream>

#include "../global.h"
#include "SinglyNode.h"
#include "../graphic/animation.h"

class VStack {
public:
    SinglyNode* pHead;

    VStack();

    void transAllNodes(int tx, int ty);

    void push(SinglyNode* pNode);
    void push(int val);
    bool pop();

    void draw();

    void destroy();
};

#endif
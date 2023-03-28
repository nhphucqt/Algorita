#ifndef CORE_STACK_H
#define CORE_STACK_H

#include <assert.h>

#include "../../global.h"
#include "CoreSinglyNode.h"

class CoreStack {
private:
    CoreSinglyNode* pHead;
    CoreSinglyNode* pIter;

public:
    CoreStack();

    CoreSinglyNode* begin() const;
    CoreSinglyNode* iter() const;
    CoreSinglyNode* next();
    CoreSinglyNode* resetIter();

    void push(int val);
    bool pop();

    void destroy();
};



#endif
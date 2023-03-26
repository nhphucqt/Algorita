#ifndef CORE_SINGLY_NODE_H
#define CORE_SINGLY_NODE_H

class CoreSinglyNode {
public:
    int val;
    CoreSinglyNode* pNext;

    CoreSinglyNode();
    CoreSinglyNode(int _v);
    CoreSinglyNode(int _v, CoreSinglyNode* pNode);
    CoreSinglyNode(CoreSinglyNode* pNode);

    void setNext(CoreSinglyNode* pNode);
};

#endif

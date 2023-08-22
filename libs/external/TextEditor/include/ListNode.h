#ifndef lIST_NODE_H
#define lIST_NODE_H

struct ListNode
{
	char c = 0;
	ListNode* next = nullptr;
	ListNode* prev = nullptr;
};

#endif
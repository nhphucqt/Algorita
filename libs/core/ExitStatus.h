#ifndef EXIT_STATUS_H
#define EXIT_STATUS_H

#include <string>

#include "../global.h"
#include "ccppfunc.h"

class ExitStatus {
public:
    bool success;
    std::string message;

    ExitStatus();
    ExitStatus(bool _success, const std::string &_message);
};

namespace ExitMess {
    const ExitStatus SUCCESS(true, "");
    const ExitStatus FAIL(false, "");

    const ExitStatus FAIL_VALUE_OOB(false, "Value is out of bounds: Allow from " + cf::num2str(Core::NODE_MIN_VALUE) + " to " + cf::num2str(Core::NODE_MAX_VALUE));
    const ExitStatus FAIL_CHAR_OOB(false, "Character is out of bounds: Allow from \"a\" to \"z\"");

    const ExitStatus FAIL_LL_EMPTY(false, "The list is empty");
    const ExitStatus FAIL_LL_SIZE_OOB(false, "Size is out of bounds: Allow from 0 to " + cf::num2str(Core::MAX_NUM_NODE_SLL));
    const ExitStatus FAIL_LL_REACH_MAX_SIZE(false, "The list has reached maximum size which is " + cf::num2str(Core::MAX_NUM_NODE_SLL));

    const ExitStatus FAIL_ARR_CAPA_OOB(false, "Capacity is out of bounds: Allow from 0 to " + cf::num2str(Core::MAX_NUM_ARRAY_ELM));
    const ExitStatus FAIL_ARR_SIZE_OOB(false, "Size is out of bounds: Allow from 0 to " + cf::num2str(Core::MAX_NUM_ARRAY_ELM));
    const ExitStatus FAIL_ARR_SIZE_OOB_CAPA(false, "The size cannot be negative or larger than capacity");
    const ExitStatus FAIL_ARR_EMPTY(false, "The size of the array is 0");
    const ExitStatus FAIL_ARR_REACH_MAX_SIZE(false, "The array has reached maximum size which is " + cf::num2str(Core::MAX_NUM_ARRAY_ELM));
    const ExitStatus FAIL_ARR_REACH_MAX_SIZE_CAPA(false, "The array has reached maximum size");

    const ExitStatus FAIL_HT_SIZE_OOB(false, "M is out of bounds: Allow from 1 to " + cf::num2str(Core::MAX_NUM_HT_HOR_ELM));
    const ExitStatus FAIL_HT_REACH_MAX_VER_SIZE(false, "The coresponding chain has reached maximum size which is " + cf::num2str(Core::MAX_NUM_HT_VER_ELM));
    const ExitStatus FAIL_HT_NUM_OOB(false, "N is out of bounds: Allow from 0 to Mx" + cf::num2str(Core::MAX_NUM_HT_VER_ELM));

    const ExitStatus FAIL_AVL_SIZE_OOB(false, "Size is out of bounds: Allow from 0 to " + cf::num2str(Core::MAX_NUM_AVL_ELM));
    const ExitStatus FAIL_AVL_REACH_MAX_SIZE(false, "The AVL Tree has reached maximum size which is " + cf::num2str(Core::MAX_NUM_AVL_ELM));

    const ExitStatus FAIL_HEAP_EMPTY(false, "The heap is empty");
    const ExitStatus FAIL_HEAP_SIZE_OOB(false, "Size is out of bounds: Allow from 0 to " + cf::num2str(Core::MAX_NUM_HEAP_ELM));
    const ExitStatus FAIL_HEAP_REACH_MAX_SIZE(false, "The Heap has reached maximum size which is " + cf::num2str(Core::MAX_NUM_HEAP_ELM));
    
    const ExitStatus FAIL_TRIE_SIZE_OOB(false, "Size is out of bounds: Allow from 0 to " + cf::num2str(Core::MAX_NUM_TRIE_ELM));
    const ExitStatus FAIL_TRIE_LEN_OOB(false, "String length is out of bounds: Allow from 1 to " + cf::num2str(Core::MAX_LEN_TRIE_ELM));
    const ExitStatus FAIL_TRIE_REACH_MAX_SIZE(false, "The Trie has reached maximum size which is " + cf::num2str(Core::MAX_NUM_TRIE_ELM));

    const ExitStatus FAIL_234_SIZE_OOB(false, "Size is out of bounds: Allow from 0 to " + cf::num2str(Core::MAX_NUM_234_ELM));
    const ExitStatus FAIL_234_REACH_MAX_SIZE(false, "The 234 Tree has reached maximum size which is " + cf::num2str(Core::MAX_NUM_234_ELM));

    const ExitStatus FAIL_GRAPH_NNODE_OOB(false, "Number of node is out of bounds: Allow from 1 to " + cf::num2str(Core::MAX_NUM_GRAPH_NODE));
    const ExitStatus FAIL_GRAPH_NEDGE_OOB(false, "Number of edge is out of bounds: Allow from 0 to " + cf::num2str(Core::MAX_NUM_GRAPH_EDGE));
    const ExitStatus FAIL_GRAPH_NODE_LABEL_OOB(false, "Node label is out of bounds");
}

#endif
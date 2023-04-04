#ifndef LIST_OF_OPERATIONS_GROUPS_CPP
#define LIST_OF_OPERATIONS_GROUPS_CPP

#include "ListOfOperationsGroups.h"

template<typename T>
ListOfOperationsGroups<T>::ListOfOperationsGroups() {
    mainObj = nullptr;    
    curOper = 0;
}

template<typename T>
void ListOfOperationsGroups<T>::setMainObj(T* _mainObj) {
    mainObj = _mainObj;
}


template<typename T>
void ListOfOperationsGroups<T>::pushBackGroup(const OperationsGroups<T> &g) {
    groups.push_back(g);
}

template<typename T>
ExitStatus ListOfOperationsGroups<T>::runNext(Codeblock* codeblock) {
    if (curOper+1 < (int)groups.size()) {
        curOper++;
        runAt(curOper, codeblock);
        return ExitStatus(true, "");
    } 
    return ExitStatus(false, "");
}

template<typename T>
ExitStatus ListOfOperationsGroups<T>::runPrev(Codeblock* codeblock) {
    if (curOper-1 >= 0) {
        curOper--;
        runAt(curOper, codeblock);
        return ExitStatus(true, "");
    }
    return ExitStatus(false, "");
}

template<typename T>
void ListOfOperationsGroups<T>::run(Codeblock* codeblock) {
    // std::cerr << "ALOG run ------------- \n";
    // std::cerr << "ALOG size " << groups.size() << '\n';
    if (!groups.empty()) {
        curOper = 0;
        groups[0].run(mainObj, false, codeblock);
        for (curOper = 1; curOper < (int)groups.size(); ++curOper) {
            // groups[curOper].run(mainObj, true, codeblock);
            groups[curOper].run(mainObj, false, codeblock);
        }
        groups[0].passObj(mainObj);
    }
}



template<typename T>
void ListOfOperationsGroups<T>::runAt(int id, Codeblock* codeblock) {
    assert(0 <= id && id < (int)groups.size());
    groups[id].run(mainObj, false, codeblock);
    groups[id].passObj(mainObj);
}

template<typename T>
void ListOfOperationsGroups<T>::clearGroup() {
    for (int i = 0; i < (int)groups.size(); ++i) {
        groups[i].destroy();
    }
    groups.clear();
}

template<typename T>
void ListOfOperationsGroups<T>::destroy() {
    mainObj->destroy();
    clearGroup();
}

#endif
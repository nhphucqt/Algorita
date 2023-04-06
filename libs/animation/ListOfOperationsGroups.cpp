#ifndef LIST_OF_OPERATIONS_GROUPS_CPP
#define LIST_OF_OPERATIONS_GROUPS_CPP

#include "ListOfOperationsGroups.h"

template<typename T>
ListOfOperationsGroups<T>::ListOfOperationsGroups() {
    mainObj = nullptr;    
    iter = groups.end();
}

template<typename T>
typename std::list<OperationsGroups<T>>::iterator ListOfOperationsGroups<T>::curGroup() const {
    return prev(iter);
}


template<typename T>
void ListOfOperationsGroups<T>::setMainObj(T* _mainObj) {
    mainObj = _mainObj;
}

template<typename T>
void ListOfOperationsGroups<T>::addNewGroup() {
    groups.push_front(OperationsGroups<T>());
    groups.front().resetOperCur();
    std::cerr << "LOG::addNewGroup -> iter end " << (iter == groups.end()) << '\n';
    std::cerr << "LOG::addNewGroup -> iter end " << (groups.front().opers.iter == groups.front().opers.q.end()) << '\n';
}

template<typename T>
OperationsGroups<T>* ListOfOperationsGroups<T>::backGroup() {
    return &(*groups.begin());
}

template<typename T>
ExitStatus ListOfOperationsGroups<T>::runPrev(Codeblock* codeblock) {
    if (iter != groups.end()) {
        iter++;
        runAt(curGroup(), codeblock);
        return ExitStatus(true, "");
    }
    return ExitStatus(false, "");
}

template<typename T>
ExitStatus ListOfOperationsGroups<T>::runNext(Codeblock* codeblock) {
    if (curGroup() != groups.begin()) {
        iter--;
        runAt(curGroup(), codeblock);
        return ExitStatus(true, "");
    }
    return ExitStatus(false, "");
}

template<typename T>
void ListOfOperationsGroups<T>::run(Codeblock* codeblock) {
    // std::cerr << "ALOG run ------------- \n";
    // std::cerr << "ALOG size " << groups.size() << '\n';
    if (iter != groups.begin()) {
    // if (0 <= curOper && curOper < (int)groups.size()) {
        std::cerr << " >> Running curOper\n";
        if (curGroup()->run()) {
            if (*curGroup()->getIsReversed()) {
                iter++;
            } else {
                iter--;
            }
        }
    }
}



template<typename T>
void ListOfOperationsGroups<T>::runAt(int id, Codeblock* codeblock) {
    assert(0 <= id && id < (int)groups.size());
    typename std::list<OperationsGroups<T>>::iterator curr = groups.begin();
    while (id--) {
        curr++;
    }
    curr->run();
    curr->passStaObj(mainObj);
}

template<typename T>
void ListOfOperationsGroups<T>::runAt(typename std::list<OperationsGroups<T>>::iterator id, Codeblock* codeblock) {
    // assert(0 <= id && id < (int)groups.size());
    // typename std::list<OperationsGroups<T>>::iterator curr = groups.begin();
    // while (id--) {
    //     curr++;
    // }
    id->run();
    id->passStaObj(mainObj);
}

template<typename T>
void ListOfOperationsGroups<T>::clearGroup() {
    for (typename std::list<OperationsGroups<T>>::iterator curr = groups.begin(); curr != groups.end(); ++curr) {
        curr->destroy();
    }
    groups.clear();
    iter = groups.end();
}

template<typename T>
void ListOfOperationsGroups<T>::destroy() {
    mainObj->destroy();
    clearGroup();
}

#endif
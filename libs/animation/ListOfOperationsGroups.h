#ifndef LIST_OF_OPERATIONS_GROUPS_H
#define LIST_OF_OPERATIONS_GROUPS_H

// #include <vector>
#include <list>

#include "animation.h"
#include "OperationsGroups.h"
#include "../graphic/gui/Codeblock.h"
#include "../core/ExitStatus.h"

template<typename T>
class ListOfOperationsGroups {
// public:
private:
    T* mainObj;
    std::list<OperationsGroups<T>> groups;
    typename std::list<OperationsGroups<T>>::iterator iter;

public:
    ListOfOperationsGroups();

    typename std::list<OperationsGroups<T>>::iterator curGroup() const;

    void run(Codeblock* codeblock = nullptr);
    void runAt(int id, Codeblock* codeblock = nullptr);
    void runAt(typename std::list<OperationsGroups<T>>::iterator id, Codeblock* codeblock);

    void setMainObj(T* _mainObj);

    void addNewGroup();

    OperationsGroups<T>* backGroup();

    ExitStatus runNext(Codeblock* codeblock = nullptr);
    ExitStatus runPrev(Codeblock* codeblock = nullptr);

    void clearGroup();

    void destroy();
};

#include "ListOfOperationsGroups.cpp"
#endif
#ifndef LIST_OF_OPERATIONS_GROUPS_H
#define LIST_OF_OPERATIONS_GROUPS_H

#include <vector>

#include "animation.h"
#include "OperationsGroups.h"
#include "../graphic/gui/Codeblock.h"
#include "../core/ExitStatus.h"

template<typename T>
class ListOfOperationsGroups {
// private:
public:
    T* mainObj;
    std::vector<OperationsGroups<T>> groups;
    int curOper;

public:
    ListOfOperationsGroups();

    void run(Codeblock* codeblock = nullptr);
    void runAt(int id, Codeblock* codeblock = nullptr);

    void setMainObj(T* _mainObj);
    void pushBackGroup(const OperationsGroups<T> &g);

    ExitStatus runNext(Codeblock* codeblock = nullptr);
    ExitStatus runPrev(Codeblock* codeblock = nullptr);

    void clearGroup();

    void destroy();
};

#include "ListOfOperationsGroups.cpp"
#endif
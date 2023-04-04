#ifndef OPERATIONS_GROUPS_H
#define OPERATIONS_GROUPS_H

#include <list>
#include <functional>

#include "animation.h"
#include "../graphic/gui/Codeblock.h"

template<typename T>
class OperationsGroups {
// private:
public:
    T obj;
    std::list<std::function<void()>> opers;
    std::vector<int> highlightLines;

public:
    OperationsGroups();
    
    void setObj(T* _obj);
    void pushBackFunc(std::function<void()> f);
    void setHighlightLines(const std::vector<int> &highlight);

    bool passHighlightLines(Codeblock* codeblock) const;
    void pushHighlightLines(Codeblock* codeblock) const;

    void reset();
    void clearFunc();

    bool passObj(T *dest) const;

    void run(T* mainObj, bool keep, Codeblock* codeblock = nullptr) const;
    void destroy();
};

#include "OperationsGroups.cpp"
#endif
#ifndef OPERATIONS_GROUPS_H
#define OPERATIONS_GROUPS_H

#include <list>
#include <functional>

#include "animation.h"
#include "../graphic/gui/Codeblock.h"

template<typename T>
class OperationsGroups {
public:
// private:
    T staObj, finObj;
    std::vector<int> highlightLines;
    Animate::QueueOfScenes opers;

public:
    OperationsGroups();
    
    void resetOperCur();

    void setStaObj(T* _obj);
    bool passStaObj(T *dest);
    void pushStaObj(T* _obj);
    
    void setFinObj(T* _obj);
    bool passFinObj(T *dest);
    void pushFinObj(T* _obj);

    void pushNew(const std::function<bool()> &f);
    void pushBack(const std::function<bool()> &f);
    void pushBlank();

    void setHighlightLines(const std::vector<int> &highlight);
    bool passHighlightLines(Codeblock* codeblock) const;
    void pushHighlightLines(const std::vector<int> &highlight, Codeblock* codeblock);

    void reset();
    void clearFunc();


    void setReverse(bool _r);

    double* getCurrTime();
    bool* getIsReversed();

    bool run();
    void destroy();
};

#include "OperationsGroups.cpp"
#endif
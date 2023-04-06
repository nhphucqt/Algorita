#ifndef OPERATIONS_GROUPS_CPP
#define OPERATIONS_GROUPS_CPP

#include "OperationsGroups.h"

template<typename T>
OperationsGroups<T>::OperationsGroups() {
    highlightLines = std::vector<int>();
    opers = Animate::QueueOfScenes();
    opers.resetCur();
    std::cerr << "OG::() resetcur " << (opers.q.end() == opers.iter) << '\n';
}

template<typename T>
void OperationsGroups<T>::resetOperCur() {
    opers.resetCur();
}

template<typename T>
void OperationsGroups<T>::setStaObj(T* _obj) {
    staObj.makeCopy(_obj);
}

template<typename T>
bool OperationsGroups<T>::passStaObj(T* dest) {
    dest->makeCopy(&staObj);
    if (dest->pHead != nullptr) {
        std::cerr << "OG::passStaObj -> dest x,y " << dest->pHead->x << ' ' << dest->pHead->y << '\n';
    }
    return true;
}

template<typename T>
void OperationsGroups<T>::pushStaObj(T* _obj) {
    setStaObj(_obj);
    pushNew(std::bind(&passStaObj, this, _obj));
}

template<typename T>
void OperationsGroups<T>::setFinObj(T* _obj) {
    finObj.makeCopy(_obj);
}

template<typename T>
bool OperationsGroups<T>::passFinObj(T* dest) {
    dest->makeCopy(&finObj);
    return true;
}

template<typename T>
void OperationsGroups<T>::pushFinObj(T* _obj) {
    setFinObj(_obj);
    pushNew(std::bind(&passFinObj, this, _obj));
}

template<typename T>
void OperationsGroups<T>::pushNew(const std::function<bool()> &f) {
    opers.pushToNewScene(f);
}

template<typename T>
void OperationsGroups<T>::pushBack(const std::function<bool()> &f) {
    opers.pushToBackScene(f);
}

template<typename T>
void OperationsGroups<T>::pushBlank() {
    opers.addBlankScene();
}


template<typename T>
void OperationsGroups<T>::setHighlightLines(const std::vector<int> &highlight) {
    highlightLines = highlight;
}

template<typename T>
bool OperationsGroups<T>::passHighlightLines(Codeblock* codeblock) const {
    codeblock->setHighlight(highlightLines);
    return true;
}

template<typename T>
void OperationsGroups<T>::pushHighlightLines(const std::vector<int> &highlight, Codeblock* codeblock) {
    setHighlightLines(highlight);
    pushNew(std::bind(&passHighlightLines, this, codeblock));
}


template<typename T>
void OperationsGroups<T>::reset() {
    staObj.destroy();
    finObj.destroy();
    clearFunc();
}

template<typename T>
void OperationsGroups<T>::clearFunc() {
    opers.clearScenes();
}

template<typename T>
void OperationsGroups<T>::setReverse(bool _r) {
    opers.setReverse(_r);
}

template<typename T>
double* OperationsGroups<T>::getCurrTime() {
    return &opers.currTime;
}

template<typename T>
bool* OperationsGroups<T>::getIsReversed() {
    return &opers.isReversed;
}

template<typename T>
bool OperationsGroups<T>::run() {
    return opers.run();
}

template<typename T>
void OperationsGroups<T>::destroy() {
    staObj.destroy();
    finObj.destroy();
    highlightLines.clear();
    opers.clearScenes();
}

#endif
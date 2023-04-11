#ifndef OPERATIONS_GROUPS_CPP
#define OPERATIONS_GROUPS_CPP

#include "OperationsGroups.h"

template<typename T>
OperationsGroups<T>::OperationsGroups() {
    highlightLines = std::vector<int>();
    opers = Animate::QueueOfScenes();
    // std::cerr << "OG::() resetcur " << (opers.q.end() == opers.iter) << '\n';
}

template<typename T>
void OperationsGroups<T>::push(const std::function<bool()> &f) {
    opers.push(f);
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
    clearFunc();
}

template<typename T>
void OperationsGroups<T>::clearFunc() {
    opers.clearScenes();
}

template<typename T>
bool OperationsGroups<T>::run() {
    return opers.run();
}

template<typename T>
void OperationsGroups<T>::destroy() {
    highlightLines.clear();
    opers.clearScenes();
}

#endif
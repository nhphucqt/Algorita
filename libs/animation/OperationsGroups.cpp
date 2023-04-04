#ifndef OPERATIONS_GROUPS_CPP
#define OPERATIONS_GROUPS_CPP

#include "OperationsGroups.h"

template<typename T>
OperationsGroups<T>::OperationsGroups() {}

template<typename T>
void OperationsGroups<T>::setObj(T* _obj) {
    obj.makeCopy(*_obj);
    // std::cerr << "OG::setObj -> x : ";
    // for (auto curr = obj.pHead; curr != nullptr; curr = curr->pNext) {
    //     std::cerr << curr->x << ' ';
    // }
    // std::cerr << '\n';
}

template<typename T>
void OperationsGroups<T>::pushBackFunc(std::function<void()> f) {
    opers.push_back(f);
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
void OperationsGroups<T>::pushHighlightLines(Codeblock* codeblock) const {
    Animate::queueOfScenes.pushToNewScene(std::bind(&passHighlightLines, this, codeblock));
}


template<typename T>
void OperationsGroups<T>::reset() {
    obj = T();
    clearFunc();
}

template<typename T>
void OperationsGroups<T>::clearFunc() {
    opers.clear();
}

template<typename T>
bool OperationsGroups<T>::passObj(T *dest) const {
    dest->makeCopy(obj);
    return true;
}

template<typename T>
void OperationsGroups<T>::run(T* mainObj, bool keep, Codeblock* codeblock) const {
    if (!keep) {
        Animate::queueOfScenes.pushToNewScene(std::bind(passObj, this, mainObj));
    }
    // std::cerr << "OG size " << opers.size() << '\n';
    // std::cerr << "OG::run -> obj x : ";
    // for (auto curr = obj.pHead; curr != nullptr; curr = curr->pNext) {
    //     std::cerr << curr->x << ' ';
    // }
    if (codeblock != nullptr) {
        pushHighlightLines(codeblock);
    }
    for (std::list<std::function<void()>>::const_iterator func = opers.begin(); func != opers.end(); ++func) {
        // std::cerr << " >> OG::run\n";
        (*func)();
    }    
}

template<typename T>
void OperationsGroups<T>::destroy() {
    obj.destroy();
    highlightLines.clear();
    opers.clear();
}

#endif
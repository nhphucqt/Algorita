#ifndef LIST_OF_OPERATIONS_GROUPS_CPP
#define LIST_OF_OPERATIONS_GROUPS_CPP

#include "ListOfOperationsGroups.h"

template<typename T>
ListOfOperationsGroups<T>::ListOfOperationsGroups() {
    mainObj = nullptr;    
    iter = groups.end();
    isReversed = false;
    isPaused = false;
    runType = Animate::RUN_ALL;
    currTime = 0.0;
}

template<typename T>
double* ListOfOperationsGroups<T>::getCurrTime() {
    return &currTime;
}

template<typename T>
bool* ListOfOperationsGroups<T>::getIsReversed() {
    return &isReversed;
}

template<typename T>
typename std::list<OperationsGroups<T>>::iterator ListOfOperationsGroups<T>::curGroup() const {
    return groups.empty() || isReversed ? iter : prev(iter);
}


template<typename T>
void ListOfOperationsGroups<T>::setMainObj(T* _mainObj) {
    mainObj = _mainObj;
}

template<typename T>
void ListOfOperationsGroups<T>::loadCode(const std::string &path) {
    codeblock.load(path);
    std::cerr << "LOG::loadCode lines.size() = " << codeblock.lines.size() << '\n';
}

template<typename T>
void ListOfOperationsGroups<T>::updateCode() {
    if (isReversed && iter != groups.end()) {
        if (next(curGroup()) != groups.end()) {
            next(curGroup())->passHighlightLines(&codeblock);
        } else {
            codeblock.resetHighlight();
        }
    } else if (!isReversed && iter != groups.begin()) {
        curGroup()->passHighlightLines(&codeblock);
    }
}

template<typename T>
void ListOfOperationsGroups<T>::resetCode() {
    codeblock.reset();
}

template<typename T>
void ListOfOperationsGroups<T>::addNewGroup() {
    groups.push_front(OperationsGroups<T>());
    // std::cerr << "LOG::addNewGroup -> iter end " << (iter == groups.end()) << '\n';
    // std::cerr << "LOG::addNewGroup -> iter end " << (groups.front().opers.iter == groups.front().opers.q.end()) << '\n';
}

template<typename T>
OperationsGroups<T>* ListOfOperationsGroups<T>::backGroup() {
    return &(*groups.begin());
}

template<typename T>
ExitStatus ListOfOperationsGroups<T>::runPrev(Animate::RunType rt) {
    isPaused = false;
    runType = rt;
    std::cerr << "LOG::runPrev -> isReversed = " << isReversed << '\n';
    if (isReversed) {
        if (iter == groups.end()) {
            std::cerr << "LOG::runPrev -> iter == groups.end()\n";
            return ExitStatus(false, "");
        } 
        if (canRunScene()) {
            std::cerr << "LOG::runPrev -> canRunScene\n";
            return ExitStatus(false, "");
        }
        iter++;
        resetCurrTime();
        updateCode();
        return ExitStatus(true, "");
    }
    isReversed = true;
    if (iter == groups.begin()) {
        std::cerr << "LOG::runPrev -> iter == groups.begin()\n";
        resetCurrTime();
        updateCode();
        return ExitStatus(true, "");
    }
    std::cerr << "LOG::runPrev -> iter != groups.begin()\n";
    iter--;
    updateCode();
    return ExitStatus(true, "");
}

template<typename T>
ExitStatus ListOfOperationsGroups<T>::runNext(Animate::RunType rt) {
    isPaused = false;
    runType = rt;
    std::cerr << "LOG::runNext -> isReversed = " << isReversed << '\n';
    if (!isReversed) {
        if (iter == groups.begin()) {
            std::cerr << "LOG::runNext -> iter == groups.begin()\n";
            return ExitStatus(false, "");
        }
        if (canRunScene()) {
            std::cerr << "LOG::runNext -> canRunScene()\n";
            return ExitStatus(false, "");
        }
        iter--;
        resetCurrTime();
        updateCode();
        return ExitStatus(true, "");
    }
    isReversed = false;
    if (iter == groups.end()) {
        std::cerr << "LOG::runNext -> iter == group.end()\n";
        assert(iter != groups.begin());
        resetCurrTime();
        updateCode();
        return ExitStatus(true, "");
    }
    std::cerr << "LOG::runNext -> iter != group.end()\n";
    iter++;
    updateCode();
    return ExitStatus(true, "");
}

template<typename T>
void ListOfOperationsGroups<T>::build() {
    assert(iter == groups.end());
    curGroup()->passHighlightLines(&codeblock);
}

template<typename T>
void ListOfOperationsGroups<T>::updateCurrTime() {
    currTime += isReversed ? -Animate::elapseTime : +Animate::elapseTime;
}

template<typename T>
void ListOfOperationsGroups<T>::resetCurrTime() {
    currTime = isReversed ? Animate::ANIMATE_TIME : 0.0;
}

template<typename T>
bool ListOfOperationsGroups<T>::canRunOper() const {
    return (isReversed && iter != groups.end()) || (!isReversed && iter != groups.begin());
}

template<typename T>
bool ListOfOperationsGroups<T>::canRunScene() const {
    return (isReversed && currTime > 0.0) || (!isReversed && currTime < Animate::ANIMATE_TIME);
}

template<typename T>
bool ListOfOperationsGroups<T>::run() {
    // std::cerr << "LOG::run() -> " << isReversed << ' ' << isPaused << ' ' << runType << '\n';
    // std::cerr << "ALOG run ------------- \n";
    // std::cerr << "ALOG size " << groups.size() << '\n';

    if (runType == Animate::RUN_ALL) {
        if (!canRunOper()) {
            return true;
        }
        // std::cerr << "LOG::run() -> prev currTime = " << currTime << '\n';
        updateCurrTime();
        // std::cerr << "LOG::run() -> curr currTime = " << currTime << '\n';
        // std::cerr << " >> Running curOper\n";
        if (curGroup()->run()) {
            if (isReversed) {
                iter++;
                if (iter != groups.end()) {
                    if (next(curGroup()) != groups.end()) {
                        next(curGroup())->passHighlightLines(&codeblock);
                    } else {
                        codeblock.resetHighlight();
                    }
                }
            } else {
                iter--;
                if (iter != groups.begin()) {
                    curGroup()->passHighlightLines(&codeblock);
                }
            }
            resetCurrTime();
        }
        return false;
    }
    if (runType == Animate::RUN_STEP) {
        // std::cerr << "LOG::run -> iter == begin() " << (iter == groups.begin()) << '\n';
        // std::cerr << "LOG::run -> isReversed " << isReversed << '\n';
        // std::cerr << "LOG::run -> curG->canRun " << (curGroup()->canRun(isReversed)) << '\n';
        if (!canRunOper()) {
            return true;
        }
        if (!canRunScene()) {
            return true;
        }
        updateCurrTime();
        curGroup()->run();
        return false;
    }
    std::cerr << "runType = " << runType << '\n';
    assert(false);
    return false;
}

template<typename T>
ExitStatus ListOfOperationsGroups<T>::toFirstState() {
    runPrev(Animate::RUN_ALL);
    while (!run());
    return ExitStatus(true, "");
}

template<typename T>
ExitStatus ListOfOperationsGroups<T>::toLastState() {
    runNext(Animate::RUN_ALL);
    while (!run());
    return ExitStatus(true, "");
}


template<typename T>
void ListOfOperationsGroups<T>::clearGroup() {
    toLastState();
    for (typename std::list<OperationsGroups<T>>::iterator curr = groups.begin(); curr != groups.end(); ++curr) {
        curr->destroy();
    }
    groups.clear();
    iter = groups.end();
    runType = Animate::RUN_ALL;
    isReversed = false;
    isPaused = false;
    codeblock.reset();
}

template<typename T>
void ListOfOperationsGroups<T>::draw() {
    codeblock.draw(Window::DIMENSION - codeblock.getBlockDimension());
}

template<typename T>
void ListOfOperationsGroups<T>::destroy() {
    mainObj->destroy();
    clearGroup();
}

template<typename T>
void ListOfOperationsGroups<T>::animateDelay() {
    backGroup()->push(std::bind(&Animate::delay, &currTime, &isReversed));
}

template<typename T> 
template<typename OT>
void ListOfOperationsGroups<T>::animateFadeIn(OT* obj) {
    backGroup()->push(std::bind(&Animate::fadeIn<OT>, obj, &currTime, &isReversed));
}

template<typename T>
template<typename OT>
void ListOfOperationsGroups<T>::animateFadeOut(OT* obj) {
    backGroup()->push(std::bind(&Animate::fadeOut<OT>, obj, &currTime, &isReversed));
}

template<typename T>
template<typename OT>
void ListOfOperationsGroups<T>::animateFocus(OT* obj) {
    backGroup()->push(std::bind(&Animate::focus<OT>, obj, &currTime, &isReversed));
}

template<typename T>
template<typename OT>
void ListOfOperationsGroups<T>::animateUnfocus(OT* obj) {
    backGroup()->push(std::bind(&Animate::unfocus<OT>, obj, &currTime, &isReversed));
}

template<typename T>
template<typename OT>
void ListOfOperationsGroups<T>::animateFocusBorder(OT* obj) {
    backGroup()->push(std::bind(&Animate::focusBorder<OT>, obj, &currTime, &isReversed));
}

template<typename T>
template<typename OT>
void ListOfOperationsGroups<T>::animateUnfocusBorder(OT* obj) {
    backGroup()->push(std::bind(&Animate::unfocusBorder<OT>, obj, &currTime, &isReversed));
}

template<typename T>
template<typename OT> 
void ListOfOperationsGroups<T>::animateDisplace(OT* obj, int Sx, int Sy, int Dx, int Dy) {
    backGroup()->push(std::bind(&Animate::displace<OT>, obj, 0, 0, 1, 1, &currTime, &isReversed));
}

template<typename T>
template<typename OT> 
void ListOfOperationsGroups<T>::animateTransform(OT* obj, int Sx, int Sy, int Tx, int Ty) {
    backGroup()->push(std::bind(&Animate::transform<OT>, obj, Sx, Sy, Tx, Ty, &currTime, &isReversed));
}

template<typename T>
template<typename OT>
void ListOfOperationsGroups<T>::animateSlideIn(OT* obj) {
    backGroup()->push(std::bind(&Animate::slideIn<OT>, obj, &currTime, &isReversed));
}

template<typename T>
template<typename OT>
void ListOfOperationsGroups<T>::animateSlideOut(OT* obj) {
    backGroup()->push(std::bind(&Animate::slideOut<OT>, obj, &currTime, &isReversed));
}

template<typename T>
template<typename OT> 
void ListOfOperationsGroups<T>::animateRedirect(OT* A, OT* C) {
    backGroup()->push(std::bind(&Animate::redirect<OT>, A, C, &currTime, &isReversed));
}


template<typename T>
template<typename OT, typename MT>
void ListOfOperationsGroups<T>::animateAppearAllNodes(OT* obj) {
    backGroup()->push(std::bind(&Animate::fadeInAllNodes<OT, MT>, obj, &currTime, &isReversed));
}

template<typename T>
template<typename OT, typename MT>
void ListOfOperationsGroups<T>::animateVanishAllNodes(OT* obj) {
    backGroup()->push(std::bind(&Animate::fadeOutAllNodes<OT, MT>, obj, &currTime, &isReversed));
}

template<typename T>
template<typename OT, typename MT>
void ListOfOperationsGroups<T>::animateUnfocusAllNodes(OT* obj) {
    backGroup()->push(std::bind(&Animate::unfocusAllNodes<OT, MT>, obj, &currTime, &isReversed));
}



#endif
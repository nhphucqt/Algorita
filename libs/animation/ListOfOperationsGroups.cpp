#ifndef LIST_OF_OPERATIONS_GROUPS_CPP
#define LIST_OF_OPERATIONS_GROUPS_CPP

#include "ListOfOperationsGroups.h"

template<typename T>
ListOfOperationsGroups<T>::ListOfOperationsGroups() {
    mainObj = nullptr;    
    iter = groups.end();
    isReversed = false;
    runType = Animate::RUN_ALL;
    currTime = 0.0;
    speed = 1.0;
    progress = 0;
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
    // std::cerr << "LOG::loadCode lines.size() = " << codeblock.lines.size() << '\n';
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
    if (groups.empty()) {
        return ExitStatus(false, "");
    }
    runType = rt;
    // std::cerr << "LOG::runPrev() -> isReversed = " << isReversed << '\n';
    // std::cerr << "LOG::runPrev() -> iter == groups.begin() = " << (iter == groups.begin()) << '\n';
    // std::cerr << "LOG::runPrev() -> iter == groups.end() = " << (iter == groups.end()) << '\n';
    // std::cerr << "LOG::runPrev() -> progress = " << getProgress() << '\n';
    if (isReversed) {
        if (iter == groups.end()) {
            // std::cerr << "LOG::runPrev -> iter == groups.end()\n";
            return ExitStatus(false, "");
        } 
        if (canRunScene()) {
            // std::cerr << "LOG::runPrev -> canRunScene\n";
            return ExitStatus(false, "");
        }
        iter++;
        resetCurrTime();
        updateCode();
        return ExitStatus(true, "");
    }
    isReversed = true;
    if (iter == groups.begin()) {
        // std::cerr << "LOG::runPrev -> iter == groups.begin()\n";
        resetCurrTime();
        updateCode();
        return ExitStatus(true, "");
    }
    // std::cerr << "LOG::runPrev -> iter != groups.begin()\n";
    iter--;
    if (currTime >= Animate::ANIMATE_TIME) {
        resetCurrTime();
    }
    updateCode();
    return ExitStatus(true, "");
}

template<typename T>
ExitStatus ListOfOperationsGroups<T>::runNext(Animate::RunType rt) {
    if (groups.empty()) {
        return ExitStatus(false, "");
    }
    runType = rt;
    // std::cerr << "LOG::runNext() -> isReversed = " << isReversed << '\n';
    // std::cerr << "LOG::runNext() -> iter == groups.begin() = " << (iter == groups.begin()) << '\n';
    // std::cerr << "LOG::runNext() -> iter == groups.end() = " << (iter == groups.end()) << '\n';
    // std::cerr << "LOG::runNext() -> progress = " << getProgress() << '\n';
    if (!isReversed) {
        if (iter == groups.begin()) {
            // std::cerr << "LOG::runNext -> iter == groups.begin()\n";
            return ExitStatus(false, "");
        }
        if (canRunScene()) {
            // std::cerr << "LOG::runNext -> canRunScene()\n";
            return ExitStatus(false, "");
        }
        iter--;
        resetCurrTime();
        updateCode();
        return ExitStatus(true, "");
    }
    isReversed = false;
    if (iter == groups.end()) {
        // std::cerr << "LOG::runNext -> iter == group.end()\n";
        assert(iter != groups.begin());
        resetCurrTime();
        updateCode();
        return ExitStatus(true, "");
    }
    // std::cerr << "LOG::runNext -> iter != group.end()\n";
    iter++;
    updateCode();
    if (currTime < 0) {
        resetCurrTime();
    }
    return ExitStatus(true, "");
}

template<typename T>
ExitStatus ListOfOperationsGroups<T>::toggleRun() {
    if (runType == Animate::RUN_ALL) {
        runType = Animate::RUN_STEP;
    } else if (runType == Animate::RUN_STEP) {
        runNext(Animate::RUN_ALL);
        // runType = Animate::RUN_ALL;
    }
    return ExitStatus(true, "");
}

template<typename T>
void ListOfOperationsGroups<T>::build() {
    assert(iter == groups.end());
    curGroup()->passHighlightLines(&codeblock);
}

template<typename T>
void ListOfOperationsGroups<T>::updateCurrTime() {
    currTime += (isReversed ? -Animate::elapseTime : +Animate::elapseTime) * speed;
}

template<typename T>
void ListOfOperationsGroups<T>::resetCurrTime() {
    currTime = isReversed ? Animate::ANIMATE_TIME : 0.0;
}

template<typename T>
void ListOfOperationsGroups<T>::updateProgress() {
    progress += isReversed ? -1 : +1;
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
            updateProgress();
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
        // std::cerr << "ALOG::run() -> curTime = " << currTime << '\n';
        if (curGroup()->run()) {
            updateProgress();
        }
        // std::cerr << "ALOG::run() -> isReversed getProgress() -> " << isReversed << ' ' << getProgress() << ' ' << groups.size() << '\n';
        return false;
    }
    // std::cerr << "runType = " << runType << '\n';
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
    progress = 0;
    groups.clear();
    iter = groups.end();
    runType = Animate::RUN_ALL;
    isReversed = false;
    codeblock.reset();
}

template<typename T>
double ListOfOperationsGroups<T>::closestSpeed(double s) {
    double res = SPEED_SIGNATURE[0];
    double mins = fabs(SPEED_SIGNATURE[0] - s);
    for (int i = 1; i < NUM_SPEED; ++i) {
        if (mins > fabs(SPEED_SIGNATURE[i] - s)) {
            mins = fabs(SPEED_SIGNATURE[i] - s);
            res = SPEED_SIGNATURE[i];
        }
    }
    return res;
}

template<typename T>
double ListOfOperationsGroups<T>::getProgress() {
    return progress;
}

template<typename T>
void ListOfOperationsGroups<T>::draw() {
    codeblock.draw(Window::DIMENSION - toVector2(0, Layout::BOTTOM_HEIGHT) - codeblock.getBlockDimension());
    float posX = Window::WIDTH - Gui::LOG_SPEED_SIGN_WIDTH;
    GuiLabel(Rectangle{posX, Window::HEIGHT - Gui::LOG_SPEED_SIGN_HEIGHT, Gui::LOG_SPEED_SIGN_WIDTH, Gui::LOG_SPEED_SIGN_HEIGHT}, (" " + cf::double2str(speed) + "x").c_str());
    posX -= Gui::LOG_SLIDER_WIDTH;
    speed = closestSpeed(GuiSlider(Rectangle{posX, Window::HEIGHT - Gui::LOG_SLIDER_HEIGHT - (Layout::BOTTOM_HEIGHT - Gui::LOG_SLIDER_HEIGHT) / 2.0, Gui::LOG_SLIDER_WIDTH, Gui::LOG_SLIDER_HEIGHT}, "", "", speed, SPEED_SIGNATURE[0], SPEED_SIGNATURE[NUM_SPEED-1]));
    posX -= 10 + Gui::LOG_SLIDER_BAR_WIDTH;
    GuiSliderBar(Rectangle{posX, Window::HEIGHT - Gui::LOG_SLIDER_BAR_HEIGHT - (Layout::BOTTOM_HEIGHT - Gui::LOG_SLIDER_BAR_HEIGHT) / 2.0, Gui::LOG_SLIDER_BAR_WIDTH, Gui::LOG_SLIDER_BAR_HEIGHT}, "", "", getProgress(), 0, (int)groups.size());
    posX -= 10 + Gui::LOG_NAV_BUTTON_WIDTH;
    if (GuiButton(Rectangle{posX, Window::HEIGHT - Gui::LOG_NAV_BUTTON_HEIGHT - (Layout::BOTTOM_HEIGHT - Gui::LOG_NAV_BUTTON_HEIGHT) / 2.0, Gui::LOG_NAV_BUTTON_WIDTH, Gui::LOG_NAV_BUTTON_HEIGHT}, ">|")) {
        toLastState();
    }
    posX -= 2 + Gui::LOG_NAV_BUTTON_WIDTH;
    if (GuiButton(Rectangle{posX, Window::HEIGHT - Gui::LOG_NAV_BUTTON_HEIGHT - (Layout::BOTTOM_HEIGHT - Gui::LOG_NAV_BUTTON_HEIGHT) / 2.0, Gui::LOG_NAV_BUTTON_WIDTH, Gui::LOG_NAV_BUTTON_HEIGHT}, ">") || IsKeyDown(KEY_RIGHT)) {
        runNext(Animate::RUN_STEP);
    }
    posX -= 2 + Gui::LOG_NAV_BUTTON_WIDTH;
    if (GuiButton(Rectangle{posX, Window::HEIGHT - Gui::LOG_NAV_BUTTON_HEIGHT - (Layout::BOTTOM_HEIGHT - Gui::LOG_NAV_BUTTON_HEIGHT) / 2.0, Gui::LOG_NAV_BUTTON_WIDTH, Gui::LOG_NAV_BUTTON_HEIGHT}, "||")) {
        toggleRun();
    }
    posX -= 2 + Gui::LOG_NAV_BUTTON_WIDTH;
    if (GuiButton(Rectangle{posX, Window::HEIGHT - Gui::LOG_NAV_BUTTON_HEIGHT - (Layout::BOTTOM_HEIGHT - Gui::LOG_NAV_BUTTON_HEIGHT) / 2.0, Gui::LOG_NAV_BUTTON_WIDTH, Gui::LOG_NAV_BUTTON_HEIGHT}, "<") || IsKeyDown(KEY_LEFT)) {
        runPrev(Animate::RUN_STEP);
    }
    posX -= 2 + Gui::LOG_NAV_BUTTON_WIDTH;
    if (GuiButton(Rectangle{posX, Window::HEIGHT - Gui::LOG_NAV_BUTTON_HEIGHT - (Layout::BOTTOM_HEIGHT - Gui::LOG_NAV_BUTTON_HEIGHT) / 2.0, Gui::LOG_NAV_BUTTON_WIDTH, Gui::LOG_NAV_BUTTON_HEIGHT}, "|<")) {
        toFirstState();
    }
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
void ListOfOperationsGroups<T>::animateTransColor(OT* obj, OT src, OT snk) {
    backGroup()->push(std::bind(Animate::transColor<OT>, obj, src, snk, &currTime, &isReversed));
}

template<typename T>
template<typename OT> 
void ListOfOperationsGroups<T>::animateTransText(OT* obj, const std::string &src, const std::string &snk) {
    backGroup()->push(std::bind(Animate::transText<OT>, obj, src, snk, &currTime, &isReversed));
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
void ListOfOperationsGroups<T>::animateSlideColorIn(OT* obj) {
    backGroup()->push(std::bind(&Animate::slideColorIn<OT>, obj, &currTime, &isReversed));
}

template<typename T>
template<typename OT>
void ListOfOperationsGroups<T>::animateSlideColorOut(OT* obj) {
    backGroup()->push(std::bind(&Animate::slideColorOut<OT>, obj, &currTime, &isReversed));
}

template<typename T>
template<typename OT> 
void ListOfOperationsGroups<T>::animateRedirect(OT* A, OT* C) {
    backGroup()->push(std::bind(&Animate::redirect<OT>, A, C, &currTime, &isReversed));
}

template<typename T>
template<typename OT>
void ListOfOperationsGroups<T>::animateNodeFromNormalToIter(OT* node) {
    animateTransColor(&node->backColor, Gcolor::NODE_BACKGROUND, Gcolor::NODE_BACKGROUND_FOCUS_ITER);
    animateTransColor(&node->bordColor, Gcolor::NODE_BORDER, Gcolor::NODE_BORDER_FOCUS_ITER);
    animateTransColor(&node->foreColor, Gcolor::NODE_FOREGROUND, Gcolor::NODE_FOREGROUND_FOCUS);
}

template<typename T>
template<typename OT>
void ListOfOperationsGroups<T>::animateNodeFromNormalToFocus(OT* node) {
    animateTransColor(&node->backColor, Gcolor::NODE_BACKGROUND, Gcolor::NODE_BACKGROUND_FOCUS);
    animateTransColor(&node->bordColor, Gcolor::NODE_BORDER, Gcolor::NODE_BORDER_FOCUS);
    animateTransColor(&node->foreColor, Gcolor::NODE_FOREGROUND, Gcolor::NODE_FOREGROUND_FOCUS);
}

template<typename T>
template<typename OT>
void ListOfOperationsGroups<T>::animateNodeFromNormalToRefer(OT* node) {
    animateTransColor(&node->backColor, Gcolor::NODE_BACKGROUND, Gcolor::NODE_BACKGROUND_FOCUS_REFER);
    animateTransColor(&node->bordColor, Gcolor::NODE_BORDER, Gcolor::NODE_BORDER_FOCUS_REFER);
    animateTransColor(&node->foreColor, Gcolor::NODE_FOREGROUND, Gcolor::NODE_FOREGROUND_FOCUS);
}

template<typename T>
template<typename OT>
void ListOfOperationsGroups<T>::animateNodeFromNormalToRemove(OT* node) {
    animateTransColor(&node->backColor, Gcolor::NODE_BACKGROUND, Gcolor::NODE_BACKGROUND_FOCUS_REMOVE);
    animateTransColor(&node->bordColor, Gcolor::NODE_BORDER, Gcolor::NODE_BORDER_FOCUS_REMOVE);
    animateTransColor(&node->foreColor, Gcolor::NODE_FOREGROUND, Gcolor::NODE_FOREGROUND_FOCUS);
}

template<typename T>
template<typename OT>
void ListOfOperationsGroups<T>::animateNodeFromIterToNormal(OT* node) {
    animateTransColor(&node->backColor, Gcolor::NODE_BACKGROUND_FOCUS_ITER, Gcolor::NODE_BACKGROUND);
    animateTransColor(&node->bordColor, Gcolor::NODE_BORDER_FOCUS_ITER, Gcolor::NODE_BORDER);
    animateTransColor(&node->foreColor, Gcolor::NODE_FOREGROUND_FOCUS, Gcolor::NODE_FOREGROUND);
}

template<typename T>
template<typename OT>
void ListOfOperationsGroups<T>::animateNodeFromIterToNearIter(OT* node) {
    animateTransColor(&node->backColor, Gcolor::NODE_BACKGROUND_FOCUS_ITER, Gcolor::NODE_BACKGROUND);
    animateTransColor(&node->foreColor, Gcolor::NODE_FOREGROUND_FOCUS, Gcolor::NODE_FOREGROUND_FOCUS_ITER);
}

template<typename T>
template<typename OT>
void ListOfOperationsGroups<T>::animateNodeFromIterToFocus(OT* node) {
    animateTransColor(&node->backColor, Gcolor::NODE_BACKGROUND_FOCUS_ITER, Gcolor::NODE_BACKGROUND_FOCUS);
    animateTransColor(&node->bordColor, Gcolor::NODE_BORDER_FOCUS_ITER, Gcolor::NODE_BORDER_FOCUS);
}

template<typename T>
template<typename OT>
void ListOfOperationsGroups<T>::animateNodeFromNearIterToNormal(OT* node) {
    animateTransColor(&node->bordColor, Gcolor::NODE_BORDER_FOCUS_ITER, Gcolor::NODE_BORDER);
    animateTransColor(&node->foreColor, Gcolor::NODE_FOREGROUND_FOCUS_ITER, Gcolor::NODE_FOREGROUND);
}

template<typename T>
template<typename OT>
void ListOfOperationsGroups<T>::animateNodeFromFocusToIter(OT* node) {
    animateTransColor(&node->backColor, Gcolor::NODE_BACKGROUND_FOCUS, Gcolor::NODE_BACKGROUND_FOCUS_ITER);
    animateTransColor(&node->bordColor, Gcolor::NODE_BORDER_FOCUS, Gcolor::NODE_BORDER_FOCUS_ITER);
}

template<typename T>
template<typename OT>
void ListOfOperationsGroups<T>::animateNodeFromReferToNormal(OT* node) {
    animateTransColor(&node->backColor, Gcolor::NODE_BACKGROUND_FOCUS_REFER, Gcolor::NODE_BACKGROUND);
    animateTransColor(&node->bordColor, Gcolor::NODE_BORDER_FOCUS_REFER, Gcolor::NODE_BORDER);
    animateTransColor(&node->foreColor, Gcolor::NODE_FOREGROUND_FOCUS, Gcolor::NODE_FOREGROUND);
}

template<typename T>
template<typename OT>
void ListOfOperationsGroups<T>::animateArrowFromNormalToIter(OT* node) {
    animateTransColor(&node->aNext.lineColor, Gcolor::ARROW_LINE, Gcolor::ARROW_LINE_FOCUS_ITER);
}

template<typename T>
template<typename OT>
void ListOfOperationsGroups<T>::animateArrowFromNormalToFocus(OT* node) {
    animateTransColor(&node->aNext.lineColor, Gcolor::ARROW_LINE, Gcolor::ARROW_LINE_FOCUS);
}

template<typename T>
template<typename OT>
void ListOfOperationsGroups<T>::animateArrowFromIterToNormal(OT* node) {
    animateTransColor(&node->aNext.lineColor, Gcolor::ARROW_LINE_FOCUS_ITER, Gcolor::ARROW_LINE);
}

template<typename T>
template<typename OT>
void ListOfOperationsGroups<T>::animateArrowFromFocusToNormal(OT* node) {
    animateTransColor(&node->aNext.lineColor, Gcolor::ARROW_LINE_FOCUS, Gcolor::ARROW_LINE);
}

template<typename T>
template<typename OT>
void ListOfOperationsGroups<T>::animateArrowSlideFromIterToNormal(OT* node) {
    animateTransColor(&node->aNext.slideColor, Gcolor::ARROW_LINE_FOCUS_ITER, Gcolor::ARROW_LINE);
}

template<typename T>
template<typename OT>
void ListOfOperationsGroups<T>::animateArrowSlideFromNormalToIter(OT* node) {
    animateTransColor(&node->aNext.slideColor, Gcolor::ARROW_LINE, Gcolor::ARROW_LINE_FOCUS_ITER);
}

#endif
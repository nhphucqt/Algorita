#include "ListOfOperationsGroups.h"


ListOfOperationsGroups::ListOfOperationsGroups() {
    iter = groups.end();
    isReversed = false;
    runType = Animate::RUN_ALL;
    resetCode();
    resetCurrTime();
    resetSpeed();
}


double* ListOfOperationsGroups::getCurrTime() {
    return &currTime;
}


bool* ListOfOperationsGroups::getIsReversed() {
    return &isReversed;
}


typename std::list<OperationsGroups>::iterator ListOfOperationsGroups::curGroup() const {
    return groups.empty() || isReversed ? iter : prev(iter);
}


void ListOfOperationsGroups::loadCode(const std::string &path) {
    codeblock.load(path);
}


void ListOfOperationsGroups::updateCode() {
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


void ListOfOperationsGroups::resetCode() {
    codeblock.reset();
}


void ListOfOperationsGroups::addNewGroup() {
    groups.push_front(OperationsGroups());
}


OperationsGroups* ListOfOperationsGroups::backGroup() {
    return &(*groups.begin());
}


ExitStatus ListOfOperationsGroups::runPrev(Animate::RunType rt) {
    if (groups.empty()) {
        return ExitStatus(false, "");
    }
    runType = rt;
    if (isReversed) {
        if (iter == groups.end()) {
            return ExitStatus(false, "");
        } 
        if (canRunScene()) {
            return ExitStatus(false, "");
        }
        iter++;
        resetCurrTime();
        updateCode();
        return ExitStatus(true, "");
    }
    isReversed = true;
    if (iter == groups.begin()) {
        resetCurrTime();
        updateCode();
        return ExitStatus(true, "");
    }
    iter--;
    if (currTime >= Animate::ANIMATE_TIME) {
        resetCurrTime();
    }
    updateCode();
    return ExitStatus(true, "");
}


ExitStatus ListOfOperationsGroups::runNext(Animate::RunType rt) {
    if (groups.empty()) {
        return ExitStatus(false, "");
    }
    runType = rt;
    if (!isReversed) {
        if (iter == groups.begin()) {
            return ExitStatus(false, "");
        }
        if (canRunScene()) {
            return ExitStatus(false, "");
        }
        iter--;
        resetCurrTime();
        updateCode();
        return ExitStatus(true, "");
    }
    isReversed = false;
    if (iter == groups.end()) {
        assert(iter != groups.begin());
        resetCurrTime();
        updateCode();
        return ExitStatus(true, "");
    }
    iter++;
    updateCode();
    if (currTime < 0) {
        resetCurrTime();
    }
    return ExitStatus(true, "");
}


bool ListOfOperationsGroups::isPaused() const {
    return runType == Animate::RUN_STEP;
}


bool ListOfOperationsGroups::isFinished() const {
    if (groups.empty()) {
        return true;
    }
    return !isReversed && (!canRunOper() || (iter == next(groups.begin()) && isPaused() && !canRunScene()));
}


ExitStatus ListOfOperationsGroups::toggleRun() {
    if (runType == Animate::RUN_ALL) {
        runType = Animate::RUN_STEP;
    } else if (runType == Animate::RUN_STEP) {
        runNext(Animate::RUN_ALL);
    }
    return ExitStatus(true, "");
}


void ListOfOperationsGroups::build() {
    assert(iter == groups.end());
    curGroup()->passHighlightLines(&codeblock);
}


void ListOfOperationsGroups::updateCurrTime() {
    currTime += (isReversed ? -Animate::elapseTime : +Animate::elapseTime) * SPEED_SIGNATURE[speedID];
}


void ListOfOperationsGroups::resetCurrTime() {
    currTime = isReversed ? Animate::ANIMATE_TIME : 0.0;
}


bool ListOfOperationsGroups::canRunOper() const {
    return (isReversed && iter != groups.end()) || (!isReversed && iter != groups.begin());
}


bool ListOfOperationsGroups::canRunScene() const {
    return (isReversed && currTime > 0.0) || (!isReversed && currTime < Animate::ANIMATE_TIME);
}


bool ListOfOperationsGroups::run() {
    if (runType == Animate::RUN_ALL) {
        if (!canRunOper()) {
            return true;
        }
        updateCurrTime();
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
    assert(false);
    return false;
}


ExitStatus ListOfOperationsGroups::toFirstState() {
    runPrev(Animate::RUN_ALL);
    while (!run());
    toggleRun();
    return ExitStatus(true, "");
}


ExitStatus ListOfOperationsGroups::toLastState() {
    runNext(Animate::RUN_ALL);
    while (!run());
    return ExitStatus(true, "");
}


ExitStatus ListOfOperationsGroups::replay() {
    toFirstState();
    toggleRun();
    return ExitStatus(true, "");
}



void ListOfOperationsGroups::clearGroup() {
    toLastState();
    for (typename std::list<OperationsGroups>::iterator curr = groups.begin(); curr != groups.end(); ++curr) {
        curr->destroy();
    }
    groups.clear();
    iter = groups.end();
    runType = Animate::RUN_ALL;
    isReversed = false;
    codeblock.reset();
}


int ListOfOperationsGroups::closestSpeedID(double s) {
    return round(s);
}


void ListOfOperationsGroups::decSpeed() {
    if (speedID > 0) {
        speedID--;
    }
}


void ListOfOperationsGroups::incSpeed() {
    if (speedID < NUM_SPEED-1) {
        speedID++;
    }
}


void ListOfOperationsGroups::resetSpeed() {
    speedID = std::lower_bound(SPEED_SIGNATURE, SPEED_SIGNATURE + NUM_SPEED, 1.0) - SPEED_SIGNATURE;
}


double ListOfOperationsGroups::getProgress() {
    int cnt = 0;
    for (typename std::list<OperationsGroups>::iterator it = groups.end(); it != iter; --it, ++cnt);
    double progress = runType == Animate::RUN_ALL ? cnt : cnt + (!canRunScene() ? (isReversed ? -1 : +1) : 0);
    if (canRunScene()) {
        progress += currTime / Animate::ANIMATE_TIME - isReversed;
    }
    return progress;
}


void ListOfOperationsGroups::draw(bool keyActive) {
    codeblock.draw(Window::DIMENSION - toVector2(0, Layout::BOTTOM_HEIGHT) - codeblock.getBlockDimension());
    float posX = Window::WIDTH - Gui::LOG_SPEED_SIGN_WIDTH;
    GuiLabel(Rectangle{posX, Window::HEIGHT - Gui::LOG_SPEED_SIGN_HEIGHT, Gui::LOG_SPEED_SIGN_WIDTH, Gui::LOG_SPEED_SIGN_HEIGHT}, (" " + cf::double2str(SPEED_SIGNATURE[speedID]) + "x").c_str());
    posX -= Gui::LOG_SLIDER_WIDTH;
    if (keyActive && IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_UP)) {
        resetSpeed();
    } else {
        if (keyActive && IsKeyPressed(KEY_DOWN)) {
            decSpeed();
        }
        if (keyActive && IsKeyPressed(KEY_UP)) {
            incSpeed();
        }
    }
    speedID = closestSpeedID(GuiSlider(Rectangle{posX, Window::HEIGHT - Gui::LOG_SLIDER_HEIGHT - (Layout::BOTTOM_HEIGHT - Gui::LOG_SLIDER_HEIGHT) / 2.0, Gui::LOG_SLIDER_WIDTH, Gui::LOG_SLIDER_HEIGHT}, nullptr, nullptr, speedID, 0, NUM_SPEED-1));
    posX -= 10 + Gui::LOG_SLIDER_BAR_WIDTH;
    GuiSliderBar(Rectangle{posX, Window::HEIGHT - Gui::LOG_SLIDER_BAR_HEIGHT - (Layout::BOTTOM_HEIGHT - Gui::LOG_SLIDER_BAR_HEIGHT) / 2.0, Gui::LOG_SLIDER_BAR_WIDTH, Gui::LOG_SLIDER_BAR_HEIGHT}, nullptr, nullptr, getProgress(), 0, (int)groups.size());
    posX -= 10 + Gui::LOG_NAV_BUTTON_WIDTH;
    if (GuiButton(Rectangle{posX, Window::HEIGHT - Gui::LOG_NAV_BUTTON_HEIGHT - (Layout::BOTTOM_HEIGHT - Gui::LOG_NAV_BUTTON_HEIGHT) / 2.0, Gui::LOG_NAV_BUTTON_WIDTH, Gui::LOG_NAV_BUTTON_HEIGHT}, Gicon::BUTTON_LAST) || (keyActive && (IsKeyDown(KEY_LEFT_SHIFT)||IsKeyDown(KEY_RIGHT_SHIFT)) && IsKeyPressed(KEY_RIGHT))) {
        toLastState();
    }
    posX -= 2 + Gui::LOG_NAV_BUTTON_WIDTH;
    if (GuiButton(Rectangle{posX, Window::HEIGHT - Gui::LOG_NAV_BUTTON_HEIGHT - (Layout::BOTTOM_HEIGHT - Gui::LOG_NAV_BUTTON_HEIGHT) / 2.0, Gui::LOG_NAV_BUTTON_WIDTH, Gui::LOG_NAV_BUTTON_HEIGHT}, Gicon::BUTTON_NEXT) || (keyActive && IsKeyDown(KEY_RIGHT))) {
        runNext(Animate::RUN_STEP);
    }
    posX -= 2 + Gui::LOG_NAV_BUTTON_WIDTH;
    if (GuiButton(Rectangle{posX, Window::HEIGHT - Gui::LOG_NAV_BUTTON_HEIGHT - (Layout::BOTTOM_HEIGHT - Gui::LOG_NAV_BUTTON_HEIGHT) / 2.0, Gui::LOG_NAV_BUTTON_WIDTH, Gui::LOG_NAV_BUTTON_HEIGHT}, isFinished() ? Gicon::BUTTON_REPLAY : isPaused() ? Gicon::BUTTON_PLAY : Gicon::BUTTON_PAUSE) || (keyActive && IsKeyPressed(KEY_SPACE))) {
        if (isFinished()) {
            replay();
        } else {
            toggleRun();
        }
    }
    posX -= 2 + Gui::LOG_NAV_BUTTON_WIDTH;
    if (GuiButton(Rectangle{posX, Window::HEIGHT - Gui::LOG_NAV_BUTTON_HEIGHT - (Layout::BOTTOM_HEIGHT - Gui::LOG_NAV_BUTTON_HEIGHT) / 2.0, Gui::LOG_NAV_BUTTON_WIDTH, Gui::LOG_NAV_BUTTON_HEIGHT}, Gicon::BUTTON_PREV) || (keyActive && IsKeyDown(KEY_LEFT))) {
        runPrev(Animate::RUN_STEP);
    }
    posX -= 2 + Gui::LOG_NAV_BUTTON_WIDTH;
    if (GuiButton(Rectangle{posX, Window::HEIGHT - Gui::LOG_NAV_BUTTON_HEIGHT - (Layout::BOTTOM_HEIGHT - Gui::LOG_NAV_BUTTON_HEIGHT) / 2.0, Gui::LOG_NAV_BUTTON_WIDTH, Gui::LOG_NAV_BUTTON_HEIGHT}, Gicon::BUTTON_FIRST) || (keyActive && (IsKeyDown(KEY_LEFT_SHIFT)||IsKeyDown(KEY_RIGHT_SHIFT)) && IsKeyPressed(KEY_LEFT))) {
        toFirstState();
    }
}   

void ListOfOperationsGroups::destroy() {
    clearGroup();
    resetCurrTime();
    resetCode();
    resetSpeed();
}

void ListOfOperationsGroups::animateDelay() {
    backGroup()->push(std::bind(&Animate::delay, &currTime, &isReversed));
}

void ListOfOperationsGroups::animateTransColor(Color* obj, Color** robj, Color* src, Color* snk) {
    backGroup()->push(std::bind(Animate::transColor, obj, robj, src, snk, &currTime, &isReversed));
}
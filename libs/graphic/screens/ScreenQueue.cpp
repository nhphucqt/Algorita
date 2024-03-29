#include "ScreenQueue.h"

Screen::ScreenQueue::ScreenQueue() {}
Screen::ScreenQueue::~ScreenQueue() {}

void Screen::ScreenQueue::load() { // Ensure that obj has to be destroy before (prevent MEMORY LEAKING)
    inputUpdate.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_DIGIT_INPUT, true, false);
    inputPush.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_DIGIT_INPUT, true,  false);
    inputUserDefined.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + 5, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6 + 5, Gui::USER_DEF_BUTTON_WIDTH - Gui::BUTTON_OPER_GO_WIDTH - 15, Gui::USER_DEF_INPUT_HEIGHT}, Graphic::MAX_SIZE_INPUT, false, false);

    toggleCreateType.init(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 7, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Create", false);
    toggleUpdateType.init(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Update", false);
    togglePushType.init(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Push", false);

    toggleUserDefine.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 7, Gui::USER_DEF_BUTTON_WIDTH, Gui::USER_DEF_BUTTON_HEIGHT}, "Input", false);

    exitMessage = StyledText(std::string(), Gfont::defaultFont);
}

void Screen::ScreenQueue::init() {
    currOperationType = OTNULL;
    currOperation = ONULL;
    exitMessage.assign(obj.initialize(GetRandomValue(1, Core::MAX_NUM_NODE_SLL), &ALOG).message);
}

void Screen::ScreenQueue::draw() {
    bool keyActive = true;
    if (toggleCreateType.draw()) {
        if (toggleCreateType.justToggle()) {
            currOperationType = CREATE;
        } else if (currOperationType != CREATE) {
            toggleCreateType.deactive();
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 7, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Empty")) {
            currOperation = CREATE_EMPTY;
            exitMessage.assign(obj.initialize(0, &ALOG).message);
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 7, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Random")) {
            currOperation = CREATE_RANDOM;
            exitMessage.assign(obj.initialize(GetRandomValue(1, Core::MAX_NUM_NODE_SLL), &ALOG).message);
        }
        if (toggleUserDefine.draw()) {
            if (toggleUserDefine.justToggle()) {
                currOperation = CREATE_USER_DEF;
            } else if (currOperation != CREATE_USER_DEF) {
                toggleUserDefine.deactive();
            }
            GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6, Gui::USER_DEF_BUTTON_WIDTH, Gui::USER_DEF_BUTTON_HEIGHT}, "");
            keyActive &= !inputUserDefined.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::USER_DEF_BUTTON_WIDTH - Gui::BUTTON_OPER_GO_WIDTH - 6, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6 + 5, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_GO_HEIGHT}, "Go") || (keyActive && IsKeyPressed(KEY_ENTER))) {
                exitMessage.assign(obj.initialize(inputUserDefined.getStr(), &ALOG).message);
            }
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::USER_DEF_BUTTON_WIDTH + Gui::BUTTON_OPER_DIST_X, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 7, Gui::FILE_DIALOG_OPEN_BUTTON_WIDTH, Gui::FILE_DIALOG_OPEN_BUTTON_HEIGHT}, "File")) {
            currOperation = CREATE_FILE;
            wchar_t const * filePath = TinyDial::guiOpenTextFile();
            if (filePath != nullptr) {
                std::wifstream fin(filePath);
                if (!fin.is_open()) {
                    std::wcerr << L"ERROR: Cannot open " << filePath << '\n';
                } else {
                    std::wstringstream ss;
                    ss << fin.rdbuf();
                    fin.close();
                    std::wstring_convert<std::codecvt_utf8<wchar_t>,wchar_t> cv;
                    std::string str = cv.to_bytes(ss.str());
                    exitMessage.assign(obj.initialize(str, &ALOG).message);
                }
            }
        }
    }
    // Peek type Button
    if (GuiButton(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Peek")) {
        currOperationType = PEEK;
        exitMessage.assign(obj.peek(&ALOG).message);
    }
    // Update type Button
    if (toggleUpdateType.draw()) {
        if (toggleUpdateType.justToggle()) {
            currOperationType = UPDATE;
        } else if (currOperationType != UPDATE) {
            toggleUpdateType.deactive();
        }
        GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, nullptr);
        GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "v =");
        keyActive &= !inputUpdate.draw();
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5 + 5, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
            inputUpdate.setnum(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5 + 5, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_GO_HEIGHT}, "Go") || (keyActive && IsKeyPressed(KEY_ENTER))) {
            exitMessage.assign(obj.update(inputUpdate.getNum(), &ALOG).message);
        }
    }
    // Push type Button
    if (togglePushType.draw()) {
        if (togglePushType.justToggle()) {
            currOperationType = PUSH;
        } else if (currOperationType != PUSH) {
            togglePushType.deactive();
        }
        GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, nullptr);
        GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "v =");
        keyActive &= !inputPush.draw();
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4 + 5, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
            inputPush.setnum(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4 + 5, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_GO_HEIGHT}, "Go") || (keyActive && IsKeyPressed(KEY_ENTER))) {
            exitMessage.assign(obj.push(inputPush.getNum(), &ALOG).message);
        }
    }
    // Pop type Button
    if (GuiButton(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Pop")) {
        currOperationType = POP;
        exitMessage.assign(obj.pop(&ALOG).message);
    }
    // Clear type button
    if (GuiButton(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Clear")) {
        currOperationType = CLEAR;
        exitMessage.assign(obj.clear(&ALOG).message);
    }
    
    ALOG.run();
    obj.draw();
    ALOG.draw(keyActive);
    exitMessage.draw(20, (Window::HEIGHT - Layout::BOTTOM_HEIGHT + (Layout::BOTTOM_HEIGHT - exitMessage.dim.y) / 2), Theme::currTheme.EXIT_MESSAGE);
    Layout::drawTopNavigation(keyActive);
}

void Screen::ScreenQueue::destroy() {
    ALOG.destroy();
    obj.destroy();
}
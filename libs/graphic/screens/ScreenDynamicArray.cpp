#include "ScreenDynamicArray.h"

Screen::ScreenDynamicArray::ScreenDynamicArray() {}

void Screen::ScreenDynamicArray::load() { // Ensure that obj has to be destroy before (prevent MEMORY LEAKING)
    inputSearchFirst.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_DIGIT_INPUT, true, false);
    inputCreateAllZeros.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_DIGIT_INPUT, true, false);
    inputCreateRandom.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_DIGIT_INPUT, true, false);
    inputAccessValue.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_DIGIT_INPUT, true, false);
    inputUpdateValuePos.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_DIGIT_INPUT, true, false);
    inputUpdateValueVal.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_DIGIT_INPUT, true, false);
    inputInsertBack.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_DIGIT_INPUT, true, false);
    inputUserDefined.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + 5, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6 + 5, Gui::USER_DEF_BUTTON_WIDTH - Gui::BUTTON_OPER_GO_WIDTH - 15, Gui::USER_DEF_INPUT_HEIGHT}, Graphic::MAX_SIZE_INPUT, false, false);

    toggleCreateType.init(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 7, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Create", false);
    toggleCreateAllZeros.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 7, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "All Zeros", false);
    toggleCreateRandom.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 7, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Random", false);

    toggleSearchType.init(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Search", false);
    toggleAccessType.init(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Access", false);
    toggleUpdateType.init(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Update", false);
    toggleInsertType.init(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Push", false);
    toggleInsertBack.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Back", false);
    toggleRemoveType.init(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Pop", false);

    toggleUserDefine.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 7, Gui::USER_DEF_BUTTON_WIDTH, Gui::USER_DEF_BUTTON_HEIGHT}, "Input", false);
    toggleSearchFirst.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "First value", false);

    exitMessage = StyledText(std::string(), Gfont::defaultFont);
}

void Screen::ScreenDynamicArray::init() {
    currOperationType = OTNULL;
    currOperation = ONULL;
    exitMessage.assign(obj.initialize(GetRandomValue(1, Core::MAX_NUM_ARRAY_ELM), true, &ALOG).message);
}

void Screen::ScreenDynamicArray::draw() {
    bool keyActive = true;
    if (toggleCreateType.draw()) {
        if (toggleCreateType.justToggle()) {
            currOperationType = CREATE;
        } else if (currOperationType != CREATE) {
            toggleCreateType.deactive();
        }
        if (toggleCreateAllZeros.draw()) {
            if (toggleCreateAllZeros.justToggle()) {
                currOperation = CREATE_ALL_ZEROS;
            } else if (currOperation != CREATE_ALL_ZEROS) {
                toggleCreateAllZeros.deactive();
            }
            GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "");
            GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "n =");
            keyActive &= !inputCreateAllZeros.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6 + 5, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
                inputCreateAllZeros.setnum(GetRandomValue(1, Core::MAX_NUM_ARRAY_ELM));
            }
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6 + 5, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_GO_HEIGHT}, "Go") || (keyActive && IsKeyPressed(KEY_ENTER))) {
                exitMessage.assign(obj.initialize(inputCreateAllZeros.getNum(), false, &ALOG).message);
            }
        }
        if (toggleCreateRandom.draw()) {
            if (toggleCreateRandom.justToggle()) {
                currOperation = CREATE_RANDOM;
            } else if (currOperation != CREATE_RANDOM) {
                toggleCreateRandom.deactive();
            }
            GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "");
            GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "n =");
            keyActive &= !inputCreateRandom.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6 + 5, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
                inputCreateRandom.setnum(GetRandomValue(1, Core::MAX_NUM_ARRAY_ELM));
            }
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6 + 5, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_GO_HEIGHT}, "Go") || (keyActive && IsKeyPressed(KEY_ENTER))) {
                exitMessage.assign(obj.initialize(inputCreateRandom.getNum(), true, &ALOG).message);
            }
        }
        if (toggleUserDefine.draw()) {
            if (toggleUserDefine.justToggle()) {
                currOperation = CREATE_USER_DEF;
            } else if (currOperation != CREATE_USER_DEF) {
                toggleUserDefine.deactive();
            }
            GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6, Gui::USER_DEF_BUTTON_WIDTH, Gui::USER_DEF_BUTTON_HEIGHT}, "");
            keyActive &= !inputUserDefined.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::USER_DEF_BUTTON_WIDTH - Gui::BUTTON_OPER_GO_WIDTH - 5, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6 + 5, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_GO_HEIGHT}, "Go") || (keyActive && IsKeyPressed(KEY_ENTER))) {
                exitMessage.assign(obj.initialize(inputUserDefined.getStr(), &ALOG).message);
            }
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::USER_DEF_BUTTON_WIDTH + Gui::BUTTON_OPER_DIST_X, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 7, Gui::FILE_DIALOG_OPEN_BUTTON_WIDTH, Gui::FILE_DIALOG_OPEN_BUTTON_HEIGHT}, "File")) {
            currOperation = CREATE_FILE;
            char const * filePath = TinyDial::guiOpenTextFile();
            if (filePath != nullptr) {
                std::ifstream fin(filePath);
                std::stringstream ss;
                ss << fin.rdbuf();
                fin.close();
                obj.initialize(ss.str(), &ALOG);
            }
        }
    }
    // Search type Button
    if (toggleSearchType.draw()) {
        if (toggleSearchType.justToggle()) {
            currOperationType = SEARCH;
        } else if (currOperationType != SEARCH) {
            toggleSearchType.deactive();
        }
        if (toggleSearchFirst.draw()) {
            if (toggleSearchFirst.justToggle()) {
                currOperation = SEARCH_FIRST;
            } else if (currOperation != SEARCH_FIRST) {
                toggleSearchFirst.deactive();
            }
            GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "");
            GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "v =");
            keyActive &= !inputSearchFirst.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
                inputSearchFirst.setnum(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
            }
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_GO_HEIGHT}, "Go") || (keyActive && IsKeyPressed(KEY_ENTER))) {
                exitMessage.assign(obj.searchFirst(inputSearchFirst.getNum(), &ALOG).message);
            }
        }
    }
    // Accesss type Button
    if (toggleAccessType.draw()) {
        if (toggleAccessType.justToggle()) {
            currOperationType = ACCESS;
        } else if (currOperationType != ACCESS) {
            toggleAccessType.deactive();
        }
        GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "");
        GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "i =");
        keyActive &= !inputAccessValue.draw();
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6 + 5, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
            if (obj.empty()) {
                exitMessage.assign(ExitMess::FAIL_ARR_EMPTY.message);
            } else {
                inputAccessValue.setnum(GetRandomValue(0, obj.size()-1));
            }
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6 + 5, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_GO_HEIGHT}, "Go") || (keyActive && IsKeyPressed(KEY_ENTER))) {
            exitMessage.assign(obj.accessValue(inputAccessValue.getNum(), &ALOG).message);
        }
    }
    // Update type Button
    if (toggleUpdateType.draw()) {
        if (toggleUpdateType.justToggle()) {
            currOperationType = UPDATE;
        } else if (currOperationType != UPDATE) {
            toggleUpdateType.deactive();
        }
        GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT * 2}, "");
        GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "i =");
        keyActive &= !inputUpdateValuePos.draw();
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5 + 5, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
            if (obj.empty()) {
                exitMessage.assign(ExitMess::FAIL_ARR_EMPTY.message);
            } else {
                inputUpdateValuePos.setnum(GetRandomValue(0, obj.size()-1));
            }
        }
        GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "v =");
        keyActive &= !inputUpdateValueVal.draw();
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4 + 5, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
            inputUpdateValueVal.setnum(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5 + 5, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_GO_HEIGHT * 2 + 10}, "Go") || (keyActive && IsKeyPressed(KEY_ENTER))) {
            exitMessage.assign(obj.updateValue(inputUpdateValuePos.getNum(), inputUpdateValueVal.getNum(), &ALOG).message);
        }
    }
    // Insert type Button
    if (toggleInsertType.draw()) {
        if (toggleInsertType.justToggle()) {
            currOperationType = INSERT;
        } else if (currOperationType != INSERT) {
            toggleInsertType.deactive();
        }
        if (toggleInsertBack.draw()) {
            if (toggleInsertBack.justToggle()) {
                currOperation = INSERT_BACK;
            } else if (currOperation != INSERT_BACK) {
                toggleInsertBack.deactive();
            }
            GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "");
            GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "v =");
            keyActive &= !inputInsertBack.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
                inputInsertBack.setnum(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
            }
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, "Go") || (keyActive && IsKeyPressed(KEY_ENTER))) {
                exitMessage.assign(obj.pushBack(inputInsertBack.getNum(), &ALOG).message);
            }
        }
    }
    // Remove type Button
    if (toggleRemoveType.draw()) {
        if (toggleRemoveType.justToggle()) {
            currOperationType = REMOVE;
        } else if (currOperationType != REMOVE) {
            toggleRemoveType.deactive();
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Back")) {
            currOperation = REMOVE_BACK;
            exitMessage.assign(obj.popBack(&ALOG).message);
        }
    }

    ALOG.run();
    obj.draw();
    ALOG.draw(keyActive);
    exitMessage.draw(10, 865, Theme::currTheme.EXIT_MESSAGE);
    Layout::drawTopNavigation(keyActive);
}

void Screen::ScreenDynamicArray::destroy() {
    obj.destroy();
    ALOG.destroy();
}
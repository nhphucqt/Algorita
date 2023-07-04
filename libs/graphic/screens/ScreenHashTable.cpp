#include "ScreenHashTable.h"

Screen::ScreenHashTable::ScreenHashTable() {}
Screen::ScreenHashTable::~ScreenHashTable() {}

void Screen::ScreenHashTable::load() { // Ensure that obj has to be destroy before (prevent MEMORY LEAKING)
    inputSearchFirst.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_DIGIT_INPUT, true, false);
    inputInsertFord.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_DIGIT_INPUT, true, false);
    inputInsertBack.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_DIGIT_INPUT, true, false);
    inputInsertMiddPos.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_DIGIT_INPUT, true, false);
    inputInsertMiddVal.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_DIGIT_INPUT, true, false);
    inputUpdateValuePos.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_DIGIT_INPUT, true, false);
    inputUpdateValueVal.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_DIGIT_INPUT, true, false);
    inputRemoveMidd.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 1 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_DIGIT_INPUT, true, false);
    inputUserDefined.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + 5, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5 + 5, Gui::USER_DEF_BUTTON_WIDTH - Gui::BUTTON_OPER_GO_WIDTH - 15, Gui::USER_DEF_INPUT_HEIGHT}, Graphic::MAX_SIZE_INPUT, false, false);

    toggleCreateType.init(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Create", false);
    toggleSearchType.init(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Search", false);
    toggleInsertType.init(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Insert", false);
    toggleUpdateType.init(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Update", false);
    toggleRemoveType.init(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Remove", false);

    toggleUserDefine.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6, Gui::USER_DEF_BUTTON_WIDTH, Gui::USER_DEF_BUTTON_HEIGHT}, "Input", false);
    toggleSearchFirst.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "First value", false);
    toggleInsertFord.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Head", false);
    toggleInsertBack.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Tail", false);
    toggleInsertMidd.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "i-th node", false);
    toggleRemoveMidd.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "i-th node", false);

    exitMessage = StyledText(std::string(), Gfont::defaultFont);
}

void Screen::ScreenHashTable::init() {
    currOperationType = OTNULL;
    currOperation = ONULL;
    int initSize = GetRandomValue(1, Core::MAX_NUM_HT_HOR_ELM);
    int initNum = GetRandomValue(0, Core::MAX_NUM_HT_VER_ELM * initSize);
    exitMessage.assign(obj.initialize(initSize, initNum, &ALOG).message);
    // std::cerr << "Screen::ScreenHashTable::init()" << std::endl;
}

void Screen::ScreenHashTable::draw() {
    // std::cerr << "Screen::ScreenHashTable::draw()" << std::endl;
    bool keyActive = true;
    if (toggleCreateType.draw()) {
        if (toggleCreateType.justToggle()) {
            currOperationType = CREATE;
        } else if (currOperationType != CREATE) {
            toggleCreateType.deactive();
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Empty")) {
            currOperation = CREATE_EMPTY;
            exitMessage.assign(obj.initialize(0, &ALOG).message);
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Random")) {
            currOperation = CREATE_RANDOM;
            // exitMessage.assign(obj.initialize(GetRandomValue(1, Core::MAX_NUM_NODE_SLL), &ALOG).message);
        }
        if (toggleUserDefine.draw()) {
            if (toggleUserDefine.justToggle()) {
                currOperation = CREATE_USER_DEF;
            } else if (currOperation != CREATE_USER_DEF) {
                toggleUserDefine.deactive();
            }
            GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5, Gui::USER_DEF_BUTTON_WIDTH, Gui::USER_DEF_BUTTON_HEIGHT}, "");
            keyActive &= !inputUserDefined.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::USER_DEF_BUTTON_WIDTH - Gui::BUTTON_OPER_GO_WIDTH - 5, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, "Go") || (keyActive && IsKeyPressed(KEY_ENTER))) {
                exitMessage.assign(obj.initialize(inputUserDefined.getStr(), &ALOG).message);
            }
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::USER_DEF_BUTTON_WIDTH + Gui::BUTTON_OPER_DIST_X, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6, Gui::FILE_DIALOG_OPEN_BUTTON_WIDTH, Gui::FILE_DIALOG_OPEN_BUTTON_HEIGHT}, "File")) {
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
            GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "");
            GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "v =");
            keyActive &= !inputSearchFirst.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
                inputSearchFirst.setnum(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
            }
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, "Go") || (keyActive && IsKeyPressed(KEY_ENTER))) {
                exitMessage.assign(obj.searchFirst(inputSearchFirst.getNum(), &ALOG).message);
            }
        }
    }
    // Insert type Button
    if (toggleInsertType.draw()) {
        if (toggleInsertType.justToggle()) {
            currOperationType = INSERT;
        } else if (currOperationType != INSERT) {
            toggleInsertType.deactive();
        }
        if (toggleInsertFord.draw()) {
            if (toggleInsertFord.justToggle()) {
                currOperation = INSERT_FORD;
            } else if (currOperation != INSERT_FORD) {
                toggleInsertFord.deactive();
            }
            GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "");
            GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "v =");
            keyActive &= !inputInsertFord.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
                inputInsertFord.setnum(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
            }
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, "Go") || (keyActive && IsKeyPressed(KEY_ENTER))) {
                // exitMessage.assign(obj.pushFront(inputInsertFord.getNum(), &ALOG).message);
            }
        }
        if (toggleInsertBack.draw()) {
            if (toggleInsertBack.justToggle()) {
                currOperation = INSERT_BACK;
            } else if (currOperation != INSERT_BACK) {
                toggleInsertBack.deactive();
            }
            GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "");
            GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "v =");
            keyActive &= !inputInsertBack.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
                inputInsertBack.setnum(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
            }
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, "Go") || (keyActive && IsKeyPressed(KEY_ENTER))) {
                // exitMessage.assign(obj.pushBack(inputInsertBack.getNum(), &ALOG).message);
            }
        }
        if (toggleInsertMidd.draw()) {
            if (toggleInsertMidd.justToggle()) {
                currOperation = INSERT_MIDD;
            } else if (currOperation != INSERT_MIDD) {
                toggleInsertMidd.deactive();
            }
            GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT * 2}, "");
            GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "i =");
            keyActive &= !inputInsertMiddPos.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
                // inputInsertMiddPos.setnum(GetRandomValue(0, obj.size()));
            }
            GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "v =");
            keyActive &= !inputInsertMiddVal.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
                inputInsertMiddVal.setnum(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
            }
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT * 2 + 10}, "Go") || (keyActive && IsKeyPressed(KEY_ENTER))) {
                // exitMessage.assign(obj.pushAtKth(inputInsertMiddPos.getNum(), inputInsertMiddVal.getNum(), &ALOG).message);
            }
        }
    }
    // Update type Button
    // if (toggleUpdateType.draw()) {
    //     if (toggleUpdateType.justToggle()) {
    //         currOperationType = UPDATE;
    //     } else if (currOperationType != UPDATE) {
    //         toggleUpdateType.deactive();
    //     }
    //     GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT * 2}, "");
    //     GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "i =");
    //     keyActive &= !inputUpdateValuePos.draw();
    //     if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
    //         if (obj.empty()) {
    //             exitMessage.assign(ExitMess::FAIL_LL_EMPTY.message);
    //         } else {
    //             inputUpdateValuePos.setnum(GetRandomValue(0, obj.size()-1));
    //         }
    //     }
    //     GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "v =");
    //     keyActive &= !inputUpdateValueVal.draw();
    //     if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
    //         inputUpdateValueVal.setnum(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
    //     }
    //     if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT * 2 + 10}, "Go") || (keyActive && IsKeyPressed(KEY_ENTER))) {
    //         exitMessage.assign(obj.updateValue(inputUpdateValuePos.getNum(), inputUpdateValueVal.getNum(), &ALOG).message);
    //     }
    // }
    
    // Remove type Button
    if (toggleRemoveType.draw()) {
        if (toggleRemoveType.justToggle()) {
            currOperationType = REMOVE;
        } else if (currOperationType != REMOVE) {
            toggleRemoveType.deactive();
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Head")) {
            exitMessage.assign(obj.popFront(&ALOG).message);
        } 
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Tail")) {
            // exitMessage.assign(obj.popBack(&ALOG).message);
        }
        if (toggleRemoveMidd.draw()) {
            if (toggleRemoveMidd.justToggle()) {
                currOperation = REMOVE_MIDD;
            } else if (currOperation != REMOVE_MIDD) {
                toggleRemoveMidd.deactive();
            }
            GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 1, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "");
            GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 1, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "i =");
            keyActive &= !inputRemoveMidd.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 1 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
                // if (obj.empty()) {
                //     exitMessage.assign("The list is empty");
                // } else {
                //     inputRemoveMidd.setnum(GetRandomValue(0, obj.size()-1));
                // }
            }
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 1 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, "Go") || (keyActive && IsKeyPressed(KEY_ENTER))) {
                // exitMessage.assign(obj.popAtKth(inputRemoveMidd.getNum(), &ALOG).message);
            }
        }
    }
    // std::cerr << "run ALOG\n";
    ALOG.run();
    // std::cerr << "done ALOG\n";
    // std::cerr << "draw obj\n";
    obj.draw();
    // std::cerr << "done draw obj\n";
    ALOG.draw(keyActive);
    exitMessage.draw(20, (Window::HEIGHT - Layout::BOTTOM_HEIGHT + (Layout::BOTTOM_HEIGHT - exitMessage.dim.y) / 2), Theme::currTheme.EXIT_MESSAGE);
    Layout::drawTopNavigation(keyActive);
}

void Screen::ScreenHashTable::destroy() {
    ALOG.destroy();
    obj.destroy();
}
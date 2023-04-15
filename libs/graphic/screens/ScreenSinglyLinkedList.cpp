#include "ScreenSinglyLinkedList.h"

Screen::ScreenSinglyLinkedList::ScreenSinglyLinkedList() { // Ensure that obj has to be destroy before (prevent MEMORY LEAKING)
    obj = GraphicSinglyLinkedList();
    inputSearchFirst.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_SIZE_INPUT, false);
    inputInsertFord.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_SIZE_INPUT, false);
    inputInsertBack.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_SIZE_INPUT, false);
    inputInsertMiddPos.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_SIZE_INPUT, false);
    inputInsertMiddVal.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_SIZE_INPUT, false);
    inputUpdateValuePos.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_SIZE_INPUT, false);
    inputUpdateValueVal.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_SIZE_INPUT, false);
    inputRemoveMidd.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 1 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_SIZE_INPUT, false);
    inputUserDefined.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + 5, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5 + 5, Gui::USER_DEF_BUTTON_WIDTH - Gui::BUTTON_OPER_GO_WIDTH - 15, Gui::USER_DEF_INPUT_HEIGHT}, Graphic::MAX_SIZE_INPUT, false);

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

    ALOG.setMainObj(&obj);

    fileDialogState = InitGuiFileDialog(Gui::FILE_DIALOG_WIDTH, Gui::FILE_DIALOG_HEIGHT, GetWorkingDirectory(), false);
}

void Screen::ScreenSinglyLinkedList::draw() {
    bool inputActive = false;
    if (fileDialogState.windowActive) {
        GuiLock();
    }
    if (toggleCreateType.draw()) {
        if (toggleCreateType.justToggle()) {
            currOperationType = CREATE;
        } else if (currOperationType != CREATE) {
            toggleCreateType.deactive();
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Empty")) {
            exitMessage.assign(obj.initialize(0, &ALOG).message);
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Random")) {
            exitMessage.assign(obj.initialize(GetRandomValue(1, Core::MAX_NUM_NODE_SLL), &ALOG).message);
        }
        if (toggleUserDefine.draw()) {
            GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5, Gui::USER_DEF_BUTTON_WIDTH, Gui::USER_DEF_BUTTON_HEIGHT}, "");
            inputActive |= inputUserDefined.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::USER_DEF_BUTTON_WIDTH - Gui::BUTTON_OPER_GO_WIDTH - 5, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, "Go")) {
                exitMessage.assign(obj.initialize(inputUserDefined.getStr(), &ALOG).message);
            }
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::USER_DEF_BUTTON_WIDTH + Gui::BUTTON_OPER_DIST_X, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6, Gui::FILE_DIALOG_OPEN_BUTTON_WIDTH, Gui::FILE_DIALOG_OPEN_BUTTON_HEIGHT}, "File")) {
            fileDialogState.windowActive = true;
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
            inputActive |= inputSearchFirst.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
                inputSearchFirst.setnum(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
            }
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, "Go")) {
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
            inputActive |= inputInsertFord.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
                inputInsertFord.setnum(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
            }
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, "Go")) {
                exitMessage.assign(obj.pushFront(inputInsertFord.getNum(), &ALOG).message);
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
            inputActive |= inputInsertBack.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
                inputInsertBack.setnum(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
            }
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, "Go")) {
                exitMessage.assign(obj.pushBack(inputInsertBack.getNum(), &ALOG).message);
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
            inputActive |= inputInsertMiddPos.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
                inputInsertMiddPos.setnum(GetRandomValue(0, obj.size()));
            }
            GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "v =");
            inputActive |= inputInsertMiddVal.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
                inputInsertMiddVal.setnum(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
            }
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT * 2 + 10}, "Go")) {
                exitMessage.assign(obj.pushAtKth(inputInsertMiddPos.getNum(), inputInsertMiddVal.getNum(), &ALOG).message);
            }
        }
    }
    // Update type Button
    if (toggleUpdateType.draw()) {
        if (toggleUpdateType.justToggle()) {
            currOperationType = UPDATE;
        } else if (currOperationType != UPDATE) {
            toggleUpdateType.deactive();
        }
        GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT * 2}, "");
        GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "i =");
        inputActive |= inputUpdateValuePos.draw();
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
            if (obj.empty()) {
                exitMessage.assign("The list is empty");
            } else {
                inputUpdateValuePos.setnum(GetRandomValue(0, obj.size()-1));
            }
        }
        GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "v =");
        inputActive |= inputUpdateValueVal.draw();
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
            inputUpdateValueVal.setnum(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT * 2 + 10}, "Go")) {
            exitMessage.assign(obj.updateValue(inputUpdateValuePos.getNum(), inputUpdateValueVal.getNum(), &ALOG).message);
        }
    }
    
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
            exitMessage.assign(obj.popBack(&ALOG).message);
        }
        if (toggleRemoveMidd.draw()) {
            if (toggleRemoveMidd.justToggle()) {
                currOperation = REMOVE_MIDD;
            } else if (currOperation != REMOVE_MIDD) {
                toggleRemoveMidd.deactive();
            }
            GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 1, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "");
            GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 1, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "i =");
            inputActive |= inputRemoveMidd.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 1 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
                if (obj.empty()) {
                    exitMessage.assign("The list is empty");
                } else {
                    inputRemoveMidd.setnum(GetRandomValue(0, obj.size()-1));
                }
            }
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 1 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, "Go")) {
                exitMessage.assign(obj.popAtKth(inputRemoveMidd.getNum(), &ALOG).message);
            }
        }
    }

    if (fileDialogState.SelectFilePressed) {
        // std::cerr << fileDialogState.fileNameText << '\n';
        std::ifstream fin(fileDialogState.fileNameText);
        std::string data;
        std::getline(fin, data);
        fin.close();
        obj.initialize(data, &ALOG);
        fileDialogState.SelectFilePressed = false;
    }

    // std::cerr << "SLLS:draw start ALOG.run()\n";
    // while (!ALOG.run());
    // std::cerr << "SLLS:draw end ALOG.run()\n";
    ALOG.run();
    obj.draw();
    ALOG.draw(!inputActive);
    exitMessage.draw(10, 865, RED);
    Layout::drawTopNavigation();
    
    GuiUnlock();
    GuiFileDialog(&fileDialogState);
}

void Screen::ScreenSinglyLinkedList::destroy() {
    obj.destroy();
    ALOG.destroy();
}
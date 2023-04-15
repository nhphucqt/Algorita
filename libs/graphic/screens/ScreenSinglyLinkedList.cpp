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

    exitMessage = StyledText(std::string(), Gfont::defaultFont);

    ALOG.setMainObj(&obj);

    fileDialogState = InitGuiFileDialog(Gui::FILE_DIALOG_WIDTH, Gui::FILE_DIALOG_HEIGHT, GetWorkingDirectory(), false);
}

void Screen::ScreenSinglyLinkedList::draw() {
    if (fileDialogState.windowActive) {
        GuiLock();
    }
    // Create type Button
    if (GuiButton(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Create")) {
        currOperationType = currOperationType == CREATE ? OTNULL : CREATE;
    }
    if (currOperationType == CREATE) {
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Empty")) {
            exitMessage.assign(obj.initialize(0, &ALOG).message);
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Random")) {
            exitMessage.assign(obj.initialize(GetRandomValue(1, Core::MAX_NUM_NODE_SLL), &ALOG).message);
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6, Gui::USER_DEF_BUTTON_WIDTH, Gui::USER_DEF_BUTTON_HEIGHT}, "Input")) {
            currOperation = currOperation == CREATE_USER_DEF ? ONULL : CREATE_USER_DEF;
        }
        if (currOperation == CREATE_USER_DEF) {
            GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5, Gui::USER_DEF_BUTTON_WIDTH, Gui::USER_DEF_BUTTON_HEIGHT}, "");
            inputUserDefined.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::USER_DEF_BUTTON_WIDTH - Gui::BUTTON_OPER_GO_WIDTH - 5, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, "Go")) {
                exitMessage.assign(obj.initialize(inputUserDefined.getStr(), &ALOG).message);
            }
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::USER_DEF_BUTTON_WIDTH + Gui::BUTTON_OPER_DIST_X, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 6, Gui::FILE_DIALOG_OPEN_BUTTON_WIDTH, Gui::FILE_DIALOG_OPEN_BUTTON_HEIGHT}, "File")) {
            fileDialogState.windowActive = true;
        }
    }
    // Search type Button
    if (GuiButton(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Search")) {
        currOperationType = currOperationType == SEARCH ? OTNULL : SEARCH;
    }
    if (currOperationType == SEARCH) {
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "First value")) {
            currOperation = currOperation == SEARCH_FIRST ? ONULL : SEARCH_FIRST;
        }
        if (currOperation == SEARCH_FIRST) {
            GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "");
            GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "v =");
            inputSearchFirst.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
                inputSearchFirst.setnum(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
            }
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, "Go")) {
                exitMessage.assign(obj.searchFirst(inputSearchFirst.getNum(), &ALOG).message);
            }
        }
    }
    // Insert type Button
    if (GuiButton(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Insert")) {
        currOperationType = currOperationType == INSERT ? OTNULL : INSERT;
    }
    if (currOperationType == INSERT) {
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Head")) {
            currOperation = currOperation == INSERT_FORD ? ONULL : INSERT_FORD;
        }
        if (currOperation == INSERT_FORD) {
            GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "");
            GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "v =");
            inputInsertFord.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
                inputInsertFord.setnum(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
            }
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, "Go")) {
                exitMessage.assign(obj.pushFront(inputInsertFord.getNum(), &ALOG).message);
            }
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Tail")) {
            currOperation = currOperation == INSERT_BACK ? ONULL : INSERT_BACK;
        }
        if (currOperation == INSERT_BACK) {
            GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "");
            GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "v =");
            inputInsertBack.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
                inputInsertBack.setnum(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
            }
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, "Go")) {
                exitMessage.assign(obj.pushBack(inputInsertBack.getNum(), &ALOG).message);
            }
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "i-th node")) {
            currOperation = currOperation == INSERT_MIDD ? ONULL : INSERT_MIDD;
        }
        if (currOperation == INSERT_MIDD) {
            GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT * 2}, "");
            GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "i =");
            inputInsertMiddPos.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
                inputInsertMiddPos.setnum(GetRandomValue(0, obj.size()));
            }
            GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "v =");
            inputInsertMiddVal.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
                inputInsertMiddVal.setnum(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
            }
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT * 2 + 10}, "Go")) {
                exitMessage.assign(obj.pushAtKth(inputInsertMiddPos.getNum(), inputInsertMiddVal.getNum(), &ALOG).message);
            }
        }
    }
    // Update type Button
    if (GuiButton(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Update")) {
        currOperationType = currOperationType == UPDATE ? OTNULL : UPDATE;
    }
    if (currOperationType == UPDATE) {
        GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT * 2}, "");
        GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "i =");
        inputUpdateValuePos.draw();
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
            if (obj.empty()) {
                exitMessage.assign("The list is empty");
            } else {
                inputUpdateValuePos.setnum(GetRandomValue(0, obj.size()-1));
            }
        }
        GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "v =");
        inputUpdateValueVal.draw();
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
            inputUpdateValueVal.setnum(GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE));
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT * 2 + 10}, "Go")) {
            exitMessage.assign(obj.updateValue(inputUpdateValuePos.getNum(), inputUpdateValueVal.getNum(), &ALOG).message);
        }
    }
    
    // Remove type Button
    if (GuiButton(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Remove")) {
        currOperationType = currOperationType == REMOVE ? OTNULL : REMOVE;
    }
    if (currOperationType == REMOVE) {
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Head")) {
            exitMessage.assign(obj.popFront(&ALOG).message);
        } 
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Tail")) {
            exitMessage.assign(obj.popBack(&ALOG).message);
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "i-th node")) {
            currOperation = currOperation == REMOVE_MIDD ? ONULL : REMOVE_MIDD;
        }
        if (currOperation == REMOVE_MIDD) {
            GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 1, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "");
            GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 3 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 1, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "i =");
            inputRemoveMidd.draw();
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
    ALOG.draw();
    exitMessage.draw(10, 865, RED);
    Layout::drawTopNavigation();
    
    GuiUnlock();
    GuiFileDialog(&fileDialogState);
}

void Screen::ScreenSinglyLinkedList::destroy() {
    obj.destroy();
    ALOG.destroy();
}
#include "ScreenSinglyLinkedList.h"

Screen::ScreenSinglyLinkedList::ScreenSinglyLinkedList() { // Ensure that obj has to be destroy before (prevent MEMORY LEAKING)
    obj = GraphicSinglyLinkedList();
    inputSearchFirst = GuiTextBoxState(Rectangle{175, 760, 45, 35}, "", Graphic::MAX_SIZE_INPUT, false);
    inputInsertFord = GuiTextBoxState(Rectangle{191, 795, 45, 35}, "", Graphic::MAX_SIZE_INPUT, false);
    inputInsertBack = GuiTextBoxState(Rectangle{367, 795, 45, 35}, "", Graphic::MAX_SIZE_INPUT, false);
    inputInsertMiddPos = GuiTextBoxState(Rectangle{507, 795, 45, 35}, "", Graphic::MAX_SIZE_INPUT, false);
    inputInsertMiddVal = GuiTextBoxState(Rectangle{597, 795, 45, 35}, "", Graphic::MAX_SIZE_INPUT, false);
    inputRemoveMidd = GuiTextBoxState{Rectangle{597, 830, 45, 35}, "", Graphic::MAX_SIZE_INPUT, false};

    exitMessage = StyledText(std::string(), Gfont::defaultFont);

    ALOG.setMainObj(&obj);
}

void Screen::ScreenSinglyLinkedList::draw() {
    // Create type Button
    if (GuiButton(Rectangle{0, 690, 100, 35}, "Create") || currOperationType == OperationType::CREATE) {
        currOperationType = OperationType::CREATE;
        if (GuiButton(Rectangle{110, 690, 80, 35}, "Empty")) {
            exitMessage.assign(obj.initialize(0, &ALOG).message);
        }
        if (GuiButton(Rectangle{200, 690, 90, 35}, "Random")) {
            exitMessage.assign(obj.initialize(GetRandomValue(1, Core::MAX_NUM_NODE_SLL), &ALOG).message);
        }
    }
    // Search type Button
    if (GuiButton(Rectangle{0, 725, 100, 35}, "Search") || currOperationType == OperationType::SEARCH) {
        currOperationType = OperationType::SEARCH;
        if (GuiButton(Rectangle{110, 725, 150, 35}, "First value") || currOperation == Operation::SEARCH_FIRST) {
            currOperation = Operation::SEARCH_FIRST;
            GuiLabel(Rectangle{130, 760, 45, 35}, "v = ");
            inputSearchFirst.draw();
            if (GuiButton(Rectangle{220, 760, 40, 35}, "Go")) {
                exitMessage.assign(obj.searchFirst(inputSearchFirst.getNum(), &ALOG).message);
            }
        }
    }
    // Insert type Button
    if (GuiButton(Rectangle{0, 760, 100, 35}, "Insert") || currOperationType == OperationType::INSERT) {
        currOperationType = OperationType::INSERT;
        if (GuiButton(Rectangle{110, 760, 166, 35}, "i = 0 (Head)") || currOperation == Operation::INSERT_FORD) {
            currOperation = Operation::INSERT_FORD;
            GuiLabel(Rectangle{146, 795, 45, 35}, "v = ");
            inputInsertFord.draw();
            if (GuiButton(Rectangle{236, 795, 40, 35}, "Go")) {
                exitMessage.assign(obj.pushFront(inputInsertFord.getNum(), &ALOG).message);
            }
        }
        if (GuiButton(Rectangle{286, 760, 166, 35}, "i = N-1 (Tail)") || currOperation == Operation::INSERT_BACK) {
            currOperation = Operation::INSERT_BACK;
            GuiLabel(Rectangle{322, 795, 45, 35}, "v = ");
            inputInsertBack.draw();
            if (GuiButton(Rectangle{412, 795, 40, 35}, "Go")) {
                exitMessage.assign(obj.pushBack(inputInsertBack.getNum(), &ALOG).message);
            }
        }
        if (GuiButton(Rectangle{462, 760, 220, 35}, "Specific position i") || currOperation == Operation::INSERT_MIDD) {
            currOperation = Operation::INSERT_MIDD;
            GuiLabel(Rectangle{462, 795, 45, 35}, "i = ");
            inputInsertMiddPos.draw();
            GuiLabel(Rectangle{552, 795, 45, 35}, "v = ");
            inputInsertMiddVal.draw();
            if (GuiButton(Rectangle{642, 795, 40, 35}, "Go")) {
                exitMessage.assign(obj.pushAtKth(inputInsertMiddPos.getNum(), inputInsertMiddVal.getNum(), &ALOG).message);
            }
        }
    }
    // Remove type Button
    if (GuiButton(Rectangle{0, 795, 100, 35}, "Remove") || currOperationType == OperationType::REMOVE) {
        currOperationType = OperationType::REMOVE;
        if (GuiButton(Rectangle{110, 795, 166, 35}, "i = 0 (Head)")) {
            exitMessage.assign(obj.popFront(&ALOG).message);
        } 
        if (GuiButton(Rectangle{286, 795, 166, 35}, "i = N-1 (Tail)")) {
            exitMessage.assign(obj.popBack(&ALOG).message);
        }
        if (GuiButton(Rectangle{462, 795, 220, 35}, "Specific position i") || currOperation == Operation::REMOVE_MIDD) {
            currOperation = Operation::REMOVE_MIDD;
            GuiLabel(Rectangle{552, 830, 45, 35}, "i = ");
            inputRemoveMidd.draw();
            if (GuiButton(Rectangle{642, 830, 40, 35}, "Go")) {
                // exitMessage.assign(obj.popAtKth(inputRemoveMidd.getNum()).message);
            }
        }
    }

    // std::cerr << "SLLS:draw start ALOG.run()\n";
    // while (!ALOG.run());
    // std::cerr << "SLLS:draw end ALOG.run()\n";
    ALOG.run();

    if (GuiButton(Rectangle{500, Window::HEIGHT-35, 35, 35}, "<<")) {
        ALOG.toFirstState();
    }

    if (GuiButton(Rectangle{500+(35+5)*1, Window::HEIGHT-35, 35, 35}, "<")) {
        ALOG.runPrev(Animate::RUN_STEP);
    }

    if (GuiButton(Rectangle{500+(35+5)*2, Window::HEIGHT-35, 35, 35}, ">")) {
        ALOG.runNext(Animate::RUN_STEP);
    }

    if (GuiButton(Rectangle{500+(35+5)*3, Window::HEIGHT-35, 35, 35}, ">>")) {
        ALOG.toLastState();
    }

    obj.draw();
    // codeblock.draw(Window::DIMENSION - codeblock.getBlockDimension());
    // std::cerr << " >> ALOG.draw() \n";
    ALOG.draw();
    exitMessage.draw(10, 865, RED);
}

void Screen::ScreenSinglyLinkedList::destroy() {
    obj.destroy();
    ALOG.destroy();
}
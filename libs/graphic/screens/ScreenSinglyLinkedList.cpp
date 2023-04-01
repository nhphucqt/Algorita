#include "ScreenSinglyLinkedList.h"

Screen::ScreenSinglyLinkedList::ScreenSinglyLinkedList() { // Ensure that obj has to be destroy before (prevent MEMORY LEAKING)
    obj = GraphicSinglyLinkedList();
    inputSearch = GuiTextBoxState(Rectangle{173, 700, 100, 40}, "", Graphic::MAX_SIZE_INPUT, false);
    inputInsertFord = GuiTextBoxState(Rectangle{181, 792, 75, 40}, "", Graphic::MAX_SIZE_INPUT, false);
    inputInsertBack = GuiTextBoxState(Rectangle{357, 792, 75, 40}, "", Graphic::MAX_SIZE_INPUT, false);
    inputInsertMiddPos = GuiTextBoxState(Rectangle{533, 792, 75, 40}, "", Graphic::MAX_SIZE_INPUT, false);
    inputInsertMiddVal = GuiTextBoxState(Rectangle{659, 792, 75, 40}, "", Graphic::MAX_SIZE_INPUT, false);
    inputRemoveMidd = GuiTextBoxState{Rectangle{533, 840, 146, 40}, "", Graphic::MAX_SIZE_INPUT, false};

    currOperationType = -1;
    currOperation = -1;
}

void Screen::ScreenSinglyLinkedList::draw() {
    // std::cerr << GetRandomValue(Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE) << '\n';
    obj.draw();
    if (GuiButton(Rectangle{0, 645, 120, 50}, "Create") || currOperationType == TYPE_OPERATION_CREATE) {
        currOperationType = TYPE_OPERATION_CREATE;
        if (GuiButton(Rectangle{130, 650, 106, 40}, "Empty")) {
            obj.initialize(0);
        }
        if (GuiButton(Rectangle{246, 650, 112, 40}, "Random")) {
            obj.initialize(GetRandomValue(1, 10));
        }
    }
    if (GuiButton(Rectangle{0, 695, 120, 50}, "Search") || currOperationType == TYPE_OPERATION_SEARCH) {
        currOperationType = TYPE_OPERATION_SEARCH;
        GuiLabel(Rectangle{125, 700, 48, 40}, "v = ");
        inputSearch.draw();
        if (GuiButton(Rectangle{285, 700, 40, 40}, "Go")) {
            currOperation = OPERATION_SEARCH;
        }
    }
    if (GuiButton(Rectangle{0, 745, 120, 50}, "Insert") || currOperationType == TYPE_OPERATION_INSERT) {
        currOperationType = TYPE_OPERATION_INSERT;
        if (GuiButton(Rectangle{130, 752, 166, 40}, "i = 0 (Head)") || currOperation == OPERATION_INSERT_FORD) {
            currOperation = OPERATION_INSERT_FORD;
            GuiLabel(Rectangle{130, 792, 51, 40}, "v = ");
            inputInsertFord.draw();
            if (GuiButton(Rectangle{256, 792, 40, 40}, "Go")) {
                obj.pushFront(inputInsertFord.getNum());
            }
        }
        if (GuiButton(Rectangle{306, 752, 166, 40}, "i = N-1 (Tail)") || currOperation == OPERATION_INSERT_BACK) {
            currOperation = OPERATION_INSERT_BACK;
            GuiLabel(Rectangle{306, 792, 51, 40}, "v = ");
            inputInsertBack.draw();
            if (GuiButton(Rectangle{432, 792, 40, 40}, "Go")) {
                obj.pushBack(inputInsertBack.getNum());
            }
        }
        if (GuiButton(Rectangle{482, 752, 292, 40}, "Specific position i") || currOperation == OPERATION_INSERT_MIDD) {
            currOperation = OPERATION_INSERT_MIDD;
            GuiLabel(Rectangle{482, 792, 51, 40}, "i = ");
            inputInsertMiddPos.draw();
            GuiLabel(Rectangle{608, 792, 51, 40}, "v = ");
            inputInsertMiddVal.draw();
            if (GuiButton(Rectangle{734, 792, 40, 40}, "Go")) {
                obj.pushAtKth(inputInsertMiddPos.getNum(), inputInsertMiddVal.getNum());
            }
        }
    }
    if (GuiButton(Rectangle{0, 795, 120, 50}, "Remove") || currOperationType == TYPE_OPERATION_REMOVE) {
        currOperationType = TYPE_OPERATION_REMOVE;
        if (GuiButton(Rectangle{130, 800, 166, 40}, "i = 0 (Head)")) {
            obj.popFront();
        } 
        if (GuiButton(Rectangle{306, 800, 166, 40}, "i = N-1 (Tail)")) {
            obj.popBack();
        }
        if (GuiButton(Rectangle{482, 800, 237, 40}, "Specific position i") || currOperation == OPERATION_REMOVE_MIDD) {
            currOperation = OPERATION_REMOVE_MIDD;
            GuiLabel(Rectangle{482, 840, 51, 40}, "i = ");
            inputRemoveMidd.draw();
            if (GuiButton(Rectangle{679, 840, 40, 40}, "Go")) {
                obj.popAtKth(inputRemoveMidd.getNum());
            }
        }
    }
}

void Screen::ScreenSinglyLinkedList::destroy() {
    obj.destroy();
}
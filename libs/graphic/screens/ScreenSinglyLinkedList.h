#ifndef SCREEN_SINGLY_LINKED_LIST_H
#define SCREEN_SINGLY_LINKED_LIST_H

#include <string.h>

#include "../../conf_raylib.h"

#include "../objects/GraphicSinglyLinkedList.h"
#include "../../rcore/rguiTextBox.h"
#include "../../animation/ListOfOperationsGroups.h"
#include "../gui/Codeblock.h"

namespace Screen {
    class ScreenSinglyLinkedList {
    private:
        enum OperationType {OTNULL, CREATE, SEARCH, INSERT, REMOVE} currOperationType;
        enum Operation {ONULL, SEARCH_FIRST, INSERT_FORD, INSERT_BACK, INSERT_MIDD, REMOVE_MIDD} currOperation;

        GraphicSinglyLinkedList obj;

        GuiTextBoxState inputSearchFirst;
        GuiTextBoxState inputInsertFord, inputInsertBack;
        GuiTextBoxState inputInsertMiddPos, inputInsertMiddVal;
        GuiTextBoxState inputRemoveMidd;

        StyledText exitMessage;

        ListOfOperationsGroups<GraphicSinglyLinkedList> ALOG;
        Codeblock codeblock;

    public:
        ScreenSinglyLinkedList();

        void draw();

        void destroy();
    };

}


#endif
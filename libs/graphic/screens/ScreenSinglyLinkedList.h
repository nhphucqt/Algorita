#ifndef SCREEN_SINGLY_LINKED_LIST_H
#define SCREEN_SINGLY_LINKED_LIST_H

#include <string.h>

#include "../../conf_raylib.h"

#include "../objects/GraphicSinglyLinkedList.h"
#include "../../rcore/rguiTextBox.h"

namespace Screen {
    class ScreenSinglyLinkedList {
    private:
        const int TYPE_OPERATION_CREATE = 0;
        const int TYPE_OPERATION_SEARCH = 1;
        const int TYPE_OPERATION_INSERT = 2;
        const int TYPE_OPERATION_REMOVE = 3;

        const int OPERATION_SEARCH = 0;
        const int OPERATION_INSERT_FORD = 1;
        const int OPERATION_INSERT_BACK = 2;
        const int OPERATION_INSERT_MIDD = 3;
        const int OPERATION_REMOVE_MIDD = 4;

        int currOperationType;
        int currOperation;
        GraphicSinglyLinkedList obj;

        GuiTextBoxState inputSearch, inputInsertFord, inputInsertBack;
        GuiTextBoxState inputInsertMiddPos, inputInsertMiddVal;
        GuiTextBoxState inputRemoveMidd;

    public:
        ScreenSinglyLinkedList();

        void draw();

        void destroy();
    };

}


#endif
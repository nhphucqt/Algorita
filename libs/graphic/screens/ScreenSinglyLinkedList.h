#ifndef SCREEN_SINGLY_LINKED_LIST_H
#define SCREEN_SINGLY_LINKED_LIST_H

#include <string.h>

#include "../../conf_raylib.h"

#include "../objects/GraphicSinglyLinkedList.h"
#include "../../rcore/rguiTextBox.h"
#include "../../rcore/rRectangle.h"
#include "../../animation/ListOfOperationsGroups.h"
#include "../gui/Codeblock.h"
#include "../../core/userfunc.h"

#include "../../external/gui_file_dialog.h"

#include "globalLayout.h"

namespace Screen {
    class ScreenSinglyLinkedList {
    private:
        enum OperationType {OTNULL, CREATE, SEARCH, INSERT, REMOVE} currOperationType;
        enum Operation {ONULL, CREATE_USER_DEF, SEARCH_FIRST, INSERT_FORD, INSERT_BACK, INSERT_MIDD, REMOVE_MIDD} currOperation;

        GraphicSinglyLinkedList obj;

        GuiTextBoxState inputSearchFirst;
        GuiTextBoxState inputInsertFord, inputInsertBack;
        GuiTextBoxState inputInsertMiddPos, inputInsertMiddVal;
        GuiTextBoxState inputRemoveMidd;
        GuiTextBoxState inputUserDefined;

        StyledText exitMessage;

        ListOfOperationsGroups<GraphicSinglyLinkedList> ALOG;

        GuiFileDialogState fileDialogState;

    public:
        ScreenSinglyLinkedList();

        void draw();

        void destroy();
    };

}


#endif
#ifndef SCREEN_DOUBLY_LINKED_LIST_H
#define SCREEN_DOUBLY_LINKED_LIST_H

#include <string.h>

#include "../../conf_raylib.h"

#include "../objects/GraphicDoublyLinkedList.h"
#include "../../animation/ListOfOperationsGroups.h"
#include "../gui/Codeblock.h"
#include "../../core/userfunc.h"

#include "../../rcore/rguiTextBox.h"
#include "../../rcore/rguiToggle.h"
#include "../../rcore/rRectangle.h"

#include "../../external/gui_file_dialog.h"

#include "globalLayout.h"

namespace Screen {
    class ScreenDoublyLinkedList {
    private:
        enum OperationType {OTNULL, CREATE, SEARCH, INSERT, UPDATE, REMOVE} currOperationType;
        enum Operation {ONULL, CREATE_USER_DEF, SEARCH_FIRST, INSERT_FORD, INSERT_BACK, INSERT_MIDD, REMOVE_MIDD} currOperation;

        GraphicDoublyLinkedList obj;

        GuiTextBoxState inputSearchFirst;
        GuiTextBoxState inputInsertFord, inputInsertBack;
        GuiTextBoxState inputInsertMiddPos, inputInsertMiddVal;
        GuiTextBoxState inputUpdateValuePos, inputUpdateValueVal;
        GuiTextBoxState inputRemoveMidd;
        GuiTextBoxState inputUserDefined;

        GuiToggleState toggleCreateType;
        GuiToggleState toggleSearchType;
        GuiToggleState toggleInsertType;
        GuiToggleState toggleUpdateType;
        GuiToggleState toggleRemoveType;
        
        GuiToggleState toggleUserDefine;
        GuiToggleState toggleSearchFirst;
        GuiToggleState toggleInsertFord;
        GuiToggleState toggleInsertBack;
        GuiToggleState toggleInsertMidd;
        GuiToggleState toggleRemoveMidd;

        StyledText exitMessage;

        ListOfOperationsGroups<GraphicDoublyLinkedList> ALOG;

        GuiFileDialogState fileDialogState;

    public:
        ScreenDoublyLinkedList();

        void load();
        void init();
        void draw();
        void destroy();
    };
}

#endif
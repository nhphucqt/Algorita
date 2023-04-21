#ifndef SCREEN_DYNAMIC_ARRAY_H
#define SCREEN_DYNAMIC_ARRAY_H

#include <string.h>

#include "../../conf_raylib.h"

#include "../objects/GraphicDynamicArray.h"
#include "../../animation/ListOfOperationsGroups.h"
#include "../gui/Codeblock.h"
#include "../../core/userfunc.h"

#include "../../rcore/rguiTextBox.h"
#include "../../rcore/rguiToggle.h"
#include "../../rcore/rRectangle.h"

#include "../gui/guiTinyDialog.h"

#include "globalLayout.h"

namespace Screen {
    class ScreenDynamicArray {
    private:
        enum OperationType {OTNULL, CREATE, SEARCH, ACCESS, INSERT, UPDATE, REMOVE} currOperationType;
        enum Operation {ONULL, CREATE_ALL_ZEROS, CREATE_RANDOM, CREATE_USER_DEF, CREATE_FILE, SEARCH_FIRST, INSERT_BACK, REMOVE_BACK} currOperation;

        GraphicDynamicArray obj;

        GuiTextBoxState inputCreateAllZeros;
        GuiTextBoxState inputCreateRandom;
        GuiTextBoxState inputUserDefined;
        GuiTextBoxState inputSearchFirst;
        GuiTextBoxState inputAccessValue;
        GuiTextBoxState inputUpdateValuePos, inputUpdateValueVal;
        GuiTextBoxState inputInsertBack;

        GuiToggleState toggleCreateType;
        GuiToggleState toggleCreateAllZeros;
        GuiToggleState toggleCreateRandom;

        GuiToggleState toggleSearchType;
        GuiToggleState toggleAccessType;
        GuiToggleState toggleUpdateType;
        GuiToggleState toggleInsertType;
        GuiToggleState toggleInsertBack;
        GuiToggleState toggleRemoveType;
        
        GuiToggleState toggleUserDefine;
        GuiToggleState toggleSearchFirst;

        StyledText exitMessage;

        ListOfOperationsGroups<GraphicDynamicArray> ALOG;
        
    public:
        ScreenDynamicArray();

        void load();
        void init();
        void draw();
        void destroy();
    };
}

#endif
#ifndef SCREEN_STATIC_ARRAY_H
#define SCREEN_STATIC_ARRAY_H

#include <cstring>

#include "../../conf_raylib.h"

#include "../objects/GraphicStaticArray.h"
#include "../../animation/ListOfOperationsGroups.h"
#include "../gui/Codeblock.h"
#include "../../core/userfunc.h"

#include "../../rcore/rguiTextBox.h"
#include "../../rcore/rguiToggle.h"
#include "../../rcore/rRectangle.h"

#include "../gui/guiTinyDialog.h"

#include "globalLayout.h"

namespace Screen {
    class ScreenStaticArray {
    private:
        enum OperationType {OTNULL, CREATE, SEARCH, ACCESS, INSERT, UPDATE, REMOVE} currOperationType;
        enum Operation {ONULL, CREATE_ALL_ZEROS, CREATE_RANDOM, CREATE_USER_DEF, CREATE_FILE, SEARCH_FIRST, INSERT_FORD, INSERT_BACK, INSERT_MIDD, REMOVE_FORD, REMOVE_BACK, REMOVE_MIDD} currOperation;

        GraphicStaticArray obj;

        GuiTextBoxState inputCreateAllZerosCapa, inputCreateAllZerosSize;
        GuiTextBoxState inputCreateRandomCapa, inputCreateRandomSize;
        GuiTextBoxState inputUserDefinedCapa, inputUserDefinedVals;
        GuiTextBoxState inputSearchFirst;
        GuiTextBoxState inputAccessValue;
        GuiTextBoxState inputUpdateValuePos, inputUpdateValueVal;
        GuiTextBoxState inputInsertFord, inputInsertBack;
        GuiTextBoxState inputInsertMiddPos, inputInsertMiddVal;
        GuiTextBoxState inputRemoveMidd;

        GuiToggleState toggleCreateType;
        GuiToggleState toggleCreateAllZeros;
        GuiToggleState toggleCreateRandom;

        GuiToggleState toggleSearchType;
        GuiToggleState toggleAccessType;
        GuiToggleState toggleUpdateType;

        GuiToggleState toggleInsertType;
        GuiToggleState toggleInsertFord, toggleInsertBack, toggleInsertMidd;
        
        GuiToggleState toggleRemoveType;
        GuiToggleState toggleRemoveMidd;
        
        GuiToggleState toggleUserDefine;
        GuiToggleState toggleSearchFirst;

        StyledText exitMessage;

        ListOfOperationsGroups ALOG;
        
    public:
        ScreenStaticArray();

        void load();
        void init();
        void draw();
        void destroy();
    };
}

#endif
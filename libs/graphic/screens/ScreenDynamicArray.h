#ifndef SCREEN_DYNAMIC_ARRAY_H
#define SCREEN_DYNAMIC_ARRAY_H

#include <cstring>

#include "../../conf_raylib.h"

#include "../objects/GraphicDynamicArray.h"
#include "../../animation/ListOfOperationsGroups.h"
#include "../gui/Codeblock.h"
#include "../../core/userfunc.h"
#include "ScreenView.h"

#include "../../rcore/rguiTextBox.h"
#include "../../rcore/rguiToggle.h"
#include "../../rcore/rRectangle.h"

#include "../gui/guiTinyDialog.h"

#include "globalLayout.h"

namespace Screen {
    class ScreenDynamicArray: public ScreenView {
    private:
        enum OperationType {OTNULL, CREATE, SEARCH, ACCESS, INSERT, UPDATE, REMOVE} currOperationType;
        enum Operation {ONULL, CREATE_ALL_ZEROS, CREATE_RANDOM, CREATE_USER_DEF, CREATE_FILE, SEARCH_FIRST, INSERT_FORD, INSERT_BACK, INSERT_MIDD, REMOVE_FORD, REMOVE_BACK, REMOVE_MIDD} currOperation;

        GraphicDynamicArray obj;

        GuiTextBoxState inputCreateAllZeros;
        GuiTextBoxState inputCreateRandom;
        GuiTextBoxState inputUserDefined;
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
        ScreenDynamicArray();
        ~ScreenDynamicArray() override;

        void load() override;
        void init() override;
        void draw() override;
        void destroy() override;
    };
}

#endif
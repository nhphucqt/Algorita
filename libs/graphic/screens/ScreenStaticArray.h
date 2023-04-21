#ifndef SCREEN_STATIC_ARRAY_H
#define SCREEN_STATIC_ARRAY_H

#include <string.h>

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
        enum OperationType {OTNULL, CREATE, SEARCH, INSERT, UPDATE, REMOVE} currOperationType;
        enum Operation {ONULL, CREATE_ALL_ZEROS, CREATE_RANDOM, CREATE_USER_DEF, CREATE_FILE, SEARCH_FIRST} currOperation;

        GraphicStaticArray obj;

        GuiTextBoxState inputCreateAllZeros;
        GuiTextBoxState inputCreateRandom;
        GuiTextBoxState inputUserDefined;
        GuiTextBoxState inputSearchFirst;
        GuiTextBoxState inputAccessValue;
        GuiTextBoxState inputUpdateValuePos, inputUpdateValueVal;
        GuiTextBoxState inputRemoveMidd;

        GuiToggleState toggleCreateType;
        GuiToggleState toggleCreateAllZeros;
        GuiToggleState toggleCreateRandom;

        GuiToggleState toggleSearchType;
        GuiToggleState toggleAccessType;
        GuiToggleState toggleUpdateType;
        
        GuiToggleState toggleUserDefine;
        GuiToggleState toggleSearchFirst;

        StyledText exitMessage;

        ListOfOperationsGroups<GraphicStaticArray> ALOG;
        
    public:
        ScreenStaticArray();

        void load();
        void init();
        void draw();
        void destroy();
    };
}


#endif
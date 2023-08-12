#ifndef SCREEN_HEAP_MAX_H
#define SCREEN_HEAP_MAX_H

#include <cstring>

#include "../../conf_raylib.h"

#include "../objects/GraphicHeap.h"
#include "../../animation/ListOfOperationsGroups.h"
#include "../gui/Codeblock.h"
#include "../../core/userfunc.h"
#include "ScreenView.h"

#include "../../rcore/rguiTextBox.h"
#include "../../rcore/rguiToggle.h"
#include "../../rcore/rRectangle.h"

#include "../gui/guiTinyDialog.h"

#include "globalLayoutCs163.h"

namespace Screen {
    class ScreenHeapMax: public ScreenView {
    private:
        enum OperationType {OTNULL, CREATE, SEARCH, INSERT, REMOVE, GET_SIZE} currOperationType;
        enum Operation {ONULL, CREATE_EMPTY, CREATE_RANDOM, CREATE_USER_DEF, CREATE_FILE} currOperation;

        GraphicHeap obj;

        GuiTextBoxState inputCreateRandomSize;
        GuiTextBoxState inputUserDefinedVals;
        GuiTextBoxState inputInsert;
        GuiTextBoxState inputRemove;

        GuiToggleState toggleCreateType;
        GuiToggleState toggleCreateRandom;

        GuiToggleState toggleInsertType;
        GuiToggleState toggleRemoveType;
        GuiToggleState toggleUserDefine;

        StyledText exitMessage;

        ListOfOperationsGroups ALOG;
        
    public:
        ScreenHeapMax();
        ~ScreenHeapMax() override;

        void load() override;
        void init() override;
        void draw() override;
        void destroy() override;
    };
}

#endif
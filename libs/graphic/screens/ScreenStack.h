#ifndef SCREEN_STACK_H
#define SCREEN_STACK_H

#include <string.h>

#include "../../conf_raylib.h"

#include "../objects/GraphicStack.h"
#include "../../animation/ListOfOperationsGroups.h"
#include "../gui/Codeblock.h"
#include "../../core/userfunc.h"

#include "../../rcore/rguiTextBox.h"
#include "../../rcore/rguiToggle.h"
#include "../../rcore/rRectangle.h"

#include "../gui/guiTinyDialog.h"

#include "globalLayout.h"

namespace Screen {
    class ScreenStack {
    private:
        enum OperationType {OTNULL, CREATE, PEEK, UPDATE, PUSH, POP} currOperationType;
        enum Operation {ONULL, CREATE_EMPTY, CREATE_RANDOM, CREATE_USER_DEF, CREATE_FILE} currOperation;

        GraphicStack obj;
        GuiTextBoxState inputUpdate;
        GuiTextBoxState inputPush;
        GuiTextBoxState inputUserDefined;

        GuiToggleState toggleCreateType;
        GuiToggleState toggleUpdateType;
        GuiToggleState togglePushType;
        
        GuiToggleState toggleUserDefine;


        StyledText exitMessage;

        ListOfOperationsGroups<GraphicStack> ALOG;

    public:
        ScreenStack();

        void load();
        void init();
        void draw();
        void destroy();
    };

}


#endif
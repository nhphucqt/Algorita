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

#include "../../external/gui_file_dialog.h"

#include "globalLayout.h"

namespace Screen {
    class ScreenStack {
    private:
        enum OperationType {OTNULL, CREATE, PEEK, PUSH, POP} currOperationType;
        enum Operation {ONULL, CREATE_USER_DEF} currOperation;

        GraphicStack obj;

        GuiTextBoxState inputPush;
        GuiTextBoxState inputUserDefined;

        GuiToggleState toggleCreateType;
        GuiToggleState toggleSearchType;
        GuiToggleState togglePushType;
        
        GuiToggleState toggleUserDefine;


        StyledText exitMessage;

        ListOfOperationsGroups<GraphicStack> ALOG;

        GuiFileDialogState fileDialogState;

    public:
        ScreenStack();

        void load();
        void init();
        void draw();
        void destroy();
    };

}


#endif
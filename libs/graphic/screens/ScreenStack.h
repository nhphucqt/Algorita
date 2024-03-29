#ifndef SCREEN_STACK_H
#define SCREEN_STACK_H

#include <cstring>

#include "../../conf_raylib.h"

#include "../objects/GraphicStack.h"
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
    class ScreenStack: public ScreenView {
    private:
        enum OperationType {OTNULL, CREATE, PEEK, UPDATE, PUSH, POP, CLEAR} currOperationType;
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

        ListOfOperationsGroups ALOG;

    public:
        ScreenStack();
        ~ScreenStack() override;

        void load() override;
        void init() override;
        void draw() override;
        void destroy() override;
    };

}


#endif
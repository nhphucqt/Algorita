#ifndef SCREEN_QUEUE_H
#define SCREEN_QUEUE_H

#include <string.h>

#include "../../conf_raylib.h"

#include "../objects/GraphicQueue.h"
#include "../../animation/ListOfOperationsGroups.h"
#include "../gui/Codeblock.h"
#include "../../core/userfunc.h"

#include "../../rcore/rguiTextBox.h"
#include "../../rcore/rguiToggle.h"
#include "../../rcore/rRectangle.h"

#include "../gui/guiTinyDialog.h"

#include "globalLayout.h"

namespace Screen {
    class ScreenQueue {
    private:
        enum OperationType {OTNULL, CREATE, PEEK, UPDATE, PUSH, POP} currOperationType;
        enum Operation {ONULL, CREATE_USER_DEF} currOperation;

        GraphicQueue obj;

        GuiTextBoxState inputUpdate;
        GuiTextBoxState inputPush;
        GuiTextBoxState inputUserDefined;

        GuiToggleState toggleCreateType;
        GuiToggleState toggleUpdateType;
        GuiToggleState toggleSearchType;
        GuiToggleState togglePushType;
        
        GuiToggleState toggleUserDefine;


        StyledText exitMessage;

        ListOfOperationsGroups<GraphicQueue> ALOG;

        // GuiFileDialogState fileDialogState;

    public:
        ScreenQueue();

        void load();
        void init();
        void draw();
        void destroy();
    };

}


#endif
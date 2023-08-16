#ifndef SCREEN_TRIE_H
#define SCREEN_TRIE_H

#include <cstring>

#include "../../conf_raylib.h"

#include "../objects/GraphicTrie.h"
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
    class ScreenTrie: public ScreenView {
    private:
        enum OperationType {OTNULL, CREATE, SEARCH, INSERT, REMOVE} currOperationType;
        enum Operation {ONULL, CREATE_EMPTY, CREATE_RANDOM, CREATE_USER_DEF, CREATE_FILE} currOperation;

        GraphicTrie obj;

        GuiTextBoxState inputCreateRandomSize;
        GuiTextBoxState inputUserDefinedVals;
        GuiTextBoxState inputSearch;
        GuiTextBoxState inputInsert;
        GuiTextBoxState inputRemove;

        GuiToggleState toggleCreateType;
        GuiToggleState toggleCreateRandom;

        GuiToggleState toggleSearchType;
        GuiToggleState toggleInsertType;
        GuiToggleState toggleRemoveType;
        GuiToggleState toggleUserDefine;

        StyledText exitMessage;

        ListOfOperationsGroups ALOG;
        
    public:
        ScreenTrie();
        ~ScreenTrie() override;

        void load() override;
        void init() override;
        void draw() override;
        void destroy() override;
    };
}

#endif
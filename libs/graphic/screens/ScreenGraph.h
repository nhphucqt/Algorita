#ifndef SCREEN_GRAPH_H
#define SCREEN_GRAPH_H

#include <cstring>

#include "../../conf_raylib.h"

#include "../objects/GraphicGraph.h"
#include "../../animation/ListOfOperationsGroups.h"
#include "../gui/Codeblock.h"
#include "../../core/userfunc.h"
#include "ScreenView.h"

#include "../../rcore/rguiTextBox.h"
#include "../../rcore/rguiToggle.h"
#include "../../rcore/rRectangle.h"

#include "../gui/guiTinyDialog.h"
#include "../gui/TextEditor.h"

#include "globalLayoutCs163.h"

namespace Screen {
    class ScreenGraph: public ScreenView {
    private:
        enum OperationType {OTNULL, CREATE, CONNECT_C, FIND_MST, DIJKSTRA, PHYSICS} currOperationType;
        enum Operation {ONULL, CREATE_RANDOM, CREATE_USER_DEF, CREATE_FILE} currOperation;

        GraphicGraph obj;

        GuiTextBoxState inputCreateRandomNode, inputCreateRandomEdge;
        GuiTextBoxState inputDijkstraSource;

        GuiToggleState toggleCreateType;
        GuiToggleState toggleCreateRandom;

        GuiToggleState toggleDijkstraType;
        GuiToggleState toggleUserDefine;

        GuiToggleState togglePhysics;

        StyledText exitMessage;

        ListOfOperationsGroups ALOG;
        
        TextEditor textEditor;
        
    public:
        ScreenGraph();
        ~ScreenGraph() override;

        void load() override;
        void init() override;
        void draw() override;
        void destroy() override;
    };
}

#endif
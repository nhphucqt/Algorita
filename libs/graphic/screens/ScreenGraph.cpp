#include "ScreenGraph.h"

Screen::ScreenGraph::ScreenGraph() {}
Screen::ScreenGraph::~ScreenGraph() {}

void Screen::ScreenGraph::load() { // Ensure that obj has to be destroy before (prevent MEMORY LEAKING)
    inputCreateRandomNode.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_DIGIT_INPUT, true, false);
    inputCreateRandomEdge.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_DIGIT_INPUT, true, false);

    inputDijkstraSource.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1    + Gui::LABEL_PADDING_LEFT + Gui::BUTTON_OPER_GO_WIDTH, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 1 + 5, Gui::BUTTON_OPER_WIDTH - Gui::BUTTON_OPER_GO_WIDTH * 3 - 20, Gui::INPUT_BOX_HEIGHT}, Graphic::MAX_DIGIT_INPUT, true, false);

    toggleCreateType.init(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Create", false);
    toggleCreateRandom.init(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Random", false);

    toggleDijkstraType.init(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 1, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Dijkstra", false);

    togglePhysics.init(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 5, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "Physics: ON", false);

    exitMessage = StyledText(std::string(), Gfont::defaultFont);
}

void Screen::ScreenGraph::init() {
    currOperationType = OTNULL;
    currOperation = ONULL;
    int nNode = GetRandomValue(1, Core::MAX_NUM_GRAPH_NODE);
    int nEdge = GetRandomValue(0, std::min(nNode*(nNode-1)/2, Core::MAX_NUM_GRAPH_EDGE));
    exitMessage.assign(obj.initialize(nNode, nEdge, &ALOG).message);
}

void Screen::ScreenGraph::draw() {
    if (textEditor.isEnabled) {
        GuiLock();
    }
    bool keyActive = true;

    togglePhysics.draw();
    if (togglePhysics.justToggle()) {
        if (togglePhysics.isActive()) {
            obj.isPhysicsLocked = true;
            togglePhysics.setText("Physics: OFF");
        } else {
            obj.isPhysicsLocked = false;
            togglePhysics.setText("Physics: ON");
        }
    }

    if (toggleCreateType.draw()) {
        if (toggleCreateType.justToggle()) {
            currOperationType = CREATE;
        } else if (currOperationType != CREATE) {
            toggleCreateType.deactive();
        }
        if (toggleCreateRandom.draw()) {
            if (toggleCreateRandom.justToggle()) {
                currOperation = CREATE_RANDOM;
            } else if (currOperation != CREATE_RANDOM) {
                toggleCreateRandom.deactive();
            }
            GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT * 2}, nullptr);
            GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "n =");
            keyActive &= !inputCreateRandomNode.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
                inputCreateRandomNode.setnum(GetRandomValue(1, Core::MAX_NUM_GRAPH_NODE));
            }
            GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "m =");
            keyActive &= !inputCreateRandomEdge.draw();
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2 + 5, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
                int nNode = inputCreateRandomNode.getNum();
                inputCreateRandomEdge.setnum(GetRandomValue(0, std::min(nNode * (nNode-1) / 2, Core::MAX_NUM_GRAPH_EDGE)));
            }
            if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3 + 5, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_GO_HEIGHT * 2 + 10}, "Go") || (keyActive && IsKeyPressed(KEY_ENTER))) {
                exitMessage.assign(obj.initialize(inputCreateRandomNode.getNum(), inputCreateRandomEdge.getNum(), &ALOG).message);
            }
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4, Gui::USER_DEF_BUTTON_WIDTH, Gui::USER_DEF_BUTTON_HEIGHT}, "Input")) {
            currOperation = CREATE_USER_DEF;
            textEditor.isEnabled = true;
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 2 + Gui::USER_DEF_BUTTON_WIDTH + Gui::BUTTON_OPER_DIST_X, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 4, Gui::FILE_DIALOG_OPEN_BUTTON_WIDTH, Gui::FILE_DIALOG_OPEN_BUTTON_HEIGHT}, "File")) {
            currOperation = CREATE_FILE;
            wchar_t const * filePath = TinyDial::guiOpenTextFile();
            if (filePath != nullptr) {
                std::wifstream fin(filePath);
                if (!fin.is_open()) {
                    std::wcerr << L"ERROR: Cannot open " << filePath << '\n';
                } else {
                    std::wstringstream ss;
                    ss << fin.rdbuf();
                    fin.close();
                    std::wstring_convert<std::codecvt_utf8<wchar_t>,wchar_t> cv;
                    std::string str = cv.to_bytes(ss.str());
                    exitMessage.assign(obj.initialize(str, &ALOG).message);
                }
            }
        }
    }
    // Search type Button
    if (GuiButton(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 3, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "CC")) {
        currOperationType = CONNECT_C;
        exitMessage.assign(obj.findConnectedComponents(&ALOG).message);
    }
    // Insert type Button
    if (GuiButton(Rectangle{0, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 2, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "MST")) {
        currOperationType = FIND_MST;
        exitMessage.assign(obj.findMinimumSpanningTree(&ALOG).message);
    }
    // Remove type Button
    if (toggleDijkstraType.draw()) {
        if (toggleDijkstraType.justToggle()) {
            currOperationType = DIJKSTRA;
        } else if (currOperationType != DIJKSTRA) {
            toggleDijkstraType.deactive();
        }
        GuiDummyRec(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 1, Gui::BUTTON_OPER_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "");
        GuiLabel(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::LABEL_PADDING_LEFT, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 1, Gui::BUTTON_OPER_GO_WIDTH, Gui::BUTTON_OPER_HEIGHT}, "v =");
        keyActive &= !inputDijkstraSource.draw();
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 2, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 1 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, Gicon::BUTTON_RANDOM)) {
            inputDijkstraSource.setnum(GetRandomValue(0, obj.numNode-1));
        }
        if (GuiButton(Rectangle{(Gui::BUTTON_OPER_WIDTH + Gui::BUTTON_OPER_DIST_X) * 1 + Gui::BUTTON_OPER_WIDTH - (Gui::BUTTON_OPER_GO_WIDTH + 5) * 1, Window::HEIGHT - Layout::BOTTOM_HEIGHT - Gui::BUTTON_OPER_HEIGHT * 1 + 5, Gui::BUTTON_OPER_GO_HEIGHT, Gui::BUTTON_OPER_GO_HEIGHT}, "Go") || (keyActive && IsKeyPressed(KEY_ENTER))) {
            exitMessage.assign(obj.dijkstra(inputDijkstraSource.getNum(), &ALOG).message);
        }
    }

    ALOG.run();
    obj.draw();
    ALOG.draw(keyActive && !GuiIsLocked());
    exitMessage.draw(20, (Window::HEIGHT - Layout::BOTTOM_HEIGHT + (Layout::BOTTOM_HEIGHT - exitMessage.dim.y) / 2), Theme::currTheme.EXIT_MESSAGE);
    LayoutCs163::drawTopNavigation(keyActive);

    if (textEditor.isEnabled) {
        GuiUnlock();
        // 640
        textEditor.draw({210, 640 - 500, 500, 500});
        if (GuiButton(Rectangle{210 + 500, 640 - 500, 50, 50}, "Hide")) {
            textEditor.isEnabled = false;
        }
        if (GuiButton(Rectangle{210 + 500, 640 - 500 + 50, 50, 50}, "Go")) {
            textEditor.isEnabled = false;
            exitMessage.assign(obj.initialize(textEditor.getContent(), &ALOG).message);
        }
    }
}

void Screen::ScreenGraph::destroy() {
    ALOG.destroy();
    obj.destroy();
}
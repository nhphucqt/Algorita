#ifndef GLOBAL_H
#define GLOBAL_H

#include <filesystem>
#include <io.h>
#include <fcntl.h>

#include <cmath>
#include <cstring>
#include <iostream>
#include <functional>

#include "conf_raylib.h"
#include "graphic/gui/Theme.h"
#include "graphic/screens/ScreenView.h"

namespace CPath {
    const char* const THEME_DATA = "assets/data/theme.data";

    const char* const SLL_SEARCH_FIRST = "assets/visual_cpp/sll/sll_search_first.cpp.txt";
    const char* const SLL_UPDATE = "assets/visual_cpp/sll/sll_update.cpp.txt";
    const char* const SLL_INSERT_FORD = "assets/visual_cpp/sll/sll_insert_ford.cpp.txt";
    const char* const SLL_INSERT_BACK = "assets/visual_cpp/sll/sll_insert_back.cpp.txt";
    const char* const SLL_INSERT_KTH = "assets/visual_cpp/sll/sll_insert_kth.cpp.txt";
    const char* const SLL_REMOVE_FORD = "assets/visual_cpp/sll/sll_remove_ford.cpp.txt";
    const char* const SLL_REMOVE_BACK = "assets/visual_cpp/sll/sll_remove_back.cpp.txt";
    const char* const SLL_REMOVE_KTH = "assets/visual_cpp/sll/sll_remove_kth.cpp.txt";

    const char* const DLL_SEARCH_FIRST = "assets/visual_cpp/dll/dll_search_first.cpp.txt";
    const char* const DLL_UPDATE = "assets/visual_cpp/dll/dll_update.cpp.txt";
    const char* const DLL_INSERT_FORD = "assets/visual_cpp/dll/dll_insert_ford.cpp.txt";
    const char* const DLL_INSERT_BACK = "assets/visual_cpp/dll/dll_insert_back.cpp.txt";
    const char* const DLL_INSERT_KTH = "assets/visual_cpp/dll/dll_insert_kth.cpp.txt";
    const char* const DLL_REMOVE_FORD = "assets/visual_cpp/dll/dll_remove_ford.cpp.txt";
    const char* const DLL_REMOVE_BACK = "assets/visual_cpp/dll/dll_remove_back.cpp.txt";
    const char* const DLL_REMOVE_KTH = "assets/visual_cpp/dll/dll_remove_kth.cpp.txt";

    const char* const CLL_SEARCH_FIRST = "assets/visual_cpp/cll/cll_search_first.cpp.txt";
    const char* const CLL_UPDATE = "assets/visual_cpp/cll/cll_update.cpp.txt";
    const char* const CLL_INSERT_FORD = "assets/visual_cpp/cll/cll_insert_ford.cpp.txt";
    const char* const CLL_INSERT_BACK = "assets/visual_cpp/cll/cll_insert_back.cpp.txt";
    const char* const CLL_INSERT_KTH = "assets/visual_cpp/cll/cll_insert_kth.cpp.txt";
    const char* const CLL_REMOVE_FORD = "assets/visual_cpp/cll/cll_remove_ford.cpp.txt";
    const char* const CLL_REMOVE_BACK = "assets/visual_cpp/cll/cll_remove_back.cpp.txt";
    const char* const CLL_REMOVE_KTH = "assets/visual_cpp/cll/cll_remove_kth.cpp.txt";

    const char* const STACK_UPDATE = "assets/visual_cpp/stack/stack_update.cpp.txt";
    const char* const STACK_PEEK = "assets/visual_cpp/stack/stack_peek.cpp.txt";
    const char* const STACK_CLEAR = "assets/visual_cpp/stack/stack_clear.cpp.txt";

    const char* const QUEUE_PEEK = "assets/visual_cpp/queue/queue_peek.cpp.txt";
    const char* const QUEUE_UPDATE = "assets/visual_cpp/queue/queue_update.cpp.txt";
    const char* const QUEUE_PUSH = "assets/visual_cpp/queue/queue_push.cpp.txt";
    const char* const QUEUE_POP = "assets/visual_cpp/queue/queue_pop.cpp.txt";
    const char* const QUEUE_CLEAR = "assets/visual_cpp/queue/queue_clear.cpp.txt";

    const char* const STAT_ARR_SEARCH_FIRST = "assets/visual_cpp/stat_arr/stat_arr_search_first.cpp.txt";
    const char* const STAT_ARR_UPDATE = "assets/visual_cpp/stat_arr/stat_arr_update.cpp.txt";
    const char* const STAT_ARR_ACCESS = "assets/visual_cpp/stat_arr/stat_arr_access.cpp.txt";
    const char* const STAT_ARR_INSERT_FORD = "assets/visual_cpp/stat_arr/stat_arr_insert_ford.cpp.txt";
    const char* const STAT_ARR_INSERT_BACK = "assets/visual_cpp/stat_arr/stat_arr_insert_back.cpp.txt";
    const char* const STAT_ARR_INSERT_KTH = "assets/visual_cpp/stat_arr/stat_arr_insert_kth.cpp.txt";
    const char* const STAT_ARR_REMOVE_FORD = "assets/visual_cpp/stat_arr/stat_arr_remove_ford.cpp.txt";
    const char* const STAT_ARR_REMOVE_BACK = "assets/visual_cpp/stat_arr/stat_arr_remove_back.cpp.txt";
    const char* const STAT_ARR_REMOVE_KTH = "assets/visual_cpp/stat_arr/stat_arr_remove_kth.cpp.txt";

    const char* const DYNA_ARR_SEARCH_FIRST = "assets/visual_cpp/dyna_arr/dyna_arr_search_first.cpp.txt";
    const char* const DYNA_ARR_UPDATE = "assets/visual_cpp/dyna_arr/dyna_arr_update.cpp.txt";
    const char* const DYNA_ARR_ACCESS = "assets/visual_cpp/dyna_arr/dyna_arr_access.cpp.txt";
    const char* const DYNA_ARR_INSERT_FORD = "assets/visual_cpp/dyna_arr/dyna_arr_insert_ford.cpp.txt";
    const char* const DYNA_ARR_INSERT_BACK = "assets/visual_cpp/dyna_arr/dyna_arr_insert_back.cpp.txt";
    const char* const DYNA_ARR_INSERT_KTH = "assets/visual_cpp/dyna_arr/dyna_arr_insert_kth.cpp.txt";
    const char* const DYNA_ARR_REMOVE_FORD = "assets/visual_cpp/dyna_arr/dyna_arr_remove_ford.cpp.txt";
    const char* const DYNA_ARR_REMOVE_BACK = "assets/visual_cpp/dyna_arr/dyna_arr_remove_back.cpp.txt";
    const char* const DYNA_ARR_REMOVE_KTH = "assets/visual_cpp/dyna_arr/dyna_arr_remove_kth.cpp.txt";

    const char* const HASHTABLE_SEARCH = "assets/visual_cpp/ht/hashtable_search.cpp.txt";
    const char* const HASHTABLE_PUSH = "assets/visual_cpp/ht/hashtable_push.cpp.txt";
    const char* const HASHTABLE_POP = "assets/visual_cpp/ht/hashtable_pop.cpp.txt";
}
namespace App {
    const char* const title = "Algorita";
    const char* const description = "Project Lab CS162 - A data structures visualizer based on VisuAlgo";
    const char* const author = "by Nguyen Hoang Phuc - 22125077";
}

namespace Geo {
    const double EPS = 1e-3;
    const double PI = acos(-1);
    const double RAD30 = PI / 6; // PI / 6
    const double RAD45 = PI / 4; // PI / 4
    const double RAD60 = PI / 3; // PI / 3
    const double RAD90 = PI / 2; // PI / 2
}

namespace Core {
    const int NUM_DATA_STRUCTURE = 7;

    const int NODE_MIN_VALUE = 0;
    const int NODE_MAX_VALUE = 99;

    const int MAX_NUM_NODE_SLL = 10;

    const int MAX_NUM_ARRAY_ELM = 16;

    const int MAX_NUM_HT_HOR_ELM = 20;
    const int MAX_NUM_HT_VER_ELM = 8;
    const int MAX_NUM_HT_ELM = MAX_NUM_HT_HOR_ELM * MAX_NUM_HT_VER_ELM;

    const int MAX_NUM_AVL_ELM = 32;
}

namespace Window {
    // WXGA+ | 16 : 10
    // const int WIDTH = 1440;
    const int WIDTH = 1600;
    const int HEIGHT = 900;
    const Vector2 DIMENSION = Vector2{WIDTH, HEIGHT};
    
    // const int FPS = 360;
    const int FPS = 120;
    // const int FPS = 10;
}

namespace Graphic {
    // GUI
    const int MAX_SIZE_INPUT = 50; // Including '\0' character
    const int MAX_DIGIT_INPUT = 4; // Including '\0' character

    // NODE GRAPHIC
    const float NODE_SIZE = 50;
    const float NODE_BORDER_WIDTH = 4;
    const float NODE_DIST = NODE_SIZE + NODE_SIZE;

    const float NODE_SIZE_SMALL = 35;
    const float NODE_BORDER_WIDTH_SMALL = 3;

    const float NODE_SUBTEXT_PADDING = 0;
    const float NODE_SUBTEXT_MARGIN_TOP = 2;

    // ARROW GRAPHIC
    const float ARROW_LINE_WIDTH = 4;
    const float ARROW_HEAD_LENGTH = 10;
    const float ARROW_HEAD_WIDTH = 10;

    const float ARROW_LINE_WIDTH_SMALL = 3;
    const float ARROW_HEAD_LENGTH_SMALL = 8;
    const float ARROW_HEAD_WIDTH_SMALL = 8;

    const int ARROW_NUM_JOIN = 6;
    const float ARROW_VERT_LENGTH = 70;
    const float ARROW_SIDE_LENGTH = 70;

    // SINGLY LINKED LIST GRAPHIC
    const int LL_ORG_X = 200;
    const int LL_ORG_Y = 225;
    const int LL_NODE_DIST = (int)NODE_DIST;

    // ARRAY
    const int ARR_ORG_X = 150;
    const int ARR_ORG_Y = 200;
    const int ARR_EML_HOR_DIST = NODE_SIZE / 2;
    const int ARR_EML_VER_DIST = NODE_SIZE * 2;

    // HASH TABLE
    const int HT_ORG_Y = 100;
    const int HT_EML_HOR_DIST = NODE_SIZE_SMALL + NODE_SIZE_SMALL / 2;
    const int HT_EML_VER_DIST = NODE_SIZE_SMALL + NODE_SIZE_SMALL / 2;

    // BINARY SEARCH TREE
    const int BST_ORG_X = 700;
    const int BST_ORG_Y = 100;
    const int BST_VERTICAL_MARGIN = 30;
    const int BST_HORIZONTAL_MARGIN = 15; 
}

namespace Layout {
    const int BOTTOM_HEIGHT = 60;
}

namespace Screen {
    inline enum ScreenType {
        SINGLY_LINKED_LIST,
        DOUBLY_LINKED_LIST,
        CIRCULAR_LINKED_LIST,
        STACK,
        QUEUE,
        STATIC_ARRAY,
        DYNAMIC_ARRAY,
        MAIN_MENU,
        HASH_TABLE,
        AVL_TREE,
        MAIN_MENU_CS163,
        NUM_SCREEN
    } currScreen;
    
    inline ScreenView* screenViews[NUM_SCREEN];

    inline void init() {
        screenViews[currScreen]->init();
    }

    inline void load() {
        for (int i = 0; i < NUM_SCREEN; ++i) {
            screenViews[i]->load();
        }
    }

    inline void draw() {
        screenViews[currScreen]->draw();
    }

    inline void destroy() {
        screenViews[currScreen]->destroy();
    }

    inline void setScreen(ScreenType screenType) {
        destroy();
        currScreen = screenType;
        init();
    }

    inline void updateScreen(ScreenType screenType) {
        if (currScreen != screenType) {
            setScreen(screenType);
        }
    }

    inline void unload() {
        for (int i = 0; i < NUM_SCREEN; ++i) {
            screenViews[i]->destroy();
            delete screenViews[i];
        }
    }

}
namespace Gui {
    const int CODEBLOCK_LINE_PADDING_X = 10;
    const int CODEBLOCK_LINE_PADDING_Y = 8;
    const int CODEBLOCK_BLOCK_PADDING_X = 0;
    const int CODEBLOCK_BLOCK_PADDING_Y = 0;
    const int CODEBLOCK_SPACING = 1;

    const int LABEL_PADDING_LEFT = 5;

    const int BUTTON_OPER_WIDTH = 200;
    const int BUTTON_OPER_HEIGHT = 50;
    const int BUTTON_OPER_DIST_X = 10;

    const int INPUT_BOX_WIDTH = 110;
    const int INPUT_BOX_HEIGHT = 40;

    const int BUTTON_OPER_GO_WIDTH = 40;
    const int BUTTON_OPER_GO_HEIGHT = 40;

    const int USER_DEF_BUTTON_WIDTH = 300;
    const int USER_DEF_BUTTON_HEIGHT = 50;
    const int USER_DEF_INPUT_HEIGHT = 40;

    const int LOG_SPEED_SIGN_WIDTH = 70;
    const int LOG_SPEED_SIGN_HEIGHT = 60;
    const int LOG_SLIDER_WIDTH = 200;
    const int LOG_SLIDER_HEIGHT = 20;
    const int LOG_SLIDER_BAR_WIDTH = 400;
    const int LOG_SLIDER_BAR_HEIGHT = 20;
    const int LOG_NAV_BUTTON_WIDTH = 35;
    const int LOG_NAV_BUTTON_HEIGHT = 35;

    const int FILE_DIALOG_OPEN_BUTTON_WIDTH = 50;
    const int FILE_DIALOG_OPEN_BUTTON_HEIGHT = 50;
    const int FILE_DIALOG_WIDTH = 1000;
    const int FILE_DIALOG_HEIGHT = 800;
}

namespace Gicon {
    const int MAX_ID_LEN = 6; // include '\0'
    inline char BUTTON_PLAY[MAX_ID_LEN];
    inline char BUTTON_PAUSE[MAX_ID_LEN];
    inline char BUTTON_PREV[MAX_ID_LEN];
    inline char BUTTON_NEXT[MAX_ID_LEN];
    inline char BUTTON_FIRST[MAX_ID_LEN];
    inline char BUTTON_LAST[MAX_ID_LEN];
    inline char BUTTON_REPLAY[MAX_ID_LEN];
    inline char BUTTON_RANDOM[MAX_ID_LEN];
    inline char LIGHT_THEME[MAX_ID_LEN];
    inline char DARK_THEME[MAX_ID_LEN];

    inline void loadIcons() {
        strcpy(BUTTON_PLAY, GuiIconText(ICON_BIG_PLAYER_PLAY, nullptr));
        strcpy(BUTTON_PAUSE, GuiIconText(ICON_BIG_PLAYER_PAUSE, nullptr));
        strcpy(BUTTON_PREV, GuiIconText(ICON_BIG_PLAYER_PREV, nullptr));
        strcpy(BUTTON_NEXT, GuiIconText(ICON_BIG_PLAYER_NEXT, nullptr));
        strcpy(BUTTON_FIRST, GuiIconText(ICON_BIG_PLAYER_FIRST, nullptr));
        strcpy(BUTTON_LAST, GuiIconText(ICON_BIG_PLAYER_LAST, nullptr));
        strcpy(BUTTON_REPLAY, GuiIconText(ICON_BIG_PLAYER_REPLAY, nullptr));
        strcpy(BUTTON_RANDOM, GuiIconText(ICON_BIG_RANDOM, nullptr));
        strcpy(LIGHT_THEME, GuiIconText(ICON_LIGHT_THEME, nullptr));
        strcpy(DARK_THEME, GuiIconText(ICON_DARK_THEME, nullptr));
    }
}

namespace Animate {
    enum RunType {RUN_ALL, RUN_STEP};

    const float ANIMATE_TIME = 0.4;
    const float FADEIN_TIME = ANIMATE_TIME;
    const float FADEOUT_TIME = ANIMATE_TIME;
    const float TRANS_TIME = ANIMATE_TIME;
    const float TRAVEL_TIME = ANIMATE_TIME;
    const float SLIDE_TIME = ANIMATE_TIME;
    const float FOCUS_TIME = ANIMATE_TIME;
    const float UNFOCUS_TIME = ANIMATE_TIME;
    const float DELAY_TIME = ANIMATE_TIME;
    const float ASSIGN_TIME = ANIMATE_TIME;

    inline double elapseTime = 0;
}

namespace Gfont {
    const int FONT_TITLE_SIZE = 96;
    const int FONT_DEFAULT_SIZE = 30;
    const int FONT_DEFAULT_SIZE_SMALL = 22;
    const int FONT_CODE_SIZE = 20;
    inline Font* defaultFont;
    inline Font* defaultFontSmall;
    inline Font* titleFont;
    inline Font* codeFont;
    inline Font ptsans_bold_def;
    inline Font ptsans_bold_def_small;
    inline Font ptsans_bold_tit;
    inline Font consolas_code;

    inline void setDefaultFont(Font* font) {
        defaultFont = font;
    }

    inline void setDefaultFontSmall(Font* font) {
        defaultFontSmall = font;
    }

    inline void setCodeFont(Font* font) {
        codeFont = font;
    }

    inline void setTitleFont(Font* font) {
        titleFont = font;
    }

    inline void loadFont() {
        // Load fonts
        ptsans_bold_def = LoadFontEx("./assets/fonts/PTSans-Bold.ttf", FONT_DEFAULT_SIZE, 0, 250);
        ptsans_bold_def_small = LoadFontEx("./assets/fonts/PTSans-Bold.ttf", FONT_DEFAULT_SIZE_SMALL, 0, 250);
        ptsans_bold_tit = LoadFontEx("./assets/fonts/PTSans-Bold.ttf", FONT_TITLE_SIZE, 0, 250);
        consolas_code = LoadFontEx("./assets/fonts/Consolas-Bold.ttf", FONT_CODE_SIZE, 0, 250);

        // Set default font
        setDefaultFont(&ptsans_bold_def);
        setDefaultFontSmall(&ptsans_bold_def_small);
        setTitleFont(&ptsans_bold_tit);
        setCodeFont(&consolas_code);
    }

    inline void unloadFont() {
        UnloadFont(ptsans_bold_def);
        UnloadFont(ptsans_bold_def_small);
        UnloadFont(ptsans_bold_tit);
        UnloadFont(consolas_code);
        defaultFont = nullptr;
        titleFont = nullptr;
        codeFont = nullptr;
    }
}

#endif
#ifndef GLOBAL_H
#define GLOBAL_H

#include "conf_raylib.h"
#include <cmath>

namespace CPath {
    const char* const SLL_SEARCH_FIRST = "assets/visual_cpp/sll/sll_search_first";
    const char* const SLL_UPDATE = "assets/visual_cpp/sll/sll_update";
    const char* const SLL_INSERT_FORD = "assets/visual_cpp/sll/sll_insert_ford";
    const char* const SLL_INSERT_BACK = "assets/visual_cpp/sll/sll_insert_back";
    const char* const SLL_INSERT_KTH = "assets/visual_cpp/sll/sll_insert_kth";
    const char* const SLL_REMOVE_FORD = "assets/visual_cpp/sll/sll_remove_ford";
    const char* const SLL_REMOVE_BACK = "assets/visual_cpp/sll/sll_remove_back";
    const char* const SLL_REMOVE_KTH = "assets/visual_cpp/sll/sll_remove_kth";
}
namespace App {
    const char* const title = "Algorita";
    const char* const author = "Nguyen Hoang Phuc";
    const char* const description = "Project Lab CS162";
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
    const int NODE_MIN_VALUE = 0;
    const int NODE_MAX_VALUE = 99;

    const int MAX_NUM_NODE_SLL = 10;
}

namespace Window {
    // WXGA+ | 16 : 10
    // const int WIDTH = 1440;
    const int WIDTH = 1600;
    const int HEIGHT = 900;
    const Vector2 DIMENSION = Vector2{WIDTH, HEIGHT};
    
    // const int FPS = 360;
    const int FPS = 720;
    // const int FPS = 10;
}

namespace Graphic {
    // GUI
    const int MAX_SIZE_INPUT = 50; // Including '\0' character

    // NODE GRAPHIC
    const float NODE_SIZE = 50;
    const float NODE_BORDER_WIDTH = 4;
    const float NODE_DIST = NODE_SIZE + NODE_SIZE;

    const float NODE_SUBTEXT_PADDING = 0;
    const float NODE_SUBTEXT_MARGIN_TOP = 2;

    // ARROW GRAPHIC
    const float ARROW_LINE_WIDTH = 4;
    const float ARROW_HEAD_LENGTH = 10;
    const float ARROW_HEAD_WIDTH = 10;

    // SINGLY LINKED LIST GRAPHIC
    const int SLL_ORG_X = 200;
    const int SLL_ORG_Y = 300;
    const int SLL_NODE_DIST = (int)NODE_DIST;

    // STACK GRAPHIC
    const int STACK_ORG_X = (Window::WIDTH - NODE_SIZE) / 2;
    const int STACK_ORG_Y = 50;
    const int STACK_NODE_DIST = (int)NODE_DIST;
}

namespace Layout {
    const int BOTTOM_HEIGHT = 60;
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
    const int LOG_SPEED_SIGN_HEIGHT = 50;
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

#define rCol Color
namespace Gcolor {
    // NODE COLOR
    inline rCol NODE_BACKGROUND = WHITE;
    inline rCol NODE_BACKGROUND_FOCUS = GREEN;
    inline rCol NODE_BACKGROUND_FOCUS_REFER = BLUE;
    inline rCol NODE_BACKGROUND_FOCUS_ITER = ORANGE;
    inline rCol NODE_BACKGROUND_FOCUS_REMOVE = BROWN;

    inline rCol NODE_FOREGROUND = BLACK;
    inline rCol NODE_FOREGROUND_FOCUS = WHITE;
    inline rCol NODE_FOREGROUND_FOCUS_ITER = ORANGE;

    inline rCol NODE_BORDER = BLACK;
    inline rCol NODE_BORDER_FOCUS = GREEN;
    inline rCol NODE_BORDER_FOCUS_REFER = BLUE;
    inline rCol NODE_BORDER_FOCUS_ITER = ORANGE;
    inline rCol NODE_BORDER_FOCUS_REMOVE = BROWN;

    inline rCol NODE_SUBTEXT = RED;

    // ARROW COLOR
    inline rCol ARROW_LINE = BLACK;
    inline rCol ARROW_LINE_FOCUS = GREEN;
    inline rCol ARROW_LINE_FOCUS_ITER = ORANGE;

    inline rCol ARROW_HEAD = BLACK;

    // TEXT BUTTON COLOR
    inline rCol TEXT_BUTTON_BACKGROUND = DARKGRAY;
    inline rCol TEXT_BUTTON_BACKGROUND_FOCUS = GRAY;
    inline rCol TEXT_BUTTON_FOREGROUND = WHITE;
    inline rCol TEXT_BUTTON_FOREGROUND_FOCUS = WHITE;

    // CODEBLOCK COLOR
    inline rCol CODEBLOCK_BACKGROUND = Color{75, 101, 186, 255};
    inline rCol CODEBLOCK_BACKGROUND_FOCUS = BLACK;
    inline rCol CODEBLOCK_FOREGROUND = WHITE;
    inline rCol CODEBLOCK_FOREGROUND_FOCUS = WHITE;
}
#undef rCol

namespace Gfont {
    const int FONT_DEFAULT_SIZE = 30;
    // const int FONT_DEFAULT_SIZE = 20;
    const int FONT_CODE_SIZE = 16;
    inline Font* defaultFont;
    inline Font* codeFont;
    inline Font jb_mono_med_def;
    inline Font ptsans_bold_def;
    inline Font consolas_code;

    inline void setDefaultFont(Font* font) {
        defaultFont = font;
    }

    inline void setCodeFont(Font* font) {
        codeFont = font;
    }

    inline void loadFont() {
        // Load fonts
        jb_mono_med_def = LoadFontEx("./assets/fonts/JetBrainsMono-Medium.ttf", FONT_DEFAULT_SIZE, 0, 250);
        ptsans_bold_def = LoadFontEx("./assets/fonts/PTSans-Bold.ttf", FONT_DEFAULT_SIZE, 0, 250);
        consolas_code = LoadFontEx("./assets/fonts/Consolas-Bold.ttf", FONT_CODE_SIZE, 0, 250);

        // Set default font
        // setDefaultFont(&jb_mono_med_def);
        setDefaultFont(&ptsans_bold_def);
        setCodeFont(&consolas_code);
    }

    inline void unloadFont() {
        UnloadFont(jb_mono_med_def);
        UnloadFont(ptsans_bold_def);
        UnloadFont(consolas_code);
    }
}

#endif
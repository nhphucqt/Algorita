#ifndef GLOBAL_H
#define GLOBAL_H

#include "conf_raylib.h"
#include <cmath>

namespace Geo {
    const double PI = acos(-1);
    const double RAD30 = PI / 6; // PI / 6
    const double RAD45 = PI / 4; // PI / 4
    const double RAD60 = PI / 3; // PI / 3
    const double RAD90 = PI / 2; // PI / 2
}

namespace Core {
    const int NODE_MIN_VALUE = 0;
    const int NODE_MAX_VALUE = 99;
}

namespace Window {
    // WXGA+ | 16 : 10
    const int WIDTH = 1440;
    const int HEIGHT = 900;
    
    // const int FPS = 360;
    const int FPS = 720;
}

namespace Graphic {
    // NODE GRAPHIC
    const float NODE_BORDER_WIDTH = 4;

    // ARROW GRAPHIC
    const float ARROW_LINE_WIDTH = 4;
    const float ARROW_HEAD_LENGTH = 16;
    const float ARROW_HEAD_WIDTH = 16;
}

namespace Animate {
    const float FADEIN_TIME = 0.5;
    const float FADEOUT_TIME = 0.5;
    const float TRANS_TIME = 1.5;
}

#define rCol raylib::Color
namespace Color {
    // NODE COLOR
    const rCol NODE_BACKGROUND = raylib::WHITE;
    // const rCol NODE_BACKGROUND = raylib::BLUE;
    const rCol NODE_BACKGROUND_FOCUS = raylib::GREEN;
    const rCol NODE_FOREGROUND = raylib::BLACK;
    const rCol NODE_FOREGROUND_FOCUS = raylib::WHITE;
    const rCol NODE_BORDER = raylib::BLACK;
    const rCol NODE_BORDER_FOCUS = raylib::BLACK;

    // ARROW COLOR
    const rCol ARROW_LINE = raylib::BLACK;
    const rCol ARROW_LINE_FOCUS = raylib::ORANGE;
    const rCol ARROW_HEAD = raylib::RED;
    // const rCol ARROW_HEAD = raylib::BLACK;
    const rCol ARROW_HEAD_FOCUS = raylib::ORANGE;
}
#undef rCol

namespace Font {
    const int FONT_DEFAULT_SIZE = 32;
    inline raylib::Font* defaultFont;
    inline raylib::Font jb_mono_med_def;

    inline void setDefaultFont(raylib::Font* font) {
        defaultFont = font;
    }

    inline void loadFont() {
        // Load fonts
        jb_mono_med_def = raylib::LoadFontEx("./assets/fonts/JetBrainsMono-Medium.ttf", FONT_DEFAULT_SIZE, 0, 250);

        // Set default font
        setDefaultFont(&jb_mono_med_def);
    }

    inline void unloadFont() {
        raylib::UnloadFont(jb_mono_med_def);
    }
}

#endif
#ifndef GLOBAL_H
#define GLOBAL_H

namespace raylib {
    #include "raylib.h"
}

namespace Core {
    const int NODE_MIN_VALUE = 0;
    const int NODE_MAX_VALUE = 99;
}

namespace Window {
    // WXGA+ | 16 : 10
    const int WIDTH = 1440;
    const int HEIGHT = 900;
    
    const int FPS = 360;
}

namespace Graphic {
    const int NODE_BORDER_WIDTH = 4;
}

namespace Animate {
    const double FADEIN_TIME = 0.5;
    const double FADEOUT_TIME = 0.5;
    const double TRANS_TIME = 1.5;
}

namespace Color {
    const raylib::Color NODE_BACKGROUND = raylib::WHITE;
    // const raylib::Color NODE_BACKGROUND = raylib::BLUE;
    const raylib::Color NODE_BACKGROUND_FOCUS = raylib::GREEN;
    const raylib::Color NODE_FOREGROUND = raylib::BLACK;
    const raylib::Color NODE_FOREGROUND_FOCUS = raylib::WHITE;
    const raylib::Color NODE_BORDER = raylib::BLACK;
    const raylib::Color NODE_BORDER_FOCUS = raylib::BLACK;
}

namespace Font {
    const int defaultSize = 32;
    inline raylib::Font* defaultFont;
    inline raylib::Font jb_mono_med_def;

    inline void setDefaultFont(raylib::Font* font) {
        defaultFont = font;
    }

    inline void loadFont() {
        // Load fonts
        jb_mono_med_def = raylib::LoadFontEx("./assets/fonts/JetBrainsMono-Medium.ttf", defaultSize, 0, 250);

        // Set default font
        setDefaultFont(&jb_mono_med_def);
    }

    inline void unloadFont() {
        raylib::UnloadFont(jb_mono_med_def);
    }
}

#endif
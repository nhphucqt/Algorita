#ifndef GLOBAL_H
#define GLOBAL_H

namespace raylib {
    #include "raylib.h"
}

namespace Core {
    // WXGA+ | 16 : 10
    const int WINDOW_WIDTH = 1440;
    const int WINDOW_HEIGHT = 900;
    
    const int FPS = 360;
}

namespace Animate {
    const double FADEIN_TIME = 0.5;
    const double FADEOUT_TIME = 0.5;
    const double TRANS_TIME = 1.5;
}

namespace Color {
    // const raylib::Color NODE_BACKGROUND = raylib::WHITE;
    const raylib::Color NODE_BACKGROUND = raylib::BLUE;
    const raylib::Color NODE_BACKGROUND_FOCUS = raylib::GREEN;
    const raylib::Color NODE_FOREGROUND = raylib::BLACK;
    const raylib::Color NODE_FOREGROUND_FOCUS = raylib::WHITE;
    const raylib::Color NODE_BORDER = raylib::BLACK;
    const raylib::Color NODE_BORDER_FOCUS = raylib::BLACK;
}

namespace Graphic {
    const int NODE_BORDER_WIDTH = 4;
}

#endif
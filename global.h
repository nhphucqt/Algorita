#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <cmath>
#include <assert.h>
#include <queue>
#include <functional>

namespace raylib {
    #include "raylib.h"
}

namespace Animate {
    const double FADEIN_SPEED = 512;
    const double FADEOUT_SPEED = 512;
    const double TRANS_TIME = 3;
}

namespace Core {
    const int FPS = 360;
    // WXGA+ | 16 : 10
    const int WINDOW_WIDTH = 1440;
    const int WINDOW_HEIGHT = 900;
}

#endif
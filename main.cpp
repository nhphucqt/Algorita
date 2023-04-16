#include <iostream>
#include <cmath>
#include <assert.h>
#include <queue>
#include <functional>

#include "libs/conf_raylib.h"

#include "libs/global.h"

#include "libs/graphic/objects/GraphicNode.h"
#include "libs/graphic/objects/GraphicSinglyNode.h"
#include "libs/graphic/objects/GraphicDoublyNode.h"
#include "libs/graphic/objects/GraphicSinglyLinkedList.h"
#include "libs/graphic/gui/GraphicButton.h"
#include "libs/animation/animation.h"

#include "libs/graphic/screens/screen.h"

int main() {
    SetRandomSeed(time(nullptr));
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);

    InitWindow(Window::WIDTH, Window::HEIGHT, "demo");
    SetTargetFPS(Window::FPS);

    SetExitKey(0);

    // Load

    Gicon::loadIcons();
    Gfont::loadFont();

    Theme::loadTheme();
    Theme::setLightTheme();

    Screen::load();

    while (!WindowShouldClose()) {
        Animate::elapseTime = GetFrameTime(); // DO NOT DELETE
        BeginDrawing();
            ClearBackground(Theme::currTheme.BACKGROUND);
            Screen::draw();
        EndDrawing();
    }

    CloseWindow();

    // Unload
    Gfont::unloadFont();

    Screen::destroy();

    return 0;
}
#include "libs/conf_raylib.h"
#include "libs/global.h"
#include "libs/graphic/screens/screen.h"

Screen::ScreenClass screen;

int main() {
    SetRandomSeed(time(nullptr));
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);

    InitWindow(Window::WIDTH, Window::HEIGHT, App::title);
    SetTargetFPS(Window::FPS);

    SetExitKey(0);

    // Load
    Gicon::loadIcons();
    Gfont::loadFont();

    Theme::loadTheme();

    screen.load();

    _setmode(_fileno(stdout), _O_U16TEXT);
    
    while (!WindowShouldClose()) {
        Animate::elapseTime = GetFrameTime(); // DO NOT DELETE
        BeginDrawing();
            ClearBackground(Theme::currTheme.BACKGROUND);
            Screen::draw();
        EndDrawing();
    }

    Screen::destroy();
    Gfont::unloadFont();
    
    CloseWindow();

    // Unload

    return 0;
}
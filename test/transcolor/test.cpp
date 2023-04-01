#include "libs/conf_raylib.h"
#include "libs/global.h"
#include "libs/rcore/rColor.h"

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);

    InitWindow(Window::WIDTH, Window::HEIGHT, "demo");
    SetTargetFPS(Window::FPS);

    double currTime = 0.0;
    double transTime = 1.0;
    double transPercent = 0;

    Color source = BLUE;
    Color destination = GREEN;

    while (!WindowShouldClose()) {
        currTime += GetFrameTime();
        if (currTime >= transTime) {
            transPercent = 1.0;
            currTime = transTime;
        } else {
            transPercent = currTime / transTime;
        }

        BeginDrawing();
            ClearBackground(TRANSCOLOR(source, destination, transPercent));
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
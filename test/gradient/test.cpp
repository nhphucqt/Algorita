#include "libs/conf_raylib.h"
#include "libs/global.h"
#include "libs/rcore/rColor.h"

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);

    InitWindow(Window::WIDTH, Window::HEIGHT, "demo");
    SetTargetFPS(Window::FPS);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(WHITE);
            DrawRectangleGradientH(100, 100, 500, 500, WHITE, BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
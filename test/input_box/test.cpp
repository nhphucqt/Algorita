#include "libs/conf_raylib.h"
#include "libs/global.h"
#include "libs/rcore/rColor.h"

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);

    InitWindow(Window::WIDTH, Window::HEIGHT, "demo");
    SetTargetFPS(Window::FPS);

    GuiLoadStyle("assets/styles/custom_style.rgs");

    char textArea[10];
    int secret;

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(WHITE);
            // GuiTextInputBox(Rectangle{100, 100, 200, 200}, "", "", "", textArea, 10, nullptr);
            GuiTextBox(Rectangle{100, 100, 100, 28}, textArea, 10, true);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
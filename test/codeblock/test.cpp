#include "libs/conf_raylib.h"
#include "libs/global.h"
#include "libs/rcore/rColor.h"
#include "libs/graphic/gui/Codeblock.h"

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);

    InitWindow(Window::WIDTH, Window::HEIGHT, "demo");
    SetTargetFPS(Window::FPS);

    Gfont::loadFont();

    Codeblock code;
    code.load("assets/visual_cpp/sll_search_first");

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(WHITE);
            code.draw(0, 0);
            code.setHighlight({0,1,2,3,4,5,6,7,8});
            code.draw(code.getBlockDimension().x + 8, 0);
            code.setHighlight({0,2,4,6,8});
            code.draw((code.getBlockDimension().x + 8) * 2, 0);
            code.setHighlight({1,3,5,7});
            code.draw((code.getBlockDimension().x + 8) * 0, (code.getBlockDimension().y + 8) * 1);
        EndDrawing();
    }

    CloseWindow();

    Gfont::unloadFont();

    return 0;
}
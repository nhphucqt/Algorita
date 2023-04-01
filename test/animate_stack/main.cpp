#include <iostream>
#include <cmath>
#include <assert.h>
#include <queue>
#include <functional>

#include "libs/conf_raylib.h"

#include "libs/global.h"

#include "libs/graphic/GraphicNode.h"
#include "libs/graphic/GraphicSinglyNode.h"
#include "libs/graphic/GraphicDoublyNode.h"
#include "libs/graphic/GraphicStack.h"

#include "libs/graphic/animation.h"

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);

    InitWindow(Window::WIDTH, Window::HEIGHT, "demo");
    SetTargetFPS(Window::FPS);

    // Load
    Font::loadFont();

    GraphicStack st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);
    st.push(6);
    st.push(7);
    st.push(8);
    st.push(9);
    st.push(10);

    while (st.pop());

    while (!WindowShouldClose()) {
        Animate::elapseTime = GetFrameTime();
        // std::cerr << "Elapse time: " << Animate::elapseTime << '\n';
        Animate::queueOfScenes.run();
        BeginDrawing();
            ClearBackground(WHITE);
            st.draw();
        EndDrawing();
    }

    CloseWindow();


    // Unload
    Font::unloadFont();

    st.destroy();

    return 0;
}
#include <iostream>
#include <cmath>
#include <assert.h>
#include <queue>
#include <functional>

#include "libs/conf_raylib.h"

#include "libs/global.h"

#include "libs/graphic/GraphicNode.h"
#include "libs/core/SinglyNode.h"
#include "libs/core/DoublyNode.h"
#include "libs/core/VStack.h"

#include "libs/graphic/animation.h"

int main() {
    raylib::SetConfigFlags(raylib::FLAG_MSAA_4X_HINT);
    raylib::SetConfigFlags(raylib::FLAG_WINDOW_ALWAYS_RUN);

    raylib::InitWindow(Window::WIDTH, Window::HEIGHT, "demo");
    raylib::SetTargetFPS(Window::FPS);

    // Load
    Font::loadFont();

    VStack st;
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

    while (!raylib::WindowShouldClose()) {
        Animate::elapseTime = raylib::GetFrameTime();
        std::cerr << "Elapse time: " << Animate::elapseTime << '\n';
        Animate::queueOfScenes.run();
        raylib::BeginDrawing();
            raylib::ClearBackground(raylib::WHITE);
            st.draw();
        raylib::EndDrawing();
    }

    raylib::CloseWindow();


    // Unload
    Font::unloadFont();

    st.destroy();

    return 0;
}
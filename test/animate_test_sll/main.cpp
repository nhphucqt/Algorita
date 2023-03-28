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
#include "libs/graphic/objects/GraphicStack.h"
#include "libs/graphic/objects/GraphicSinglyLinkedList.h"

#include "libs/graphic/animation.h"

int main() {
    raylib::SetConfigFlags(raylib::FLAG_MSAA_4X_HINT);
    raylib::SetConfigFlags(raylib::FLAG_WINDOW_ALWAYS_RUN);

    raylib::InitWindow(Window::WIDTH, Window::HEIGHT, "demo");
    raylib::SetTargetFPS(Window::FPS);

    // Load
    Font::loadFont();

    GraphicSinglyLinkedList li;

    li.pushFront(1);
    li.pushFront(2);
    li.pushFront(3);
    li.pushFront(4);
    li.pushFront(5);
    li.pushBack(6);
    // li.pushBack(7);
    // li.pushBack(8);
    // li.pushBack(9);
    li.pushFront(10);
    li.pushAtKth(3, 11);
    li.popFront();
    li.popFront();
    li.popBack();
    li.popBack();
    li.popAtKth(1);

    // while (st.pop());

    while (!raylib::WindowShouldClose()) {
        Animate::elapseTime = raylib::GetFrameTime();
        // std::cerr << "Elapse time: " << Animate::elapseTime << '\n';
        Animate::queueOfScenes.run();
        raylib::BeginDrawing();
            raylib::ClearBackground(raylib::WHITE);
            li.draw();
        raylib::EndDrawing();
    }

    raylib::CloseWindow();


    // Unload
    Font::unloadFont();

    li.destroy();

    return 0;
}
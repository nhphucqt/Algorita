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
#include "libs/graphic/gui/GraphicButton.h"

#include "libs/animation/animation.h"

int main() {
    SetRandomSeed(time(nullptr));
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);

    InitWindow(Window::WIDTH, Window::HEIGHT, "demo");
    SetTargetFPS(Window::FPS);

    // Load
    Gfont::loadFont();

    int randval = 0;

    GraphicSinglyLinkedList li;

    std::list<GraphicTextButton*> observers;

    GraphicTextButton pushFrontButton(274, 732, 156, 57, "push front");
    GraphicTextButton pushBackButton(522, 732, 156, 57, "push back");
    GraphicTextButton popFrontButton(770, 732, 156, 57, "pop front");
    GraphicTextButton popBackButton(1018, 732, 156, 57, "pop back");

    observers.push_back(&pushFrontButton);
    observers.push_back(&pushBackButton);
    observers.push_back(&popFrontButton);
    observers.push_back(&popBackButton);

    while (!WindowShouldClose()) {
        if (pushFrontButton.isReleased(MOUSE_BUTTON_LEFT)) {
            li.pushFront(cf::getRandomNode());
        }
        if (pushBackButton.isReleased(MOUSE_BUTTON_LEFT)) {
            li.pushBack(cf::getRandomNode());
        }
        if (popFrontButton.isReleased(MOUSE_BUTTON_LEFT)) {
            li.popFront();
        }
        if (popBackButton.isReleased(MOUSE_BUTTON_LEFT)) {
            li.popBack();
        }
        Animate::elapseTime = GetFrameTime();
        Animate::queueOfScenes.run();
        BeginDrawing();
            ClearBackground(WHITE);
            for (auto obj : observers) {
                obj->draw();
            }
            li.draw();
        EndDrawing();
    }

    CloseWindow();


    // Unload
    Gfont::unloadFont();

    li.destroy();

    return 0;
}
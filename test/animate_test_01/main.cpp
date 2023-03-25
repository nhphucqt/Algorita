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

#include "libs/graphic/animation.h"

int main() {
    raylib::SetConfigFlags(raylib::FLAG_MSAA_4X_HINT);
    raylib::SetConfigFlags(raylib::FLAG_WINDOW_ALWAYS_RUN);

    raylib::InitWindow(Window::WIDTH, Window::HEIGHT, "demo");
    raylib::SetTargetFPS(Window::FPS);

    // Load
    Font::loadFont();

    DoublyNode* node = new DoublyNode(200, 200, Graphic::NODE_SIZE, false, 12);
    DoublyNode* node_2 = new DoublyNode(50, 200, Graphic::NODE_SIZE, false, 5);
    node->setNext(node_2);

    Animate::queueOfScenes.addBlankScene();
    Animate::queueOfScenes.pushFadeInToBackScene(node, Animate::FADEIN_TIME);
    Animate::queueOfScenes.pushFadeInToBackScene(node_2, Animate::FADEIN_TIME);

    node->aNext.vanish();
    node_2->aPrev.vanish();
    Animate::queueOfScenes.addBlankScene();
    Animate::queueOfScenes.pushFadeInToBackScene(&node->aNext);
    Animate::queueOfScenes.pushFadeInToBackScene(&node_2->aPrev);

    Animate::queueOfScenes.addBlankScene();
    Animate::queueOfScenes.pushTransformToBackScene(node, 500, 500);
    Animate::queueOfScenes.pushTransformToBackScene(node_2, 500, 500+Graphic::NODE_SIZE);

    Animate::queueOfScenes.pushFadeOutToNewScene(node);

    Animate::queueOfScenes.pushFadeInToNewScene(node);

    Animate::queueOfScenes.addBlankScene();
    Animate::queueOfScenes.pushTransformToBackScene(node, 300, 500);
    Animate::queueOfScenes.pushTransformToBackScene(node_2, 900, 700);

    Animate::queueOfScenes.addBlankScene();
    Animate::queueOfScenes.pushTransformToBackScene(node, 1200, 300);
    Animate::queueOfScenes.pushTransformToBackScene(node_2, 1000, 450);
    
    Animate::queueOfScenes.pushTransformToNewScene(node, 340, 321);

    Animate::queueOfScenes.addBlankScene();
    Animate::queueOfScenes.pushTransformToBackScene(node, 0, 0);
    Animate::queueOfScenes.pushTransformToBackScene(node_2, Window::WIDTH-Graphic::NODE_SIZE, Window::HEIGHT-Graphic::NODE_SIZE);

    Animate::queueOfScenes.addBlankScene();
    Animate::queueOfScenes.pushTransformToBackScene(node, 450, 450);
    Animate::queueOfScenes.pushTransformToBackScene(node_2, 0, 0);

    Animate::queueOfScenes.addBlankScene();
    Animate::queueOfScenes.pushTransformToBackScene(node, 600, 200);
    Animate::queueOfScenes.pushTransformToBackScene(node_2, 600, 200);
    
    Animate::queueOfScenes.addBlankScene();
    Animate::queueOfScenes.pushTransformToBackScene(node, 200, 200);
    Animate::queueOfScenes.pushTransformToBackScene(node_2, 1000, 600);

    Animate::queueOfScenes.addBlankScene();
    Animate::queueOfScenes.pushFadeOutToBackScene(node);
    Animate::queueOfScenes.pushFadeOutToBackScene(node_2);
    Animate::queueOfScenes.pushFadeOutToBackScene(&node->aNext);
    Animate::queueOfScenes.pushFadeOutToBackScene(&node_2->aPrev);

    while (!raylib::WindowShouldClose()) {
        Animate::elapseTime = raylib::GetFrameTime();
        std::cerr << "Elapse time: " << Animate::elapseTime << '\n';
        Animate::queueOfScenes.run();
        raylib::BeginDrawing();
            raylib::ClearBackground(raylib::WHITE);
            node->draw();
            node_2->draw();
        raylib::EndDrawing();
    }

    raylib::CloseWindow();


    // Unload
    Font::unloadFont();

    delete node;
    delete node_2;

    return 0;
}
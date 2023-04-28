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

#include "libs/animation/animation.h"

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);

    InitWindow(Window::WIDTH, Window::HEIGHT, "demo");
    SetTargetFPS(Window::FPS);

    // Load
    Font::loadFont();

    GraphicDoublyNode* node = new GraphicDoublyNode(200, 200, Graphic::NODE_SIZE, false, 12);
    GraphicDoublyNode* node_2 = new GraphicDoublyNode(50, 200, Graphic::NODE_SIZE, false, 5);
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
    Animate::queueOfScenes.pushDisplaceToBackScene(node, 500, 500);
    Animate::queueOfScenes.pushDisplaceToBackScene(node_2, 500, 500+Graphic::NODE_SIZE);

    Animate::queueOfScenes.pushFadeOutToNewScene(node);

    Animate::queueOfScenes.pushFadeInToNewScene(node);

    Animate::queueOfScenes.addBlankScene();
    Animate::queueOfScenes.pushDisplaceToBackScene(node, 300, 500);
    Animate::queueOfScenes.pushDisplaceToBackScene(node_2, 900, 700);

    Animate::queueOfScenes.addBlankScene();
    Animate::queueOfScenes.pushDisplaceToBackScene(node, 1200, 300);
    Animate::queueOfScenes.pushDisplaceToBackScene(node_2, 1000, 450);
    
    Animate::queueOfScenes.pushDisplaceToNewScene(node, 340, 321);

    Animate::queueOfScenes.addBlankScene();
    Animate::queueOfScenes.pushDisplaceToBackScene(node, 0, 0);
    Animate::queueOfScenes.pushDisplaceToBackScene(node_2, Window::WIDTH-Graphic::NODE_SIZE, Window::HEIGHT-Graphic::NODE_SIZE);

    Animate::queueOfScenes.addBlankScene();
    Animate::queueOfScenes.pushDisplaceToBackScene(node, 450, 450);
    Animate::queueOfScenes.pushDisplaceToBackScene(node_2, 0, 0);

    Animate::queueOfScenes.addBlankScene();
    Animate::queueOfScenes.pushDisplaceToBackScene(node, 600, 200);
    Animate::queueOfScenes.pushDisplaceToBackScene(node_2, 600, 200);
    
    Animate::queueOfScenes.addBlankScene();
    Animate::queueOfScenes.pushDisplaceToBackScene(node, 200, 200);
    Animate::queueOfScenes.pushDisplaceToBackScene(node_2, 1000, 600);

    Animate::queueOfScenes.addBlankScene();
    Animate::queueOfScenes.pushFadeOutToBackScene(node);
    Animate::queueOfScenes.pushFadeOutToBackScene(node_2);
    Animate::queueOfScenes.pushFadeOutToBackScene(&node->aNext);
    Animate::queueOfScenes.pushFadeOutToBackScene(&node_2->aPrev);

    while (!WindowShouldClose()) {
        Animate::elapseTime = GetFrameTime();
        Animate::queueOfScenes.run();
        BeginDrawing();
            ClearBackground(WHITE);
            node->draw();
            node_2->draw();
        EndDrawing();
    }

    CloseWindow();


    // Unload
    Font::unloadFont();

    delete node;
    delete node_2;

    return 0;
}
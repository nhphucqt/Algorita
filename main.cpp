#include <iostream>
#include <cmath>
#include <assert.h>
#include <queue>
#include <functional>

#include "libs/conf_raylib.h"

#include "libs/global.h"

#include "libs/graphic/GraphicNode.h"
#include "libs/core/SinglyNode.h"

#include "libs/graphic/animation.h"

int main() {
    raylib::SetConfigFlags(raylib::FLAG_MSAA_4X_HINT);
    raylib::SetConfigFlags(raylib::FLAG_WINDOW_ALWAYS_RUN);

    raylib::InitWindow(Window::WIDTH, Window::HEIGHT, "demo");
    raylib::SetTargetFPS(Window::FPS);

    // Load
    Font::loadFont();

    const int NODE_SIZE = 50;
    SinglyNode* node = new SinglyNode(200, 200, NODE_SIZE, true, 12);
    SinglyNode* node_2 = new SinglyNode(200-NODE_SIZE, 200, NODE_SIZE, false, 5);
    node->setNext(node_2);

    std::queue<std::vector<std::function<bool()>>> queueOfScenes;

    double* elapseTime = new double(0);
    double* currTime = new double(0);

    queueOfScenes.push({
        std::bind(&nodeFadeIn<GraphicNode>, node, elapseTime, currTime, Animate::FADEIN_TIME),
        std::bind(&nodeFadeIn<GraphicNode>, node_2, elapseTime, currTime, Animate::FADEIN_TIME)
    });

    queueOfScenes.push({
        std::bind(&nodeTransform<GraphicNode>, node, 500, 500, elapseTime, currTime, Animate::TRANS_TIME),
        std::bind(&nodeTransform<GraphicNode>, node_2, 500, 500+NODE_SIZE, elapseTime, currTime, Animate::TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeFadeOut<GraphicNode>, node, elapseTime, currTime, Animate::FADEOUT_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeFadeIn<GraphicNode>, node, elapseTime, currTime, Animate::FADEIN_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform<GraphicNode>, node, 300, 500, elapseTime, currTime, Animate::TRANS_TIME),
        std::bind(&nodeTransform<GraphicNode>, node_2, 900, 700, elapseTime, currTime, Animate::TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform<GraphicNode>, node, 1200, 300, elapseTime, currTime, Animate::TRANS_TIME),
        std::bind(&nodeTransform<GraphicNode>, node_2, 1000, 450, elapseTime, currTime, Animate::TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform<GraphicNode>, node, 340, 321, elapseTime, currTime, Animate::TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform<GraphicNode>, node, 0, 0, elapseTime, currTime, Animate::TRANS_TIME),
        std::bind(&nodeTransform<GraphicNode>, node_2, Window::WIDTH-NODE_SIZE, Window::HEIGHT-NODE_SIZE, elapseTime, currTime, Animate::TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform<GraphicNode>, node, 450, 450, elapseTime, currTime, Animate::TRANS_TIME),
        std::bind(&nodeTransform<GraphicNode>, node_2, 0, 0, elapseTime, currTime, Animate::TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform<GraphicNode>, node, 600, 200, elapseTime, currTime, Animate::TRANS_TIME),
        std::bind(&nodeTransform<GraphicNode>, node_2, 600, 200, elapseTime, currTime, Animate::TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform<GraphicNode>, node, 200, 200, elapseTime, currTime, Animate::TRANS_TIME),
        std::bind(&nodeTransform<GraphicNode>, node_2, 1000, 600, elapseTime, currTime, Animate::TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform<GraphicNode>, node, 500, 500, elapseTime, currTime, Animate::TRANS_TIME),
        std::bind(&nodeTransform<GraphicNode>, node_2, 500, 500+NODE_SIZE, elapseTime, currTime, Animate::TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeFadeOut<GraphicNode>, node, elapseTime, currTime, Animate::FADEOUT_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeFadeIn<GraphicNode>, node, elapseTime, currTime, Animate::FADEIN_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform<GraphicNode>, node, 300, 500, elapseTime, currTime, Animate::TRANS_TIME),
        std::bind(&nodeTransform<GraphicNode>, node_2, 900, 700, elapseTime, currTime, Animate::TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform<GraphicNode>, node, 1200, 300, elapseTime, currTime, Animate::TRANS_TIME),
        std::bind(&nodeTransform<GraphicNode>, node_2, 1000, 450, elapseTime, currTime, Animate::TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform<GraphicNode>, node, 340, 321, elapseTime, currTime, Animate::TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform<GraphicNode>, node, 0, 0, elapseTime, currTime, Animate::TRANS_TIME),
        std::bind(&nodeTransform<GraphicNode>, node_2, Window::WIDTH-NODE_SIZE, Window::HEIGHT-NODE_SIZE, elapseTime, currTime, Animate::TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform<GraphicNode>, node, 450, 450, elapseTime, currTime, Animate::TRANS_TIME),
        std::bind(&nodeTransform<GraphicNode>, node_2, 0, 0, elapseTime, currTime, Animate::TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform<GraphicNode>, node, 600, 200, elapseTime, currTime, Animate::TRANS_TIME),
        std::bind(&nodeTransform<GraphicNode>, node_2, 600, 200, elapseTime, currTime, Animate::TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform<GraphicNode>, node, 200, 200, elapseTime, currTime, Animate::TRANS_TIME),
        std::bind(&nodeTransform<GraphicNode>, node_2, 1000, 600, elapseTime, currTime, Animate::TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeFadeOut<GraphicNode>, node, elapseTime, currTime, Animate::FADEOUT_TIME),
        std::bind(&nodeFadeOut<GraphicNode>, node_2, elapseTime, currTime, Animate::FADEOUT_TIME)
    });

    while (!raylib::WindowShouldClose()) {
        *elapseTime = raylib::GetFrameTime();
        std::cerr << "Elapse time: " << *elapseTime << '\n';
        runScenes(queueOfScenes, currTime, elapseTime);
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
    delete elapseTime;
    delete currTime;

    return 0;
}
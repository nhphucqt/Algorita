#include <iostream>
#include <cmath>
#include <assert.h>
#include <queue>
#include <functional>

#include "libs/global.h"
#include "libs/rcore/rvector2.h"
#include "libs/graphic/GraphicNode.h"
#include "libs/graphic/animation.h"

int main() {
    raylib::InitWindow(Core::WINDOW_WIDTH, Core::WINDOW_HEIGHT, "demo");
    raylib::SetTargetFPS(Core::FPS);

    const int NODE_SIZE = 50;
    GraphicNode* node = new GraphicNode(200, 200, NODE_SIZE, false);
    GraphicNode* node_2 = new GraphicNode(200-NODE_SIZE, 200, NODE_SIZE, false);

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
        std::bind(&nodeTransform<GraphicNode>, node_2, Core::WINDOW_WIDTH-NODE_SIZE, Core::WINDOW_HEIGHT-NODE_SIZE, elapseTime, currTime, Animate::TRANS_TIME)
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
        std::bind(&nodeTransform<GraphicNode>, node_2, Core::WINDOW_WIDTH-NODE_SIZE, Core::WINDOW_HEIGHT-NODE_SIZE, elapseTime, currTime, Animate::TRANS_TIME)
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
        std::cerr << node_2->x << ' ' << node_2->y << '\n';
    }

    raylib::CloseWindow();

    delete node;
    delete node_2;
    delete elapseTime;
    delete currTime;

    return 0;
}
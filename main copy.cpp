#include "global.h"

const int ANIMATE_FADEIN_SPEED = 5;
const int ANIMATE_FADEOUT_SPEED = 5;
const float ANIMATE_TRANS_SPEED = 100;

struct Node {
	float x, y;
	int size;
	raylib::Color currColor, trueColor;
	bool isSqr; // 1 -> square | 0 -> circle
    Node() {}
    Node(float _x, float _y, int _s, raylib::Color _cc, raylib::Color _tc, bool _sqr) {
        x = _x; y = _y; size = _s;
        currColor = _cc;
        trueColor = _tc;
        isSqr = _sqr;
    }
    void draw() {
        if (isSqr) {
            raylib::DrawRectangle(x, y, size, size, currColor);
        } else {
            float radius = (float) size / 2.0;
            raylib::DrawCircleV(raylib::Vector2{x+radius,y+radius}, radius, currColor);
        }
    }
};

bool nodeFadeIn(Node* pNode) {
    assert(pNode->trueColor.a >= pNode->currColor.a);
    if (pNode->trueColor.a - pNode->currColor.a <= ANIMATE_FADEIN_SPEED) {
        pNode->currColor.a = pNode->trueColor.a;
        return true;
    } else {
        pNode->currColor.a += ANIMATE_FADEIN_SPEED;
        return false;
    }
}

bool nodeTransform(Node* pNode, int x, int y, float* elapse) {
    float dist = ANIMATE_TRANS_SPEED * (*elapse);
    raylib::Vector2 direction = raylib::Vector2{(float)(x - pNode->x), (float)(y - pNode->y)};
    float len = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (dist >= len) {
        pNode->x = x;
        pNode->y = y;
        return true;
    } else {
        pNode->x += direction.x / len * dist;
        pNode->y += direction.y / len * dist;
        return false;
    }
}

bool nodeFadeOut(Node* pNode) {
    if (pNode->currColor.a <= ANIMATE_FADEIN_SPEED) {
        pNode->currColor.a = 0;
        return true;
    } else {
        pNode->currColor.a -= ANIMATE_FADEOUT_SPEED;
        return false;
    }
}

void runScenes(std::queue<std::vector<std::function<bool()>>> &queueOfScenes) {
    if (!queueOfScenes.empty()) {
        for (int i = (int)queueOfScenes.front().size()-1; i >= 0; --i) {
            if (queueOfScenes.front()[i]()) {
                queueOfScenes.front()[i] = queueOfScenes.front().back();
                queueOfScenes.front().pop_back();
            }
        }
        if (queueOfScenes.front().empty()) {
            queueOfScenes.pop();
        }
    }
}

int main() {
    raylib::InitWindow(500, 500, "demo");
    raylib::SetTargetFPS(60);

    Node* node = new Node(100, 100, 50, CLITERAL(raylib::Color){230, 41, 55, 0}, CLITERAL(raylib::Color){230, 41, 55, 255}, true);
    Node* node_2 = new Node(0, 0, 50, CLITERAL(raylib::Color){0, 228, 48, 0}, CLITERAL(raylib::Color){0, 228, 48, 255}, false);

    std::queue<std::vector<std::function<bool()>>> queueOfScenes;

    float* elapseTime = new float;

    queueOfScenes.push({
        std::bind(&nodeFadeIn, node),   
        std::bind(&nodeFadeIn, node_2)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform, node, 400, 400, elapseTime),
        std::bind(&nodeTransform, node_2, 350, 400, elapseTime)
    });
    queueOfScenes.push({
        std::bind(&nodeFadeOut, node)
    });
    queueOfScenes.push({
        std::bind(&nodeFadeIn, node)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform, node, 300, 400, elapseTime),
        std::bind(&nodeTransform, node_2, 450, 450, elapseTime)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform, node, 300, 300, elapseTime),
        std::bind(&nodeTransform, node_2, 0, 450, elapseTime)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform, node, 0, 0, elapseTime)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform, node, 0, 450, elapseTime),
        std::bind(&nodeTransform, node_2, 450, 0, elapseTime)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform, node, 450, 450, elapseTime),
        std::bind(&nodeTransform, node_2, 0, 0, elapseTime)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform, node, 450, 0, elapseTime),
        std::bind(&nodeTransform, node_2, 0, 450, elapseTime)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform, node, 0, 0, elapseTime),
        std::bind(&nodeTransform, node_2, 450, 450, elapseTime)
    });
    queueOfScenes.push({
        std::bind(&nodeFadeOut, node),
        std::bind(&nodeFadeOut, node_2)
    });

    while (!raylib::WindowShouldClose()) {
        *elapseTime = raylib::GetFrameTime();
        runScenes(queueOfScenes);
        raylib::BeginDrawing();
            raylib::ClearBackground(raylib::WHITE);
            node->draw();
            node_2->draw();
        raylib::EndDrawing();
    }

    raylib::CloseWindow();

    delete node;
    delete node_2;
    delete elapseTime;

    return 0;
}
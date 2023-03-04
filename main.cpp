#include "global.h"

raylib::Vector2 operator - (const raylib::Vector2 &a, const raylib::Vector2 &b) {
    return raylib::Vector2{a.x-b.x, a.y-b.y};
}

struct Node {
	double x, y;
    double lx, ly;
	int size;
	raylib::Color currColor, trueColor;
    double transparent;
	bool isSqr; // 1 -> square | 0 -> circle
    Node() {}
    Node(double _x, double _y, int _s, raylib::Color _cc, raylib::Color _tc, bool _sqr) {
        lx = x = _x; ly = y = _y; size = _s;
        currColor = _cc;
        trueColor = _tc;
        isSqr = _sqr;
    }
    void draw() {
        if (isSqr) {
            raylib::DrawRectangle(x, y, size, size, currColor);
        } else {
            double radius = (double) size / 2.0;
            raylib::DrawCircleV(raylib::Vector2{(float)(x+radius),(float)(y+radius)}, radius, currColor);
        }
    }
};

bool nodeFadeIn(Node* pNode, double* elapseTime) {
    double inc = Animate::FADEIN_SPEED * *elapseTime;
    if ((pNode->transparent+=inc) >= pNode->trueColor.a) {
        pNode->currColor.a = pNode->trueColor.a;
        return true;
    } else {
        pNode->currColor.a = pNode->transparent;
        return false;
    }
}

bool nodeFadeOut(Node* pNode, double* elapseTime) {
    double dec = Animate::FADEOUT_SPEED * *elapseTime;
    if ((pNode->transparent-=dec) <= 0) {
        pNode->currColor.a = 0;
        return true;
    } else {
        pNode->currColor.a = pNode->transparent;
        return false;
    }
}

float getDist(float x, float y, float u, float v) {
    return sqrt((x-u)*(x-u) + (y-v)*(y-v));
}

double bezier(double S, double T, double t) {
    // std::pair<double,double> A(0,0);
    // std::pair<double,double> B(T+500000,-500);
    // std::pair<double,double> C(0-500000,S+500);
    // std::pair<double,double> D(T,S);

    // std::pair<double,double> A(0,0);
    // std::pair<double,double> B(T+500000,-500);
    // std::pair<double,double> C(0-500000,S+500);
    // std::pair<double,double> D(T,S);

    std::pair<double,double> A(0,0);
    std::pair<double,double> B(T,0);
    std::pair<double,double> C(0,S);
    std::pair<double,double> D(T,S);
    // A -> B -> C -> D
    double p = t / T;
    double tA = -p*p*p + 3*p*p - 3*p + 1;
    double tB = 3*p*p*p - 6*p*p + 3*p;
    double tC = -3*p*p*p + 3*p*p;
    double tD = p*p*p;
    double rY = A.second * tA + B.second * tB + C.second * tC + D.second * tD;
    return rY;
}

bool nodeTransform(Node* pNode, int Tx, int Ty, double* elapseTime, double* currTime, double transTime) {
    double Ux = Tx - pNode->lx;
    double Uy = Ty - pNode->ly;
    double leng = sqrt(Ux*Ux + Uy*Uy);
    double distance = bezier(leng, transTime, std::min(transTime, (*currTime) + (*elapseTime)));
    pNode->x = pNode->lx + Ux / leng * distance;
    pNode->y = pNode->ly + Uy / leng * distance;
    if ((*currTime) + (*elapseTime) >= transTime) {
        pNode->lx = pNode->x = Tx;
        pNode->ly = pNode->y = Ty;
        return true;
    } else {
        return false;
    }
}


void runScenes(std::queue<std::vector<std::function<bool()>>> &queueOfScenes, double* currTime, double* elapseTime) {
    if (!queueOfScenes.empty()) {
        for (int i = (int)queueOfScenes.front().size()-1; i >= 0; --i) {
            if (queueOfScenes.front()[i]()) {
                queueOfScenes.front()[i] = queueOfScenes.front().back();
                queueOfScenes.front().pop_back();
            }
        }
        if (queueOfScenes.front().empty()) {
            queueOfScenes.pop();
            *currTime = 0;
        } else {
            *currTime += *elapseTime;
        }
    }
}

int main() {
    raylib::InitWindow(Core::WINDOW_WIDTH, Core::WINDOW_HEIGHT, "demo");
    raylib::SetTargetFPS(Core::FPS);

    const int NODE_SIZE = 50;
    Node* node = new Node(10, 10, NODE_SIZE, CLITERAL(raylib::Color){230, 41, 55, 0}, CLITERAL(raylib::Color){230, 41, 55, 160}, true);
    Node* node_2 = new Node(0, 0, NODE_SIZE, CLITERAL(raylib::Color){0, 228, 48, 0}, CLITERAL(raylib::Color){0, 228, 48, 160}, true);

    std::queue<std::vector<std::function<bool()>>> queueOfScenes;

    double* elapseTime = new double(0);
    double* currTime = new double(0);

    queueOfScenes.push({
        std::bind(&nodeFadeIn, node, elapseTime),   
        std::bind(&nodeFadeIn, node_2, elapseTime)
    });

    queueOfScenes.push({
        std::bind(&nodeTransform, node, Core::WINDOW_WIDTH-NODE_SIZE, Core::WINDOW_HEIGHT-NODE_SIZE, elapseTime, currTime, Animate::TRANS_TIME),
        std::bind(&nodeTransform, node_2, Core::WINDOW_WIDTH-NODE_SIZE, Core::WINDOW_HEIGHT-NODE_SIZE*2, elapseTime, currTime, Animate::TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeFadeOut, node, elapseTime)
    });
    queueOfScenes.push({
        std::bind(&nodeFadeIn, node, elapseTime)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform, node, 300, 400, elapseTime, currTime, Animate::TRANS_TIME),
        std::bind(&nodeTransform, node_2, 450, 450, elapseTime, currTime, Animate::TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform, node, 300, 300, elapseTime, currTime, Animate::TRANS_TIME),
        std::bind(&nodeTransform, node_2, 0, 450, elapseTime, currTime, Animate::TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform, node, 0, 0, elapseTime, currTime, Animate::TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform, node, 0, 450, elapseTime, currTime, Animate::TRANS_TIME),
        std::bind(&nodeTransform, node_2, 450, 0, elapseTime, currTime, Animate::TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform, node, 450, 450, elapseTime, currTime, Animate::TRANS_TIME),
        std::bind(&nodeTransform, node_2, 0, 0, elapseTime, currTime, Animate::TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform, node, 450, 0, elapseTime, currTime, Animate::TRANS_TIME),
        std::bind(&nodeTransform, node_2, 0, 450, elapseTime, currTime, Animate::TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform, node, 0, 0, elapseTime, currTime, Animate::TRANS_TIME),
        std::bind(&nodeTransform, node_2, 450, 450, elapseTime, currTime, Animate::TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeFadeOut, node, elapseTime),
        std::bind(&nodeFadeOut, node_2, elapseTime)
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
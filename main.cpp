#include "global.h"

raylib::Vector2 operator - (const raylib::Vector2 &a, const raylib::Vector2 &b) {
    return raylib::Vector2{a.x-b.x, a.y-b.y};
}

// WXGA | 16 : 10
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 800;

const double ANIMATE_FADEIN_SPEED = 512;
const double ANIMATE_FADEOUT_SPEED = 512;
const double ANIMATE_TRANS_TIME = 1.5;

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
    double inc = ANIMATE_FADEIN_SPEED * *elapseTime;
    if ((pNode->transparent+=inc) >= pNode->trueColor.a) {
        pNode->currColor.a = pNode->trueColor.a;
        return true;
    } else {
        pNode->currColor.a = pNode->transparent;
        return false;
    }
}

bool nodeFadeOut(Node* pNode, double* elapseTime) {
    double dec = ANIMATE_FADEOUT_SPEED * *elapseTime;
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

std::pair<double,double> unitVector(double x, double y, double u, double v) {
    double Vx = u - x;
    double Vy = v - y; 
    double len = sqrt(Vx*Vx+Vy*Vy);
    return std::make_pair(Vx / len, Vy / len);
}

double bezier(double S, double T, double t) {
    // std::pair<double,double> A(0,0);
    // std::pair<double,double> B(T/2,0);
    // std::pair<double,double> C(0,S);
    // std::pair<double,double> D(T,S);
    std::pair<double,double> A(0,0);
    std::pair<double,double> B(T,0);
    std::pair<double,double> C(0,S);
    std::pair<double,double> D(T,S);
    // A -> B -> C -> D
    double p = t / T;

    // double x_a = A.x + (B.x - A.x) * p;
    // double y_a = A.y + (B.y - A.y) * p;
    // double x_b = B.x + (C.x - B.x) * p;
    // double y_b = B.y + (C.y - B.y) * p;
    // double x_c = C.x + (D.x - C.x) * p;
    // double y_c = C.y + (D.y - C.y) * p;

    // double x_d = x_a + (x_b - x_a) * p;
    // double y_d = y_a + (y_b - y_a) * p;
    // double x_e = x_b + (x_c - x_b) * p;
    // double y_e = y_b + (y_c - y_b) * p;

    // double x_g = x_d + (x_e - x_d) * p;
    // double y_g = y_d + (y_e - y_d) * p;

    double tA = -p*p*p + 3*p*p - 3*p + 1;
    double tB = 3*p*p*p - 6*p*p + 3*p;
    double tC = -3*p*p*p + 3*p*p;
    double tD = p*p*p;

    // double rX = A.first * tA + B.first * tB + C.first * tC + D.first * tD;
    double rY = A.second * tA + B.second * tB + C.second * tC + D.second * tD;

    std::cerr << " >>+ " << S << ' ' << p << ' ' << rY << '\n';

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
    raylib::InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "demo");
    raylib::SetTargetFPS(360);

    const int NODE_SIZE = 50;
    Node* node = new Node(100, 100, NODE_SIZE, CLITERAL(raylib::Color){230, 41, 55, 0}, CLITERAL(raylib::Color){230, 41, 55, 255}, true);
    Node* node_2 = new Node(0, 0, NODE_SIZE, CLITERAL(raylib::Color){0, 228, 48, 0}, CLITERAL(raylib::Color){0, 228, 48, 255}, true);

    std::queue<std::vector<std::function<bool()>>> queueOfScenes;

    double* elapseTime = new double(0);
    double* currTime = new double(0);

    queueOfScenes.push({
        std::bind(&nodeFadeIn, node, elapseTime),   
        std::bind(&nodeFadeIn, node_2, elapseTime)
    });

    queueOfScenes.push({
        std::bind(&nodeTransform, node, WINDOW_WIDTH-NODE_SIZE, WINDOW_HEIGHT-NODE_SIZE, elapseTime, currTime, ANIMATE_TRANS_TIME),
        std::bind(&nodeTransform, node_2, WINDOW_WIDTH-NODE_SIZE, WINDOW_HEIGHT-NODE_SIZE*2, elapseTime, currTime, ANIMATE_TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeFadeOut, node, elapseTime)
    });
    queueOfScenes.push({
        std::bind(&nodeFadeIn, node, elapseTime)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform, node, 300, 400, elapseTime, currTime, ANIMATE_TRANS_TIME),
        std::bind(&nodeTransform, node_2, 450, 450, elapseTime, currTime, ANIMATE_TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform, node, 300, 300, elapseTime, currTime, ANIMATE_TRANS_TIME),
        std::bind(&nodeTransform, node_2, 0, 450, elapseTime, currTime, ANIMATE_TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform, node, 0, 0, elapseTime, currTime, ANIMATE_TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform, node, 0, 450, elapseTime, currTime, ANIMATE_TRANS_TIME),
        std::bind(&nodeTransform, node_2, 450, 0, elapseTime, currTime, ANIMATE_TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform, node, 450, 450, elapseTime, currTime, ANIMATE_TRANS_TIME),
        std::bind(&nodeTransform, node_2, 0, 0, elapseTime, currTime, ANIMATE_TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform, node, 450, 0, elapseTime, currTime, ANIMATE_TRANS_TIME),
        std::bind(&nodeTransform, node_2, 0, 450, elapseTime, currTime, ANIMATE_TRANS_TIME)
    });
    queueOfScenes.push({
        std::bind(&nodeTransform, node, 0, 0, elapseTime, currTime, ANIMATE_TRANS_TIME),
        std::bind(&nodeTransform, node_2, 450, 450, elapseTime, currTime, ANIMATE_TRANS_TIME)
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
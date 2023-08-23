#ifndef GRAPHIC_GRAPH_H
#define GRAPHIC_GRAPH_H

#include <set>
#include <queue>

#include "raylib.h"
#include "../../core/ccppfunc.h"
#include "../../global.h"
#include "../../rcore/rVector2.h"
#include "../../animation/ListOfOperationsGroups.h"
#include "GraphicNode.h"

struct CoreEdge {
    int x, y, w;
};

class Observer {
public:
    Vector2 curPos;
    Vector2 acceleration;
public:
    Observer() {}
    Observer(Vector2 pos) : curPos(pos) {}
    virtual void draw() = 0;
};

class GraphEdge: public Observer {
public:
    GraphicNode* nodeA;
    GraphicNode* nodeB;
    Color lineColor;
    Color *pLineColor;
    float constant, eqLen;
    int cost;

    GraphEdge() = default;
    GraphEdge(GraphicNode* na, GraphicNode* nb, float _constant, float _eqLen);

    void setCost(int _cost);

    void resetColor();

    void draw() override;
};

class GraphicGraph: public Observer {
private:
    void dfs(int u, std::vector<int>& mark, int num, ListOfOperationsGroups* ALOG);
    
    class DSU {
    private:
        std::vector<int> fa;
    public:
        DSU(int n);
        int getRoot(int x) {
            return fa[x] < 0 ? x : fa[x] = getRoot(fa[x]);
        }
        void unite(int u, int v) {
            if (fa[u] > fa[v]) {
                std::swap(u, v);
            }
            fa[u] += fa[v];
            fa[v] = u;
        }
    };

public:
    int numNode, numEdge;
    std::vector<GraphicNode*> nodes;
    std::vector<GraphEdge*> edges;
    GraphicNode* holdNode;
    bool isPhysicsLocked;

    GraphicGraph() : isPhysicsLocked(false), holdNode(nullptr) {}

    void create(int _numNode, std::vector<CoreEdge>& edg);

    void destroy();

    void update();

    void updatePosition();

    Vector2 getCenter();

    ExitStatus initialize(int nNode, int nEdge, ListOfOperationsGroups* ALOG);
    ExitStatus initialize(int nNode, std::vector<CoreEdge>& edg, ListOfOperationsGroups* ALOG);
    ExitStatus initialize(std::string str, ListOfOperationsGroups* ALOG);

    ExitStatus findConnectedComponents(ListOfOperationsGroups* ALOG);
    ExitStatus findMinimumSpanningTree(ListOfOperationsGroups* ALOG);
    ExitStatus dijkstra(int source, ListOfOperationsGroups* ALOG);

    void draw() override;

    void resetColor();
    void resetSubtext();
    void reset();
};

#endif
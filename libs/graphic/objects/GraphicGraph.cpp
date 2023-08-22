#include "GraphicGraph.h"

GraphicGraph::DSU::DSU(int n) {
    fa.assign(n, -1);
}

GraphEdge::GraphEdge(GraphicNode* na, GraphicNode* nb, float _constant, float _eqLen) 
    : nodeA(na), nodeB(nb), constant(_constant), eqLen(_eqLen) {
        resetColor();
}

void GraphEdge::setCost(int _cost) {
    cost = _cost;
}

void GraphEdge::draw() {
    DrawLineEx(nodeA->getCenter(), nodeB->getCenter(), Graphic::ARROW_LINE_WIDTH_SMALL, pLineColor == nullptr ? lineColor : *pLineColor);
    float margin = 4;
    float fontSize = 24;
    float spacing = 2;
    Vector2 vect = nodeB->getCenter() - nodeA->getCenter();
    std::string str = cf::num2str(cost);
    Vector2 dim = MeasureTextEx(*Gfont::defaultFontSmall, str.c_str(), fontSize, spacing);
    if (nodeA->getCenter().y < nodeB->getCenter().y) {
        // left
        if (nodeA->getCenter().x >= nodeB->getCenter().x) {
            DrawTextEx(*Gfont::defaultFontSmall, str.c_str(), trans((nodeA->getCenter()+nodeB->getCenter())/2, normVector(revVector(vect)), margin), fontSize, spacing, pLineColor == nullptr ? lineColor : *pLineColor);
        } else {
            DrawTextEx(*Gfont::defaultFontSmall, str.c_str(), trans((nodeA->getCenter()+nodeB->getCenter())/2, normVector(revVector(vect)), margin) - Vector2{0.f, dim.y}, fontSize, spacing, pLineColor == nullptr ? lineColor : *pLineColor);
        }
    } else {
        if (nodeA->getCenter().x >= nodeB->getCenter().x) {
            DrawTextEx(*Gfont::defaultFontSmall, str.c_str(), trans((nodeA->getCenter()+nodeB->getCenter())/2, normVector(vect), margin) - Vector2{0.f, dim.y}, fontSize, spacing, pLineColor == nullptr ? lineColor : *pLineColor);
        } else {
            DrawTextEx(*Gfont::defaultFontSmall, str.c_str(), trans((nodeA->getCenter()+nodeB->getCenter())/2, normVector(vect), margin), fontSize, spacing, pLineColor == nullptr ? lineColor : *pLineColor);
        }
    }
}

void GraphEdge::resetColor() {
    pLineColor = &Theme::currTheme.ARROW_LINE;
}

void GraphicGraph::create(int _numNode, std::vector<CoreEdge>& edg) {
    numNode = _numNode;
    numEdge = edg.size();
    nodes.resize(numNode);
    for (int i = 0; i < numNode; ++i) {
        nodes[i] = new GraphicNode(
            GetRandomValue(0, Window::WIDTH),
            GetRandomValue(0, Window::HEIGHT), 
            Graphic::NODE_SIZE_SMALL,
            Graphic::NODE_BORDER_WIDTH_SMALL,
            false,
            Gfont::defaultFontSmall,
            i,
            ""
        );
    }
    edges.resize(numEdge);
    for (int i = 0; i < numEdge; ++i) {
        edges[i] = new GraphEdge(nodes[edg[i].x], nodes[edg[i].y], 1, 50);
        edges[i]->setCost(edg[i].w);
    }
}

void GraphicGraph::destroy() {
    // for (int i = 0; i < numEdge; ++i) {
    //     delete edges[i];
    // }
    // for (int i = 0; i < numNode; ++i) {
    //     delete nodes[i];
    // }
    assert(numEdge == (int)edges.size());
}

void GraphicGraph::update() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        for (int i = 0; i < numNode; ++i) {
            if (CheckCollisionPointCircle(GetMousePosition(), nodes[i]->getCenter(), nodes[i]->size / 2)) {
                holdNode = nodes[i];
            }
        }
    } else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (holdNode != nullptr) {
            holdNode->x = GetMousePosition().x;
            holdNode->y = GetMousePosition().y;
        }
    } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        holdNode = nullptr;
    }
    if (IsKeyPressed(KEY_G)) {
        isPhysicsLocked ^= 1;
    }
    int subStep = 3;
    for (int i = 0; i < subStep; ++i) {
        updatePosition();
    }
}

void GraphicGraph::updatePosition() {
    if (isPhysicsLocked) return;
    std::vector<Vector2> accNodes(numNode, Z_VECT);
    for (int i = 0; i < numNode; ++i) {
        for (int j = i+1; j < numNode; ++j) {
            float repConst = 20000;
            float d = dist(nodes[i]->getCenter(), nodes[j]->getCenter());
            Vector2 acc = unitVector(nodes[i]->getCenter() - nodes[j]->getCenter()) * repConst / d / d;
            accNodes[i] += acc;
            accNodes[j] += revVector(acc);
        }
    }
    for (int i = 0; i < numNode; ++i) {
        float repConst = 0.003;
        float distUp = nodes[i]->getCenter().y;
        float distDown = Window::HEIGHT - nodes[i]->getCenter().y;
        float distLeft = nodes[i]->getCenter().x;
        float distRight = Window::WIDTH - nodes[i]->getCenter().x;
        Vector2 accUp = Vector2{0,-1} * repConst * distUp;
        Vector2 accDown = Vector2{0,1} * repConst * distDown;
        Vector2 accLeft = Vector2{-1,0} * repConst * distLeft;
        Vector2 accRight = Vector2{1,0} * repConst * distRight;
        accNodes[i] += accUp + accDown + accLeft + accRight;
    }
    // std::cerr << nodes[0]->acceleration.x << ' ' << nodes[0]->acceleration.y << '\n';
    for (int i = 0; i < numEdge; ++i) {
        float d = dist(edges[i]->nodeA->getCenter(), edges[i]->nodeB->getCenter());
        Vector2 acc = unitVector(edges[i]->nodeA->getCenter() - edges[i]->nodeB->getCenter()) * log(d / edges[i]->eqLen) * edges[i]->constant;
        accNodes[edges[i]->nodeA->nVal] += revVector(acc);
        accNodes[edges[i]->nodeB->nVal] += acc;
    }
    for (int i = 0; i < numEdge; ++i) {
        for (int j = i+1; j < numEdge; ++j) {
            float repConst = 2000;
            Vector2 pA = (edges[i]->nodeA->getCenter()+edges[i]->nodeB->getCenter())/2;
            Vector2 pB = (edges[j]->nodeA->getCenter()+edges[j]->nodeB->getCenter())/2;
            float d = dist(pA, pB);
            Vector2 acc = unitVector(pA - pB) * repConst / d / d;
            accNodes[edges[i]->nodeA->nVal] += acc;
            accNodes[edges[i]->nodeB->nVal] += acc;
            accNodes[edges[j]->nodeA->nVal] += revVector(acc);
            accNodes[edges[j]->nodeB->nVal] += revVector(acc);
        }
    }
    for (int i = 0; i < numEdge; ++i) {
        for (int j = 0; j < numNode; ++j) if (nodes[j] != edges[i]->nodeA && nodes[j] != edges[i]->nodeB) {
            float repConst = 2000;
            Vector2 pA = (edges[i]->nodeA->getCenter()+edges[i]->nodeB->getCenter())/2;
            Vector2 pB = nodes[j]->getCenter();
            float d = dist(pA, pB);
            Vector2 acc = unitVector(pA - pB) * repConst / d / d;
            accNodes[edges[i]->nodeA->nVal] += acc / 2;
            accNodes[edges[i]->nodeB->nVal] += acc / 2;
            accNodes[j] += revVector(acc);
        }
    }
    Vector2 center = getCenter();

    // float gravity = 0.02;
    // Vector2 realCenter = Vector2{WINDOW_WIDTH/2.0f, WINDOW_HEIGHT/2.0f};
    // Vector2 accGrav = (realCenter - center) * gravity;
    // for (int i = 0; i < numNode; ++i) {
    //     nodes[i]->addAcceleration(accGrav);
    // }

    bool allSame = true;
    for (int i = 0; i < numNode-1; ++i) {
        float d_1 = dist(nodes[i]->getCenter(), center);
        float d_2 = dist(nodes[i+1]->getCenter(), center);
        if (fabs(d_1) < Geo::EPS) continue;
        if (fabs(d_2) < Geo::EPS) continue;

        Vector2 yVect_1 = unitVector(nodes[i]->getCenter() - center);
        float m_1 = (accNodes[i] * yVect_1) / vsqrlen(yVect_1);
        Vector2 trans_1 = yVect_1 * m_1 / d_1;

        Vector2 yVect_2 = unitVector(nodes[i+1]->getCenter() - center);
        float m_2 = (accNodes[i+1] * yVect_2) / vsqrlen(yVect_2);
        Vector2 trans_2 = yVect_2 * m_2 / d_2;
        
        // std::cerr << fabs(diff) << '\n';
        if (fabs(trans_1.x - trans_2.x) > Geo::EPS || fabs(trans_1.y - trans_2.y) > Geo::EPS) {
            allSame = false;
            break;
        }
    }
    for (int i = 0; i < numNode; ++i) {
        if (allSame) {
            if (fabs(dist(nodes[i]->getCenter(), center)) < Geo::EPS) continue;
            Vector2 yVect = unitVector(nodes[i]->getCenter() - center);
            float n = (accNodes[i] * yVect) / vsqrlen(yVect);
            accNodes[i] = yVect * n;
        } 
        // nodes[i]->acceleration = nodes[i]->acceleration * (!allSame);
    }
    // if (allSame) {
    //     std::cerr << "STOP MOVING!!\n";
    // }
    for (int i = 0; i < numNode; ++i) {
        if (nodes[i] != holdNode) {
            Vector2 newPos = nodes[i]->getCenter() + accNodes[i];
            nodes[i]->x = newPos.x - nodes[i]->size / 2;
            nodes[i]->y = newPos.y - nodes[i]->size / 2;
        }
    }
}

Vector2 GraphicGraph::getCenter() {
    Vector2 center = {0,0};
    for (int i = 0; i < numNode; ++i) {
        center = center + nodes[i]->getCenter();
    }
    center.x /= numNode;
    center.y /= numNode; 
    return center;
}

ExitStatus GraphicGraph::initialize(int nNode, int nEdge, ListOfOperationsGroups* ALOG) {
    if (nNode < 1 || nNode > Core::MAX_NUM_GRAPH_NODE) {
        return ExitMess::FAIL_GRAPH_NNODE_OOB;
    }
    if (nEdge < 0 || nEdge > Core::MAX_NUM_GRAPH_EDGE) {
        return ExitMess::FAIL_GRAPH_NEDGE_OOB;
    }
    if (nEdge < 0 || nEdge > nNode * (nNode - 1) / 2) {
        return ExitStatus(false, "Number of edge is out of bounds");
    }

    std::vector<CoreEdge> edges;
    std::set<std::pair<int,int>> s;
    while ((int)edges.size() < nEdge) {
        int x = GetRandomValue(0, nNode-1);
        int y = GetRandomValue(0, nNode-1);
        while (x == y || s.count(std::make_pair(std::min(x,y), std::max(x,y)))) {
            x = GetRandomValue(0, nNode-1);
            y = GetRandomValue(0, nNode-1);
        }
        s.insert(std::make_pair(std::min(x,y), std::max(x,y)));
        edges.push_back({x, y, GetRandomValue(1, 99)});
    }

    return initialize(nNode, edges, ALOG);
}

ExitStatus GraphicGraph::initialize(int nNode, std::vector<CoreEdge>& edges, ListOfOperationsGroups* ALOG) {
    if (nNode < 1 || nNode > Core::MAX_NUM_GRAPH_NODE) {
        return ExitMess::FAIL_GRAPH_NNODE_OOB;
    }
    if ((int)edges.size() < 0 || (int)edges.size() > Core::MAX_NUM_GRAPH_EDGE) {
        return ExitMess::FAIL_GRAPH_NEDGE_OOB;
    }
    if ((int)edges.size() < 0 || (int)edges.size() > nNode * (nNode - 1) / 2) {
        return ExitStatus(false, "Number of edge is out of bounds");
    }
    for (int i = 0; i < (int)edges.size(); ++i) {
        if (edges[i].x < 0 || edges[i].x >= nNode) {
            return ExitMess::FAIL_GRAPH_NODE_LABEL_OOB;
        }
        if (edges[i].y < 0 || edges[i].y >= nNode) {
            return ExitMess::FAIL_GRAPH_NODE_LABEL_OOB;
        }
    }

    ALOG->clearGroup();
    ALOG->resetCode();
    create(nNode, edges);
    for (int i = 0; i < numNode; ++i) {
        nodes[i]->appear();
    }

    ALOG->addNewGroup();

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicGraph::initialize(std::string str, ListOfOperationsGroups* ALOG) {
    int nNode = 0;
    std::vector<CoreEdge> edges;

    std::stringstream ss(str);
    ss >> nNode;
    for (int i = 0; i < nNode; ++i) {
        for (int j = 0; j < nNode; ++j) {
            int w;
            ss >> w;
            if (i < j && fabs(w) > Geo::EPS) {
                edges.push_back({i, j, w});
            }
        }
    }
    return initialize(nNode, edges, ALOG);   
}

void GraphicGraph::dfs(int u, std::vector<int>& mark, int num, ListOfOperationsGroups* ALOG) {
    mark[u] = num;
    ALOG->addNewGroup();
    ALOG->animateNodeFromNormalToHighlight(nodes[u], mark[u]);
    for (int i = 0; i < numEdge; ++i) {
        if (edges[i]->nodeA->nVal == u || edges[i]->nodeB->nVal == u) {
            int v = u ^ edges[i]->nodeA->nVal ^ edges[i]->nodeB->nVal;
            if (mark[v] == -1) {
                dfs(v, mark, num, ALOG);
            }
        }
    }
}

ExitStatus GraphicGraph::findConnectedComponents(ListOfOperationsGroups* ALOG) {
    ALOG->clearGroup();
    ALOG->resetCode();
    reset();

    std::vector<int> mark(numNode, -1);
    int num = 0;
    for (int i = 0; i < numNode; ++i) {
        if (mark[i] == -1) {
            dfs(i, mark, num++, ALOG);
        }
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicGraph::findMinimumSpanningTree(ListOfOperationsGroups* ALOG) {
    ALOG->clearGroup();
    ALOG->resetCode();
    reset();

    std::sort(edges.begin(), edges.end(), [&](GraphEdge* a, GraphEdge* b) {
        return a->cost < b->cost;
    });

    DSU dsu(numNode);
    for (int i = 0; i < numEdge; ++i) {
        int u = dsu.getRoot(edges[i]->nodeA->nVal);
        int v = dsu.getRoot(edges[i]->nodeB->nVal);
        if (u != v) {
            ALOG->addNewGroup();
            ALOG->animateArrowFromNormalToFocus(edges[i]);
            dsu.unite(u, v);
        }
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}

ExitStatus GraphicGraph::dijkstra(int source, ListOfOperationsGroups* ALOG) {
    ALOG->clearGroup();
    ALOG->resetCode();
    reset();

    std::priority_queue<std::pair<int, int>> heap;
    std::vector<int> dist(numNode, 0x3f3f3f3f);

    dist[source] = 0;
    heap.emplace(-dist[source], source);

    ALOG->addNewGroup();
    ALOG->animateTransText(&nodes[source]->sub, "", cf::num2str(dist[source]));

    while (!heap.empty()) {
        int u = heap.top().second;
        int w = -heap.top().first;
        heap.pop();

        if (w != dist[u]) continue;

        ALOG->addNewGroup();
        ALOG->animateNodeFromNormalToIter(nodes[u]);

        for (int i = 0; i < numEdge; ++i) {
            if (u == edges[i]->nodeA->nVal || u == edges[i]->nodeB->nVal) {
                int v = u ^ edges[i]->nodeA->nVal ^ edges[i]->nodeB->nVal;
                if (dist[v] > dist[u] + edges[i]->cost) {
                    ALOG->addNewGroup();
                    ALOG->animateArrowFromNormalToIter(edges[i]);
                    
                    ALOG->addNewGroup();
                    if (dist[v] == 0x3f3f3f3f) {
                        ALOG->animateTransText(&nodes[v]->sub, "", cf::num2str(dist[u] + edges[i]->cost));
                    } else {
                        ALOG->animateTransText(&nodes[v]->sub, cf::num2str(dist[v]), cf::num2str(dist[u] + edges[i]->cost));
                    }
                    dist[v] = dist[u] + edges[i]->cost;
                    heap.emplace(-dist[v], v);
                }
            }
        }

        ALOG->addNewGroup();
        ALOG->animateNodeFromIterToNearIter(nodes[u]);
    }

    ALOG->build();

    return ExitMess::SUCCESS;
}


void GraphicGraph::resetColor() {
    for (int i = 0; i < numNode; ++i) {
        nodes[i]->resetColor();
    }
    for (int i = 0; i < numEdge; ++i) {
        edges[i]->resetColor();
    }
}

void GraphicGraph::reset() {
    resetColor();
}


void GraphicGraph::draw() {
    update();
    for (int i = 0; i < numEdge; ++i) {
        edges[i]->draw();
    }
    for (int i = 0; i < numNode; ++i) {
        nodes[i]->draw();
    }
    // for (int i = 0; i < numNode; ++i) {
    //     DrawLineEx(nodes[i]->getCenter(), nodes[i]->getCenter()+nodes[i]->acceleration * 1000, 2, RED);
    // }
    Vector2 center = getCenter();
    // for (int i = 0; i < numNode; ++i) {
    //     Vector2 yVect = unitVector(nodes[i]->getCenter() - center);
    //     Vector2 xVect = {yVect.y, -yVect.x};
    //     float n = (nodes[i]->acceleration * yVect) / vsqrlen(yVect);
    //     float m = (nodes[i]->acceleration % yVect) / vsqrlen(yVect);
    //     DrawLineEx(nodes[i]->getCenter(), nodes[i]->getCenter() + yVect * n * 1000, 2, BLUE);
    //     DrawLineEx(nodes[i]->getCenter(), nodes[i]->getCenter() + xVect * m * 1000, 2, GREEN);
    // }
    DrawCircleV(center, 3, ORANGE);
}
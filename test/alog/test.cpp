#include "libs/conf_raylib.h"
#include "libs/global.h"
#include "libs/rcore/rColor.h"
#include "libs/graphic/objects/GraphicSinglyLinkedList.h"
#include "libs/animation/ListOfOperationsGroups.h"
#include "libs/animation/animation.h"

int main() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);

    InitWindow(Window::WIDTH, Window::HEIGHT, "demo");
    SetTargetFPS(Window::FPS);

    Gfont::loadFont();

    GraphicSinglyLinkedList li;

    ListOfOperationsGroups ALOG;
    ALOG.setMainObj(&li);

    OperationsGroups<GraphicSinglyLinkedList> group;

    li.pHead = new GraphicSinglyNode(Graphic::LL_ORG_X, Graphic::LL_ORG_Y, Graphic::NODE_SIZE, false, 0);
    GraphicSinglyNode* curr = li.pHead;
    curr->appear();
    for (int i = 1; i < 10; ++i) {
        GraphicSinglyNode* tmp = new GraphicSinglyNode(curr->x + Graphic::LL_NODE_DIST, curr->y, Graphic::NODE_SIZE, false, i);
        curr->setNext(tmp);
        curr->aNext.appear();
        curr->aNext.maximize();
        curr = curr->pNext;
        curr->appear();
    }

    GraphicSinglyLinkedList li2;

    auto func = [&](int k) {
        Animate::queueOfScenes.pushToNewScene(std::bind(&Animate::fadeInKthNode<GraphicSinglyLinkedList>, &li2, k, &Animate::queueOfScenes.currTime, Animate::FADEIN_TIME));
    };

    auto func2 = [&](int k) {
        Animate::queueOfScenes.pushToNewScene(std::bind(&Animate::fadeOutKthNode<GraphicSinglyLinkedList>, &li2, k, &Animate::queueOfScenes.currTime, Animate::FADEOUT_TIME));
    };

    auto func3 = [&](GraphicSinglyLinkedList* l, int k) {
        Animate::queueOfScenes.pushToNewScene(std::bind(&Animate::focusKthNode<GraphicSinglyLinkedList>, l, k, &Animate::queueOfScenes.currTime, Animate::FOCUS_TIME));
    };

    ALOG.setMainObj(&li2);

    group.reset();
    group.setObj(&li2);
    for (int i = 0; i < 10; ++i) {
        GraphicSinglyNode* curr = li2.pHead;
        for (int k = i; k--; curr = curr->pNext);
        // group.pushBackFunc(std::bind(func, i));
        // group.pushBackFunc(std::bind(func3, &li2, i));
        group.pushBackFunc(std::bind(&GraphicSinglyLinkedList::focusAtKthNode, &li2, i, true));
        curr->focus();
        // curr->appear();
    }

    ALOG.pushBackGroup(group);

    group.reset();
    group.setObj(&li2);
    for (int i = 0; i < 10; ++i) {
        GraphicSinglyNode* curr = li2.pHead;
        for (int k = i; k--; curr = curr->pNext);
        curr->vanish();
        group.pushBackFunc(std::bind(func2, i));
    }
    ALOG.pushBackGroup(group);

    // ALOG.runAt(1);
    // ALOG.runAt(1);
    // ALOG.runAt(1);

    ALOG.run();

    // ALOG.runAt(0);
    // ALOG.runAt(1);
    // ALOG.runAt(0);
    // ALOG.runAt(1);
    // ALOG.runAt(1);
    // ALOG.runAt(1);
    // ALOG.runAt(0);
    // ALOG.runAt(0);
    // ALOG.runAt(0);

    while (!WindowShouldClose()) {
        Animate::elapseTime = GetFrameTime();
        Animate::queueOfScenes.run();
        BeginDrawing();
            ClearBackground(WHITE);
            li2.draw();
        EndDrawing();
    }

    CloseWindow();

    Gfont::unloadFont();

    li.destroy();
    li2.destroy();
    group.destroy();
    ALOG.destroy();

    return 0;
}
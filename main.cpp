#include "libs/conf_raylib.h"
#include "libs/global.h"
#include "libs/graphic/screens/ScreenCircularLinkedList.h"
#include "libs/graphic/screens/ScreenDoublyLinkedList.h"
#include "libs/graphic/screens/ScreenDynamicArray.h"
#include "libs/graphic/screens/ScreenMainMenu.h"
#include "libs/graphic/screens/ScreenMainMenuCs163.h"
#include "libs/graphic/screens/ScreenQueue.h"
#include "libs/graphic/screens/ScreenSinglyLinkedList.h"
#include "libs/graphic/screens/ScreenStack.h"
#include "libs/graphic/screens/ScreenStaticArray.h"
#include "libs/graphic/screens/ScreenHashTable.h"
#include "libs/graphic/screens/ScreenAVLTree.h"
#include "libs/graphic/screens/ScreenHeapMin.h"
#include "libs/graphic/screens/ScreenHeapMax.h"

int main() {
    SetRandomSeed(time(nullptr));
    srand(time(nullptr));
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);

    InitWindow(Window::WIDTH, Window::HEIGHT, App::title);
    SetTargetFPS(Window::FPS);

    SetExitKey(0);

    // Load
    Gicon::loadIcons();
    Gfont::loadFont();

    Theme::loadTheme();

    // Load Screens
    Layout::initialize();
    LayoutCs163::initialize();
    Screen::screenViews[Screen::SINGLY_LINKED_LIST] = new Screen::ScreenSinglyLinkedList();
    Screen::screenViews[Screen::DOUBLY_LINKED_LIST] = new Screen::ScreenDoublyLinkedList();
    Screen::screenViews[Screen::CIRCULAR_LINKED_LIST] = new Screen::ScreenCircularLinkedList();
    Screen::screenViews[Screen::STACK] = new Screen::ScreenStack();
    Screen::screenViews[Screen::QUEUE] = new Screen::ScreenQueue();
    Screen::screenViews[Screen::STATIC_ARRAY] = new Screen::ScreenStaticArray();
    Screen::screenViews[Screen::DYNAMIC_ARRAY] = new Screen::ScreenDynamicArray();
    Screen::screenViews[Screen::MAIN_MENU] = new Screen::ScreenMainMenu();

    Screen::screenViews[Screen::HASH_TABLE] = new Screen::ScreenHashTable();
    Screen::screenViews[Screen::AVL_TREE] = new Screen::ScreenAVLTree();
    Screen::screenViews[Screen::HEAP_MIN] = new Screen::ScreenHeapMin();
    Screen::screenViews[Screen::HEAP_MAX] = new Screen::ScreenHeapMax();
    Screen::screenViews[Screen::MAIN_MENU_CS163] = new Screen::ScreenMainMenuCs163();
    Screen::load();
    Screen::setScreen(Screen::MAIN_MENU_CS163);
    
    _setmode(_fileno(stdout), _O_U16TEXT);
    
    while (!WindowShouldClose()) {
        Animate::elapseTime = GetFrameTime(); // DO NOT DELETE
        BeginDrawing();
            ClearBackground(Theme::currTheme.BACKGROUND);
            Screen::draw();
        EndDrawing();
    }

    Screen::destroy();
    Gfont::unloadFont();
    
    CloseWindow();

    // Unload

    Screen::unload();

    return 0;
}
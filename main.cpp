#include "libs/conf_raylib.h"
#include "libs/global.h"
#include "libs/graphic/screens/ScreenCircularLinkedList.h"
#include "libs/graphic/screens/ScreenDoublyLinkedList.h"
#include "libs/graphic/screens/ScreenDynamicArray.h"
#include "libs/graphic/screens/ScreenMainMenu.h"
#include "libs/graphic/screens/ScreenQueue.h"
#include "libs/graphic/screens/ScreenSinglyLinkedList.h"
#include "libs/graphic/screens/ScreenStack.h"
#include "libs/graphic/screens/ScreenStaticArray.h"

int main() {
    SetRandomSeed(time(nullptr));
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);

    InitWindow(Window::WIDTH, Window::HEIGHT, App::title);
    SetTargetFPS(Window::FPS);

    SetExitKey(0);

    // Load
    Gicon::loadIcons();
    Gfont::loadFont();

    Theme::loadTheme();

    // screen.load();
    // Load Screens
    Layout::initialize();
    Screen::screenViews[Screen::SINGLY_LINKED_LIST] = new Screen::ScreenSinglyLinkedList();
    Screen::screenViews[Screen::DOUBLY_LINKED_LIST] = new Screen::ScreenDoublyLinkedList();
    Screen::screenViews[Screen::CIRCULAR_LINKED_LIST] = new Screen::ScreenCircularLinkedList();
    Screen::screenViews[Screen::STACK] = new Screen::ScreenStack();
    Screen::screenViews[Screen::QUEUE] = new Screen::ScreenQueue();
    Screen::screenViews[Screen::STATIC_ARRAY] = new Screen::ScreenStaticArray();
    Screen::screenViews[Screen::DYNAMIC_ARRAY] = new Screen::ScreenDynamicArray();
    Screen::screenViews[Screen::MAIN_MENU] = new Screen::ScreenMainMenu();
    Screen::load();
    Screen::setScreen(Screen::MAIN_MENU);
    
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
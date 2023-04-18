#include "screen.h"

void Screen::load() {
    Layout::initialize();

    screenSLL.load();
    screenDLL.load();
    screenST.load();
    screenMM.load();

    screenInit[SINGLY_LINKED_LIST] = std::bind(&ScreenSinglyLinkedList::init, &screenSLL);
    screenInit[DOUBLY_LINKED_LIST] = std::bind(&ScreenDoublyLinkedList::init, &screenDLL);
    screenInit[STACK]              = std::bind(&ScreenStack::init, &screenST);
    screenInit[MAIN_MENU]          = std::bind(&ScreenMainMenu::init, &screenMM);

    screenDraw[SINGLY_LINKED_LIST] = std::bind(&ScreenSinglyLinkedList::draw, &screenSLL);
    screenDraw[DOUBLY_LINKED_LIST] = std::bind(&ScreenDoublyLinkedList::draw, &screenDLL);
    screenDraw[STACK]              = std::bind(&ScreenStack::draw, &screenST);
    screenDraw[MAIN_MENU]          = std::bind(&ScreenMainMenu::draw, &screenMM);

    screenDest[SINGLY_LINKED_LIST] = std::bind(&ScreenSinglyLinkedList::destroy, &screenSLL);
    screenDest[DOUBLY_LINKED_LIST] = std::bind(&ScreenDoublyLinkedList::destroy, &screenDLL);
    screenDest[STACK]              = std::bind(&ScreenStack::destroy, &screenST);
    screenDest[MAIN_MENU]          = std::bind(&ScreenMainMenu::destroy, &screenMM);

    setScreen(MAIN_MENU);
}
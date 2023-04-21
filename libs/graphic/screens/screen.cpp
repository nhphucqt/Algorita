#include "screen.h"

void Screen::ScreenClass::load() {
    Layout::initialize();

    screenSLL.load();
    screenDLL.load();
    screenST.load();
    screenQU.load();
    screenMM.load();
    screenSA.load();
    screenDA.load();

    screenInit[SINGLY_LINKED_LIST] = std::bind(&ScreenSinglyLinkedList::init, &screenSLL);
    screenInit[DOUBLY_LINKED_LIST] = std::bind(&ScreenDoublyLinkedList::init, &screenDLL);
    screenInit[STACK]              = std::bind(&ScreenStack::init, &screenST);
    screenInit[QUEUE]              = std::bind(&ScreenQueue::init, &screenQU);
    screenInit[STATIC_ARRAY]       = std::bind(&ScreenStaticArray::init, &screenSA);
    screenInit[DYNAMIC_ARRAY]      = std::bind(&ScreenDynamicArray::init, &screenDA);
    screenInit[MAIN_MENU]          = std::bind(&ScreenMainMenu::init, &screenMM);

    screenDraw[SINGLY_LINKED_LIST] = std::bind(&ScreenSinglyLinkedList::draw, &screenSLL);
    screenDraw[DOUBLY_LINKED_LIST] = std::bind(&ScreenDoublyLinkedList::draw, &screenDLL);
    screenDraw[STACK]              = std::bind(&ScreenStack::draw, &screenST);
    screenDraw[QUEUE]              = std::bind(&ScreenQueue::draw, &screenQU);
    screenDraw[STATIC_ARRAY]       = std::bind(&ScreenStaticArray::draw, &screenSA);
    screenDraw[DYNAMIC_ARRAY]      = std::bind(&ScreenDynamicArray::draw, &screenDA);
    screenDraw[MAIN_MENU]          = std::bind(&ScreenMainMenu::draw, &screenMM);

    screenDest[SINGLY_LINKED_LIST] = std::bind(&ScreenSinglyLinkedList::destroy, &screenSLL);
    screenDest[DOUBLY_LINKED_LIST] = std::bind(&ScreenDoublyLinkedList::destroy, &screenDLL);
    screenDest[STACK]              = std::bind(&ScreenStack::destroy, &screenST);
    screenDest[QUEUE]              = std::bind(&ScreenQueue::destroy, &screenQU);
    screenDest[STATIC_ARRAY]       = std::bind(&ScreenStaticArray::destroy, &screenSA);
    screenDest[DYNAMIC_ARRAY]      = std::bind(&ScreenDynamicArray::destroy, &screenDA);
    screenDest[MAIN_MENU]          = std::bind(&ScreenMainMenu::destroy, &screenMM);

    setScreen(MAIN_MENU);
}
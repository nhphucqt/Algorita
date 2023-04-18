#include "ScreenMainMenu.h"

ScreenMainMenu::ScreenMainMenu() {}

void ScreenMainMenu::load() {
    title = StyledText(App::title, Gfont::titleFont);
}

void ScreenMainMenu::init() {}

void ScreenMainMenu::draw() {
    title.draw((Window::WIDTH - title.dim.x) / 2, 90, Theme::currTheme.TITLE);
    if (GuiButton(Rectangle{250, 300, 300, 200}, "Singly Linked List")) {
        Layout::setScreen(Screen::SINGLY_LINKED_LIST);
    }
    if (GuiButton(Rectangle{650, 300, 300, 200}, "Doubly Linked List")) {
        Layout::setScreen(Screen::DOUBLY_LINKED_LIST);
    }
    if (GuiButton(Rectangle{1050, 300, 300, 200}, "Circular Linked List")) {

    }
    if (GuiButton(Rectangle{50, 580, 300, 200}, "Stack")) {
        Layout::setScreen(Screen::STACK);
    }
    if (GuiButton(Rectangle{450, 580, 300, 200}, "Queue")) {

    }
    if (GuiButton(Rectangle{850, 580, 300, 200}, "Static Array")) {

    }
    if (GuiButton(Rectangle{1250, 580, 300, 200}, "Dynamic Array")) {

    }
    Theme::draw(true);
}

void ScreenMainMenu::destroy() {}
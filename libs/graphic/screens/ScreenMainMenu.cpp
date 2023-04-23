#include "ScreenMainMenu.h"

ScreenMainMenu::ScreenMainMenu() {}

void ScreenMainMenu::load() {
    title = StyledText(App::title, Gfont::titleFont);
    desc = StyledText(App::description, Gfont::defaultFont);
    author = StyledText(App::author, Gfont::defaultFont);
}

void ScreenMainMenu::init() {}

void ScreenMainMenu::draw() {
    int yAxis = 40;
    int padding = 5;
    title.draw((Window::WIDTH - title.dim.x) / 2, yAxis, Theme::currTheme.TITLE);
    desc.draw((Window::WIDTH - desc.dim.x) / 2, yAxis + title.dim.y + padding*2, Theme::currTheme.TITLE);
    author.draw((Window::WIDTH - author.dim.x) / 2, yAxis + title.dim.y + padding + desc.dim.y + padding, Theme::currTheme.TITLE);
    if (GuiButton(Rectangle{250, 300, 300, 200}, "Singly Linked List")) {
        Layout::setScreen(Screen::SINGLY_LINKED_LIST);
    }
    if (GuiButton(Rectangle{650, 300, 300, 200}, "Doubly Linked List")) {
        Layout::setScreen(Screen::DOUBLY_LINKED_LIST);
    }
    if (GuiButton(Rectangle{1050, 300, 300, 200}, "Circular Linked List")) {
        Layout::setScreen(Screen::CIRCULAR_LINKED_LIST);
    }
    if (GuiButton(Rectangle{50, 580, 300, 200}, "Stack")) {
        Layout::setScreen(Screen::STACK);
    }
    if (GuiButton(Rectangle{450, 580, 300, 200}, "Queue")) {
        Layout::setScreen(Screen::QUEUE);
    }
    if (GuiButton(Rectangle{850, 580, 300, 200}, "Static Array")) {
        Layout::setScreen(Screen::STATIC_ARRAY);
    }
    if (GuiButton(Rectangle{1250, 580, 300, 200}, "Dynamic Array")) {
        Layout::setScreen(Screen::DYNAMIC_ARRAY);
    }
    Theme::draw(true);
}

void ScreenMainMenu::destroy() {}
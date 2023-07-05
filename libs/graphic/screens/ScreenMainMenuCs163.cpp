#include "ScreenMainMenuCs163.h"

Screen::ScreenMainMenuCs163::ScreenMainMenuCs163() {}
Screen::ScreenMainMenuCs163::~ScreenMainMenuCs163() {}

void Screen::ScreenMainMenuCs163::load() {
    title = StyledText(App::title, Gfont::titleFont);
    desc = StyledText(App::description, Gfont::defaultFont);
    author = StyledText(App::author, Gfont::defaultFont);
}

void Screen::ScreenMainMenuCs163::init() {}

void Screen::ScreenMainMenuCs163::draw() {
    int yAxis = 40;
    int padding = 5;
    title.draw((Window::WIDTH - title.dim.x) / 2, yAxis, Theme::currTheme.TITLE);
    desc.draw((Window::WIDTH - desc.dim.x) / 2, yAxis + title.dim.y + padding*2, Theme::currTheme.TITLE);
    author.draw((Window::WIDTH - author.dim.x) / 2, yAxis + title.dim.y + padding + desc.dim.y + padding, Theme::currTheme.TITLE);
    if (GuiButton(Rectangle{250, 300, 300, 200}, "Hash Table")) {
        Layout::setScreen(Screen::HASH_TABLE);
    }
    if (GuiButton(Rectangle{650, 300, 300, 200}, "AVL Tree")) {
        Layout::setScreen(Screen::DOUBLY_LINKED_LIST);
    }
    if (GuiButton(Rectangle{1050, 300, 300, 200}, "234 Tree")) {
        Layout::setScreen(Screen::CIRCULAR_LINKED_LIST);
    }
    if (GuiButton(Rectangle{250, 580, 300, 200}, "Heap")) {
        Layout::setScreen(Screen::STACK);
    }
    if (GuiButton(Rectangle{650, 580, 300, 200}, "Trie")) {
        Layout::setScreen(Screen::QUEUE);
    }
    if (GuiButton(Rectangle{1050, 580, 300, 200}, "Graph")) {
        Layout::setScreen(Screen::STATIC_ARRAY);
    }
    Theme::draw(true);
}

void Screen::ScreenMainMenuCs163::destroy() {}
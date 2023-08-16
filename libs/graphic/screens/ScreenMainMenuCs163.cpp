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
        LayoutCs163::setScreen(0, Screen::HASH_TABLE);
    }
    if (GuiButton(Rectangle{650, 300, 300, 200}, "AVL Tree")) {
        LayoutCs163::setScreen(1, Screen::AVL_TREE);
    }
    if (GuiButton(Rectangle{1050, 300, 300, 200}, "234 Tree")) {
        LayoutCs163::setScreen(2, Screen::CIRCULAR_LINKED_LIST);
    }
    if (GuiButton(Rectangle{50, 580, 300, 200}, "Heap Min")) {
        LayoutCs163::setScreen(3, Screen::HEAP_MIN);
    }
    if (GuiButton(Rectangle{450, 580, 300, 200}, "Heap Max")) {
        LayoutCs163::setScreen(4, Screen::HEAP_MAX);
    }
    if (GuiButton(Rectangle{850, 580, 300, 200}, "Trie")) {
        LayoutCs163::setScreen(5, Screen::TRIE);
    }
    if (GuiButton(Rectangle{1250, 580, 300, 200}, "Graph")) {
        LayoutCs163::setScreen(6, Screen::DYNAMIC_ARRAY);
    }
    Theme::draw(true);
}

void Screen::ScreenMainMenuCs163::destroy() {}
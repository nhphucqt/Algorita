#include "globalLayoutCs163.h"

void LayoutCs163::initialize() {
    dropDownList.init(Rectangle{130,0,240,50}, "Hash Table ;AVL Tree ;234 Tree ;Heap Min ;Heap Max ;Trie ;Graph ");
}

void LayoutCs163::setScreen(int id, Screen::ScreenType screen) {
    Screen::updateScreen(screen);
    if (0 <= id && id < Core::NUM_DATA_STRUCTURE) {
        dropDownList.setActive(id);
    }
}


void LayoutCs163::drawTopNavigation(bool keyActive) {
    if (GuiButton(Rectangle{0,0,120,50}, App::title)) {
        LayoutCs163::setScreen(-1, Screen::MAIN_MENU_CS163);
    }
    if (dropDownList.draw()) {
        if (!dropDownList.isEditMode()) {
            switch (dropDownList.getActive()) {
                case 0:
                    LayoutCs163::setScreen(0, Screen::HASH_TABLE);
                break;
                case 1:
                    LayoutCs163::setScreen(1, Screen::AVL_TREE);
                break;
                case 2:
                    LayoutCs163::setScreen(2, Screen::QUEUE);
                break;
                case 3:
                    LayoutCs163::setScreen(3, Screen::HEAP_MIN);
                break;
                case 4:
                    LayoutCs163::setScreen(4, Screen::HEAP_MAX);
                break;
                case 5:
                    LayoutCs163::setScreen(5, Screen::STATIC_ARRAY);
                break;
                case 6:
                    LayoutCs163::setScreen(6, Screen::DYNAMIC_ARRAY);
                break;
            }
        }
    }
    Theme::draw(keyActive);
}
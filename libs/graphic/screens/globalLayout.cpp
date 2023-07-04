#include "globalLayout.h"

void Layout::initialize() {
    dropDownList.init(Rectangle{130,0,240,50}, "Singly Linked List ;Doubly Linked List ;Circular Linked List ;Stack;Queue ;Static Array ;Dynamic Array ");
}

void Layout::setScreen(Screen::ScreenType screen) {
    Screen::updateScreen(screen);
    if (0 <= screen && screen < Core::NUM_DATA_STRUCTURE) {
        dropDownList.setActive(screen);
    }
}


void Layout::drawTopNavigation(bool keyActive) {
    if (GuiButton(Rectangle{0,0,120,50}, App::title)) {
        Layout::setScreen(Screen::MAIN_MENU_CS163);
    }
    if (dropDownList.draw()) {
        if (!dropDownList.isEditMode()) {
            switch (dropDownList.getActive()) {
                case 0:
                    Layout::setScreen(Screen::SINGLY_LINKED_LIST);
                break;
                case 1:
                    Layout::setScreen(Screen::DOUBLY_LINKED_LIST);
                break;
                case 2:
                    Layout::setScreen(Screen::CIRCULAR_LINKED_LIST);
                break;
                case 3:
                    Layout::setScreen(Screen::STACK);
                break;
                case 4:
                    Layout::setScreen(Screen::QUEUE);
                break;
                case 5:
                    Layout::setScreen(Screen::STATIC_ARRAY);
                break;
                case 6:
                    Layout::setScreen(Screen::DYNAMIC_ARRAY);
                break;
            }
        }
    }
    Theme::draw(keyActive);
}
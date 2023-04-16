#include "globalLayout.h"

void Layout::initialize() {
    dropDownList.init(Rectangle{130,0,240,50}, "Singly Linked List ;Doubly Linked List ;Circular Linked List ;Stack;Queue ;Static Array ;Dynamic Array ");
}

void Layout::drawTopNavigation() {
    if (GuiButton(Rectangle{0,0,120,50}, App::title)) {
        Screen::updateScreen(Screen::MAIN_MENU);
    }
    if (dropDownList.draw()) {
        if (!dropDownList.isEditMode()) {
            switch (dropDownList.getActive()) {
                case 0:
                    Screen::updateScreen(Screen::SINGLY_LINKED_LIST);
                break;
                case 3:
                    Screen::updateScreen(Screen::STACK);
                break;
            }
        }
    }
    Theme::draw();
}
#include "globalLayout.h"

void Layout::initialize() {
    appNameButton = GraphicTextButton(Rectangle{0,0,122,50}, App::title);
    dropDownList.init(Rectangle{122,0,240,50}, "Singly Linked List ;Doubly Linked List ;Circular Linked List ;Stack;Queue ;Static Array ;Dynamic Array ");
}

void Layout::drawTopNavigation() {
    appNameButton.draw();
    dropDownList.draw();
    if (GuiButton(Rectangle{Window::WIDTH - 40 - 5, 5, 40, 40}, Theme::currTheme.iconText.c_str())) {
        Theme::toggleTheme();
    }
}
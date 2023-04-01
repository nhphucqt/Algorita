#include "globalLayout.h"

void Layout::initialize() {
    appNameButton = GraphicTextButton(Rectangle{0,0,122,50}, App::title);
    SLLButton = GraphicTextButton(Rectangle{122,0,240,50}, "Singly Linked List");
    DLLButton = GraphicTextButton(Rectangle{362,0,240,50}, "Doubly Linked List");
    CLLButton = GraphicTextButton(Rectangle{602,0,251,50}, "Circular Linked List");
    stackButton = GraphicTextButton(Rectangle{853,0,91,50}, "Stack");
    queueButton = GraphicTextButton(Rectangle{944,0,107,50}, "Queue");
    staticArrButton = GraphicTextButton(Rectangle{1051,0,166,50}, "Static Array");
    dynamicArrButton = GraphicTextButton(Rectangle{1217,0,223,50}, "Dynamic Array");
}

void Layout::drawTopNavigation() {
    appNameButton.draw();
    SLLButton.draw();
    DLLButton.draw();
    CLLButton.draw();
    stackButton.draw();
    queueButton.draw();
    staticArrButton.draw();
    dynamicArrButton.draw();
}
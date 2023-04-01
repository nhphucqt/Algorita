#ifndef GLOBAL_LAYOUT_H
#define GLOBAL_LAYOUT_H

#include <iostream>

#include "../../global.h"
#include "../gui/GraphicButton.h"

namespace Layout {
    inline GraphicTextButton appNameButton;
    inline GraphicTextButton SLLButton, DLLButton, CLLButton;
    inline GraphicTextButton stackButton, queueButton;
    inline GraphicTextButton staticArrButton, dynamicArrButton;

    void initialize();
    void drawTopNavigation();
}

#endif
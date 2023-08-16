#ifndef GLOBAL_LAYOUT_CS163_H
#define GLOBAL_LAYOUT_CS163_H

#include <iostream>

#include "../../global.h"
#include "../../rcore/rguiDropDownBox.h"

namespace LayoutCs163 {
    inline DropDownBoxState dropDownList;

    void initialize();
    void setScreen(int id, Screen::ScreenType screen);
    void drawTopNavigation(bool keyActive);
}

#endif
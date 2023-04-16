#ifndef GLOBAL_LAYOUT_H
#define GLOBAL_LAYOUT_H

#include <iostream>

#include "../../global.h"
#include "../../rcore/rguiDropDownBox.h"

namespace Layout {
    inline DropDownBoxState dropDownList;

    void initialize();
    void drawTopNavigation();
}

#endif
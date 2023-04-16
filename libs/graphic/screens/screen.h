#ifndef SCREEN_H
#define SCREEN_H

#include <functional>

#include "../../global.h"
#include "globalLayout.h"
#include "ScreenMainMenu.h"
#include "ScreenSinglyLinkedList.h"
#include "ScreenStack.h"

namespace Screen {
    inline ScreenSinglyLinkedList screenSLL;
    inline ScreenStack            screenST;
    inline ScreenMainMenu         screenMM;

    void load();
}

#endif
#ifndef SCREEN_H
#define SCREEN_H

#include <functional>

#include "../../global.h"
#include "globalLayout.h"
#include "ScreenMainMenu.h"
#include "ScreenSinglyLinkedList.h"
#include "ScreenDoublyLinkedList.h"
#include "ScreenStack.h"
#include "ScreenQueue.h"

namespace Screen {
    inline ScreenSinglyLinkedList screenSLL;
    inline ScreenDoublyLinkedList screenDLL;
    inline ScreenStack            screenST;
    inline ScreenQueue            screenQU;
    inline ScreenMainMenu         screenMM;

    void load();
}

#endif
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
#include "ScreenStaticArray.h"
#include "ScreenDynamicArray.h"

namespace Screen {
    class ScreenClass {
    private:
        ScreenSinglyLinkedList screenSLL;
        ScreenDoublyLinkedList screenDLL;
        ScreenStack            screenST;
        ScreenQueue            screenQU;
        ScreenStaticArray      screenSA;
        ScreenDynamicArray     screenDA;
        ScreenMainMenu         screenMM;

    public:
        void load();
    };
}

#endif
#ifndef SCREEN_MAIN_MENU_H
#define SCREEN_MAIN_MENU_H

#include "../../conf_raylib.h"
#include "../../global.h"
#include "../gui/StyledText.h"
#include "globalLayout.h"

class ScreenMainMenu {
private:
    StyledText title;

public:
    ScreenMainMenu();
    
    void load();
    void init();
    void draw();
    void destroy();
};

#endif
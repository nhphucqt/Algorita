#ifndef SCREEN_MAIN_MENU_H
#define SCREEN_MAIN_MENU_H

#include "../../conf_raylib.h"
#include "../../global.h"
#include "../gui/StyledText.h"
#include "globalLayout.h"
#include "ScreenView.h"

namespace Screen {
    class ScreenMainMenu: public ScreenView {
    private:
        StyledText title;
        StyledText desc;
        StyledText author;

    public:
        ScreenMainMenu();
        ~ScreenMainMenu() override;
        
        void load() override;
        void init() override;
        void draw() override;
        void destroy() override;
    };
}

#endif
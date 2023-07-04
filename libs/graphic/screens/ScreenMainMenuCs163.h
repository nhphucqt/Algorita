#ifndef SCREEN_MAIN_MENU_CS163_H
#define SCREEN_MAIN_MENU_CS163_H

#include "../../conf_raylib.h"
#include "../../global.h"
#include "../gui/StyledText.h"
#include "globalLayout.h"
#include "ScreenView.h"

namespace Screen {
    class ScreenMainMenuCs163: public ScreenView {
    private:
        StyledText title;
        StyledText desc;
        StyledText author;

    public:
        ScreenMainMenuCs163();
        ~ScreenMainMenuCs163() override;
        
        void load() override;
        void init() override;
        void draw() override;
        void destroy() override;
    };
}

#endif
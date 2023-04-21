#ifndef THEME_H
#define THEME_H

#include <string>

#include "../../conf_raylib.h"
#include "../../global.h"

namespace Theme {
    class ColorTheme {
    public:
        std::string iconText;
        std::string stylePath;

        Color BACKGROUND;
        Color TITLE;

        Color NODE_BACKGROUND;
        Color NODE_BACKGROUND_DISABLED;
        Color NODE_BACKGROUND_FOCUS;
        Color NODE_BACKGROUND_FOCUS_REFER;
        Color NODE_BACKGROUND_FOCUS_ITER;
        Color NODE_BACKGROUND_FOCUS_NEAR_ITER;
        Color NODE_BACKGROUND_FOCUS_REMOVE;

        Color NODE_FOREGROUND;
        Color NODE_FOREGROUND_DISABLED;
        Color NODE_FOREGROUND_FOCUS;
        Color NODE_FOREGROUND_FOCUS_ITER;

        Color NODE_BORDER;
        Color NODE_BORDER_DISABLED;
        Color NODE_BORDER_FOCUS;
        Color NODE_BORDER_FOCUS_REFER;
        Color NODE_BORDER_FOCUS_ITER;
        Color NODE_BORDER_FOCUS_REMOVE;

        Color NODE_SUPERTEXT;
        Color NODE_SUBTEXT;

        // ARROW COLOR
        Color ARROW_LINE;
        Color ARROW_LINE_FOCUS;
        Color ARROW_LINE_FOCUS_ITER;

        Color ARROW_HEAD;

        // TEXT BUTTON COLOR
        Color TEXT_BUTTON_BACKGROUND;
        Color TEXT_BUTTON_BACKGROUND_FOCUS;
        Color TEXT_BUTTON_FOREGROUND;
        Color TEXT_BUTTON_FOREGROUND_FOCUS;

        // CODEBLOCK COLOR
        Color CODEBLOCK_BACKGROUND;
        Color CODEBLOCK_BACKGROUND_FOCUS;
        Color CODEBLOCK_FOREGROUND;
        Color CODEBLOCK_FOREGROUND_FOCUS;

        Color EXIT_MESSAGE;

        void load();
    };

    const int LIGHT_THEME_ID = 0;
    const int DARK_THEME_ID = 1;

    inline ColorTheme themes[2];
    inline ColorTheme currTheme;
    inline int currThemeID;

    void loadTheme();
    void setTheme(int id);
    void setLightTheme();
    void setDarkTheme();
    void toggleTheme();

    void draw(bool keyActive);
}


#endif
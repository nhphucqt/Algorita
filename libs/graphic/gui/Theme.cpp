#include "Theme.h"

void Theme::ColorTheme::load() {
    GuiLoadStyle(stylePath.c_str());
}

void Theme::loadTheme() {
    themes[LIGHT_THEME_ID].iconText = Gicon::LIGHT_THEME;
    themes[LIGHT_THEME_ID].stylePath = "assets/styles/light.rgs";

    themes[LIGHT_THEME_ID].BACKGROUND = Color{249,247,247,255};
    themes[LIGHT_THEME_ID].TITLE = Color{17, 45, 78, 255};

    themes[LIGHT_THEME_ID].NODE_BACKGROUND = Color{249,247,247,255};
    themes[LIGHT_THEME_ID].NODE_BACKGROUND_DISABLED = Color{150,150,150,255};
    themes[LIGHT_THEME_ID].NODE_BACKGROUND_FOCUS = GREEN;
    themes[LIGHT_THEME_ID].NODE_BACKGROUND_FOCUS_REFER = BLUE;
    themes[LIGHT_THEME_ID].NODE_BACKGROUND_FOCUS_ITER = ORANGE;
    themes[LIGHT_THEME_ID].NODE_BACKGROUND_FOCUS_NEAR_ITER = Color{255, 226, 204, 255};
    themes[LIGHT_THEME_ID].NODE_BACKGROUND_FOCUS_REMOVE = BROWN;

    themes[LIGHT_THEME_ID].NODE_FOREGROUND = BLACK;
    themes[LIGHT_THEME_ID].NODE_FOREGROUND_DISABLED = BLACK;
    themes[LIGHT_THEME_ID].NODE_FOREGROUND_FOCUS = WHITE;
    themes[LIGHT_THEME_ID].NODE_FOREGROUND_FOCUS_ITER = Color{255, 135, 0, 255};

    themes[LIGHT_THEME_ID].NODE_BORDER = BLACK;
    themes[LIGHT_THEME_ID].NODE_BORDER_DISABLED = Color{60,60,60,255};
    themes[LIGHT_THEME_ID].NODE_BORDER_FOCUS = GREEN;
    themes[LIGHT_THEME_ID].NODE_BORDER_FOCUS_REFER = BLUE;
    themes[LIGHT_THEME_ID].NODE_BORDER_FOCUS_ITER = ORANGE;
    themes[LIGHT_THEME_ID].NODE_BORDER_FOCUS_REMOVE = BROWN;

    themes[LIGHT_THEME_ID].NODE_SUBTEXT = RED;
    themes[LIGHT_THEME_ID].NODE_SUPERTEXT = BLACK;

    // ARROW COLOR
    themes[LIGHT_THEME_ID].ARROW_LINE = BLACK;
    themes[LIGHT_THEME_ID].ARROW_LINE_FOCUS = GREEN;
    themes[LIGHT_THEME_ID].ARROW_LINE_FOCUS_ITER = ORANGE;

    themes[LIGHT_THEME_ID].ARROW_HEAD = BLACK;

    // TEXT BUTTON COLOR
    themes[LIGHT_THEME_ID].TEXT_BUTTON_BACKGROUND = DARKGRAY;
    themes[LIGHT_THEME_ID].TEXT_BUTTON_BACKGROUND_FOCUS = GRAY;
    themes[LIGHT_THEME_ID].TEXT_BUTTON_FOREGROUND = WHITE;
    themes[LIGHT_THEME_ID].TEXT_BUTTON_FOREGROUND_FOCUS = WHITE;

    // CODEBLOCK COLOR
    themes[LIGHT_THEME_ID].CODEBLOCK_BACKGROUND = Color{63, 114, 175, 255};
    themes[LIGHT_THEME_ID].CODEBLOCK_BACKGROUND_FOCUS = Color{17, 45, 78, 255};
    themes[LIGHT_THEME_ID].CODEBLOCK_FOREGROUND = Color{249, 247, 247, 255};
    themes[LIGHT_THEME_ID].CODEBLOCK_FOREGROUND_FOCUS = Color{249, 247, 247, 255};

    themes[LIGHT_THEME_ID].EXIT_MESSAGE = RED;

    // DARK THEME
    themes[DARK_THEME_ID].iconText = Gicon::DARK_THEME;
    themes[DARK_THEME_ID].stylePath = "assets/styles/dark.rgs";

    themes[DARK_THEME_ID].BACKGROUND = Color{41,41,41,255};
    themes[DARK_THEME_ID].TITLE = WHITE;

    themes[DARK_THEME_ID].NODE_BACKGROUND = Color{242, 231, 254, 255};
    themes[DARK_THEME_ID].NODE_BACKGROUND_DISABLED = Color{128, 120, 138, 255};
    themes[DARK_THEME_ID].NODE_BACKGROUND_FOCUS = Color{0, 196, 180, 255};
    themes[DARK_THEME_ID].NODE_BACKGROUND_FOCUS_REFER = Color{75, 156, 211, 255};
    themes[DARK_THEME_ID].NODE_BACKGROUND_FOCUS_ITER = ORANGE;
    themes[DARK_THEME_ID].NODE_BACKGROUND_FOCUS_NEAR_ITER = Color{255, 226, 204, 255};
    themes[DARK_THEME_ID].NODE_BACKGROUND_FOCUS_REMOVE = Color{159, 129, 112, 255};

    themes[DARK_THEME_ID].NODE_FOREGROUND = Color{152, 94, 255, 255};
    themes[DARK_THEME_ID].NODE_FOREGROUND_DISABLED = Color{65, 44, 102, 255};
    themes[DARK_THEME_ID].NODE_FOREGROUND_FOCUS = WHITE;
    themes[DARK_THEME_ID].NODE_FOREGROUND_FOCUS_ITER = Color{255, 135, 0, 255};

    themes[DARK_THEME_ID].NODE_BORDER = Color{187, 134, 252, 255};
    themes[DARK_THEME_ID].NODE_BORDER_DISABLED = Color{82, 58, 110, 255};
    themes[DARK_THEME_ID].NODE_BORDER_FOCUS = Color{0, 196, 180, 255};
    themes[DARK_THEME_ID].NODE_BORDER_FOCUS_REFER = Color{75, 156, 211, 255};
    themes[DARK_THEME_ID].NODE_BORDER_FOCUS_ITER = ORANGE;
    themes[DARK_THEME_ID].NODE_BORDER_FOCUS_REMOVE = Color{159, 129, 112, 255};

    themes[DARK_THEME_ID].NODE_SUPERTEXT = WHITE;
    themes[DARK_THEME_ID].NODE_SUBTEXT = WHITE;

    // ARROW COLOR
    themes[DARK_THEME_ID].ARROW_LINE = LIGHTGRAY;
    themes[DARK_THEME_ID].ARROW_LINE_FOCUS = Color{0, 196, 180, 255};
    themes[DARK_THEME_ID].ARROW_LINE_FOCUS_ITER = ORANGE;

    themes[DARK_THEME_ID].ARROW_HEAD = LIGHTGRAY;

    // TEXT BUTTON COLOR
    themes[DARK_THEME_ID].TEXT_BUTTON_BACKGROUND = DARKGRAY;
    themes[DARK_THEME_ID].TEXT_BUTTON_BACKGROUND_FOCUS = GRAY;
    themes[DARK_THEME_ID].TEXT_BUTTON_FOREGROUND = WHITE;
    themes[DARK_THEME_ID].TEXT_BUTTON_FOREGROUND_FOCUS = WHITE;

    // CODEBLOCK COLOR
    themes[DARK_THEME_ID].CODEBLOCK_BACKGROUND = BLACK;
    themes[DARK_THEME_ID].CODEBLOCK_BACKGROUND_FOCUS = Color{187, 134, 252, 255};
    themes[DARK_THEME_ID].CODEBLOCK_FOREGROUND = WHITE;
    themes[DARK_THEME_ID].CODEBLOCK_FOREGROUND_FOCUS = BLACK;

    themes[DARK_THEME_ID].EXIT_MESSAGE = Color{255, 117, 151, 255};

    // Get last theme
    std::ifstream fin("assets/styles/theme.data");
    if (!fin.is_open()) {
        std::cerr << "ERROR: Cannot open theme.data for reading!!\n";
        currThemeID = 0;
    } else {
        fin >> currThemeID;
        if (currThemeID < 0 || currThemeID > NUM_THEME) {
            currThemeID = 0;
        }
    }
    fin.close();
    setTheme(currThemeID);
}

void Theme::setTheme(int id) {
    currThemeID = id;
    currTheme = themes[id];
    currTheme.load();

    // Save last theme
    std::ofstream fout("assets/styles/theme.data");
    if (!fout.is_open()) {
        std::cerr << "ERROR: Cannot open theme.data for writing!!\n";
    } else {
        fout << currThemeID;
    }
}

void Theme::setLightTheme() {
    setTheme(LIGHT_THEME_ID);
}

void Theme::setDarkTheme() {
    setTheme(DARK_THEME_ID);
}

void Theme::toggleTheme() {
    setTheme(currThemeID ^ 1);
}

void Theme::draw(bool keyActive) {
    if (GuiButton(Rectangle{Window::WIDTH - 40 - 5, 5, 40, 40}, Theme::currTheme.iconText.c_str())) {
        Theme::toggleTheme();
    }
}
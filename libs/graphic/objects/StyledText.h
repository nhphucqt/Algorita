#ifndef STYLED_TEXT_H
#define STYLED_TEXT_H

#include <string>
#include <assert.h>

#include "../../conf_raylib.h"
#include "../../core/ccppfunc.h"
#include "../../rcore/rVector2.h"

class StyledText {
public:
    std::string content;
    Font* font;
    Vector2 dim;

    StyledText();
    StyledText(const std::string &_content, Font* _font);
    StyledText(int _num, Font* _font);

    void draw(const Vector2 &p, const Color &color = BLACK);
    void draw(int x, int y, const Color &color = BLACK);
};

#endif
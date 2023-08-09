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
    float spacing;

    StyledText();
    StyledText(const std::string &_content, Font* _font);
    StyledText(const std::string &_content, Font* _font, float _spacing);
    StyledText(int _num, Font* _font);
    StyledText(int _num, Font* _font, float _spacing);

    void assign(int val);
    void assign(const std::string &text);

    void draw(const Vector2 &p, const Color &color = BLACK);
    void draw(int x, int y, const Color &color = BLACK);
};

#endif
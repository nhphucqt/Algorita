#ifndef STYLED_TEXT_H
#define STYLED_TEXT_H

#include <string>
#include <assert.h>

namespace raylib {
    #include "raylib.h"
}
#include "../core/ccppfunc.h"
#include "../rcore/rvector2.h"

class StyledText {
public:
    std::string content;
    raylib::Font* font;
    raylib::Vector2 dim;

    StyledText();
    StyledText(const std::string &_content, raylib::Font* _font);
    StyledText(int _num, raylib::Font* _font);

    void draw(const raylib::Vector2 &p, const raylib::Color &color = raylib::BLACK);
    void draw(int x, int y, const raylib::Color &color = raylib::BLACK);
};

#endif
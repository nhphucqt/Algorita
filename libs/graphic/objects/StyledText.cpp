#include "StyledText.h"

StyledText::StyledText() {}

StyledText::StyledText(const std::string &_content, raylib::Font* _font) {
    content = _content;
    font = _font;
    dim = raylib::MeasureTextEx(*font, content.c_str(), font->baseSize,  0);
}

StyledText::StyledText(int _num, raylib::Font* _font) {
    content = cf::num2str(_num);
    font = _font;
    dim = raylib::MeasureTextEx(*font, content.c_str(), font->baseSize,  0);
}

void StyledText::draw(const raylib::Vector2 &p, const raylib::Color &color) {
    raylib::DrawTextEx(*font, content.c_str(), p, font->baseSize, 0, color);
}

void StyledText::draw(int x, int y, const raylib::Color &color) {
    draw(toVector2(x,y), color);
}

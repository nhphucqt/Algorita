#include "StyledText.h"

StyledText::StyledText() {}

StyledText::StyledText(const std::string &_content, Font* _font) {
    content = _content;
    font = _font;
    dim = MeasureTextEx(*font, content.c_str(), font->baseSize,  0);
}

StyledText::StyledText(int _num, Font* _font) {
    content = cf::num2str(_num);
    font = _font;
    dim = MeasureTextEx(*font, content.c_str(), font->baseSize,  0);
}

void StyledText::draw(const Vector2 &p, const Color &color) {
    DrawTextEx(*font, content.c_str(), p, font->baseSize, 0, color);
}

void StyledText::draw(int x, int y, const Color &color) {
    draw(toVector2(x,y), color);
}

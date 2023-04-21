#include "StyledText.h"

StyledText::StyledText() {
    font = nullptr;
}

StyledText::StyledText(const std::string &_content, Font* _font, float _spacing) {
    content = _content;
    font = _font;
    spacing = _spacing;
    dim = MeasureTextEx(*font, content.c_str(), font->baseSize, spacing);
}

StyledText::StyledText(const std::string &_content, Font* _font) : StyledText(_content, _font, 0) {}

StyledText::StyledText(int _num, Font* _font) : StyledText(cf::num2str(_num), _font) {}

StyledText::StyledText(int _num, Font* _font, float _spacing) : StyledText(cf::num2str(_num), _font, _spacing) {}

void StyledText::assign(const std::string &text) {
    content = text;
    dim = MeasureTextEx(*font, text.c_str(), font->baseSize, spacing);
}

void StyledText::draw(const Vector2 &p, const Color &color) {
    DrawTextEx(*font, content.c_str(), p, font->baseSize, spacing, color);
}

void StyledText::draw(int x, int y, const Color &color) {
    draw(toVector2(x,y), color);
}

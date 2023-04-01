#include "rguiTextBox.h"

GuiTextBoxState::GuiTextBoxState() {}

GuiTextBoxState::GuiTextBoxState(const Rectangle &_bounds, const char* _text, int _textSize, bool _active) {
    int n = strlen(_text);
    assert(n < _textSize); // _textSize includes '\0'
    bounds = _bounds;
    text = new char[_textSize];
    for (int i = 0; i < _textSize; ++i) {
        text[i] = 0;
    }
    for (int i = 0; i <= n; ++i) {
        text[i] = _text[i];
    }
    textSize = _textSize;
    active = _active;
}

GuiTextBoxState::~GuiTextBoxState() {
    delete[] text;
}

int GuiTextBoxState::getNum() {
    return cf::str2num(text);
}

std::string GuiTextBoxState::getStr() {
    return std::string(text);
}

void GuiTextBoxState::draw() {
    if (GuiTextBox(bounds, text, textSize, active)) {
        active ^= 1;
    }
}
#include "rguiTextBox.h"

GuiTextBoxState::GuiTextBoxState() {}

void GuiTextBoxState::init(const Rectangle &_bounds, const char* _text, int _textSize, bool _digitMode, bool _active) {
    int n = strlen(_text);
    assert(n < _textSize); // _textSize includes '\0'
    bounds = _bounds;
    text = new char[_textSize];
    for (int i = 0; i < _textSize; ++i) {
        text[i] = '\0';
    }
    for (int i = 0; i <= n; ++i) {
        text[i] = _text[i];
    }
    textSize = _textSize;
    digitMode = _digitMode;
    active = _active;
}

void GuiTextBoxState::init(const Rectangle &_bounds, int _textSize, bool _digitMode, bool _active) {
    bounds = _bounds;
    text = new char[_textSize];
    for (int i = 0; i < _textSize; ++i) {
        text[i] = '\0';
    }
    textSize = _textSize;
    digitMode = _digitMode;
    active = _active;
}

GuiTextBoxState::~GuiTextBoxState() {
    delete[] text;
}

int GuiTextBoxState::getNum() {
    fix();
    return cf::str2num(text);
}

std::string GuiTextBoxState::getStr() {
    return std::string(text);
}

void GuiTextBoxState::fix() {
    if (!digitMode) {
        return;
    }
    int shift = 0;
    int len = strlen(text);
    if (len == 0) {
        strcpy(text, "0");
    } else if (strcmp(text, "0") != 0) {
        for (int i = 0; i <= len; ++i) {
            text[i-shift] = text[i];
            if (!isdigit(text[i]) || (text[i] == '0' && i-shift == 0)) {
                shift++;
            }
        }
    }
}

void GuiTextBoxState::setnum(int num) {
    std::string str = cf::num2str(num);
    for (int i = 0; i < (int)str.size(); ++i) {
        text[i] = str[i];
    }
    text[str.size()] = '\0';
}

bool GuiTextBoxState::isActive() const {
    return active;
}

bool GuiTextBoxState::draw() {
    if (GuiTextBox(bounds, text, textSize, active)) {
        active ^= 1;
    }
    fix();
    return active;
}
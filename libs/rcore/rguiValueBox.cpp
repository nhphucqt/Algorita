#include "rguiValueBox.h"

GuiValueBoxState::GuiValueBoxState() {}

GuiValueBoxState::GuiValueBoxState(const Rectangle &_bounds, int _minValue, int _maxValue, bool _active) {
    bounds = _bounds;
    value = 0;
    minValue = _minValue;
    maxValue = _maxValue;
    active = _active;
}

int GuiValueBoxState::getNum() {
    return value;
}

void GuiValueBoxState::draw() {
    if (GuiValueBox(bounds, "abcdef", &value, minValue, maxValue, active)) {
        active ^= 1;
    }
}
#include "rguiToggle.h"

void GuiToggleState::init(Rectangle _bounds, const char* _text, bool _active) {
    bounds = _bounds;
    text = _text;
    active = _active;
}

bool GuiToggleState::justToggle() const {
    return pre ^ active;
}

void GuiToggleState::deactive() {
    pre = active;
    active = false;
}

bool GuiToggleState::draw() {
    pre = active;
    return active = GuiToggle(bounds, text.c_str(), active);
}

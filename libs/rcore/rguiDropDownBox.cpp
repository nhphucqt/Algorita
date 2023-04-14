#include "rguiDropDownBox.h"

void DropDownBoxState::init(Rectangle _bounds, const std::string &_options) {
    bounds = _bounds;
    active = 0;
    editMode = false;
    options = _options;
}

void DropDownBoxState::draw() {
    if (GuiDropdownBox(bounds, options.c_str(), &active, editMode)) {
        editMode ^= 1;
    }
}
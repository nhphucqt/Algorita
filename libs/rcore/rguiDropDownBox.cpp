#include "rguiDropDownBox.h"

void DropDownBoxState::init(Rectangle _bounds, const std::string &_options) {
    bounds = _bounds;
    active = 0;
    editMode = false;
    options = _options;
}

bool DropDownBoxState::draw() {
    if (GuiDropdownBox(bounds, options.c_str(), &active, editMode)) {
        editMode ^= 1;
        return true;
    }
    return false;
}

bool DropDownBoxState::isEditMode() const {
    return editMode;
}

int DropDownBoxState::getActive() const {
    return active;
}
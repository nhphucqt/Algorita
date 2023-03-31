#include "GraphicButton.h"

GraphicTextButton::GraphicTextButton() {
    backColor[0] = Gcolor::TEXT_BUTTON_BACKGROUND;
    backColor[1] = Gcolor::TEXT_BUTTON_BACKGROUND_FOCUS;
    foreColor[0] = Gcolor::TEXT_BUTTON_FOREGROUND;
    foreColor[1] = Gcolor::TEXT_BUTTON_FOREGROUND_FOCUS;
}

GraphicTextButton::GraphicTextButton(const Rectangle &_box, const std::string &text) : GraphicTextButton() {
    box = _box;
    content = StyledText(text, Gfont::defaultFont);
}

GraphicTextButton::GraphicTextButton(float x, float y, float w, float h, const std::string &text) 
: GraphicTextButton(Rectangle{x, y, w, h}, text) {}

bool GraphicTextButton::isHovering() const {
    return CheckCollisionPointRec(GetMousePosition(), box);
}

bool GraphicTextButton::isPressed(int button) const {
    return isHovering() && IsMouseButtonPressed(button);
}

bool GraphicTextButton::isHolding(int button) const {
    return isHovering() && IsMouseButtonDown(button);
}

bool GraphicTextButton::isReleased(int button) const {
    return isHovering() && IsMouseButtonReleased(button);
}

void GraphicTextButton::draw() {
    DrawRectangleRec(box, backColor[isHovering()]);
    content.draw(centerRect(box, content.dim), foreColor[isHovering()]);
}

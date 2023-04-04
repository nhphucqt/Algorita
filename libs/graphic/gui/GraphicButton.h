#ifndef GRAPHIC_BUTTON_H
#define GRAPHIC_BUTTON_H

#include <functional>

#include "../../conf_raylib.h"
#include "../../global.h"
#include "../gui/StyledText.h"
#include "../../rcore/rRectangle.h"

class GraphicTextButton {
public:
    Color backColor[2], foreColor[2];

    Rectangle box;
    StyledText content;

    GraphicTextButton();
    GraphicTextButton(const Rectangle &_box, const std::string &text);
    GraphicTextButton(float x, float y, float w, float h, const std::string &text);

    bool isHovering() const;
    bool isPressed(int button) const;
    bool isHolding(int button) const;
    bool isReleased(int button) const;

    void draw();
};

#endif
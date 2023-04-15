#ifndef RGUI_TOGGLE_H
#define RGUI_TOGGLE_H

#include <string>
#include <iostream>

#include "../conf_raylib.h"

class GuiToggleState {
private:
    Rectangle bounds;
    std::string text;
    bool pre, active;
public:
    void init(Rectangle _bounds, const char* _text, bool _active);

    bool justToggle() const;

    void deactive();

    bool draw();
};

#endif
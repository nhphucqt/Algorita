#ifndef RGUI_VALUEBOX_H
#define RGUI_VALUEBOX_H

#include <string>
#include <cstring>
#include <assert.h>

#include "../conf_raylib.h"
#include "../core/ccppfunc.h"

class GuiValueBoxState {
private:
    Rectangle bounds;
    int value;
    int minValue, maxValue;
    bool active;

public:
    GuiValueBoxState();
    GuiValueBoxState(const Rectangle &_bounds, int _minValue, int _maxValue, bool _active);

    int getNum();
    std::string getStr();

    void draw();
};

#endif
#ifndef RGUI_TEXTBOX_H
#define RGUI_TEXTBOX_H

#include <string>
#include <string.h>
#include <assert.h>

#include "../conf_raylib.h"
#include "../core/ccppfunc.h"

class GuiTextBoxState {
private:
    Rectangle bounds;
    char* text;
    int textSize;
    bool active;

public:
    GuiTextBoxState();
    void init(const Rectangle &_bounds, const char* _text, int _textSize, bool _active);
    void init(const Rectangle &_bounds, int _textSize, bool _active);
    ~GuiTextBoxState();

    int getNum();
    std::string getStr();

    void setnum(int num);

    void draw();
};

#endif
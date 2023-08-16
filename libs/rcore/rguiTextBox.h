#ifndef RGUI_TEXTBOX_H
#define RGUI_TEXTBOX_H

#include <string>
#include <cstring>
#include <assert.h>

#include "../conf_raylib.h"
#include "../core/ccppfunc.h"

class GuiTextBoxState {
private:
    Rectangle bounds;
    char* text;
    int textSize;
    bool active;
    bool digitMode;

public:
    GuiTextBoxState();
    void init(const Rectangle &_bounds, const char* _text, int _textSize, bool _digitMode, bool _active);
    void init(const Rectangle &_bounds, int _textSize, bool _digitMode, bool _active);
    ~GuiTextBoxState();

    int getNum();
    std::string getStr();

    void fix();

    void setnum(int num);
    void setText(std::string text);

    bool isActive() const;

    bool draw();
};

#endif
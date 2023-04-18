#ifndef RGUI_DROP_DOWN_BOX
#define RGUI_DROP_DOWN_BOX

#include <string>

#include "../conf_raylib.h"

class DropDownBoxState {
private:
    Rectangle bounds;
    int active;
    bool editMode;
    std::string options;

public:
    void init(Rectangle _bounds, const std::string &_options);
    bool draw();
    bool isEditMode() const;
    int getActive() const;
    void setActive(int act);
};

#endif
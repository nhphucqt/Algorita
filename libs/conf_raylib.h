// Modified in raygui.h : line 2089
// old : while (editMode && textWidth >= textBounds.width && *text)
// new : while (textWidth >= textBounds.width && *text)

#ifndef CONF_RAYLIB_H
#define CONF_RAYLIB_H

#include "raylib.h"
// #define RAYGUI_IMPLEMENTATION
#define RAYGUI_CUSTOM_ICONS
#include "libs/external/ricons.h"
#include "libs/external/raygui.h"

#undef PI

#endif
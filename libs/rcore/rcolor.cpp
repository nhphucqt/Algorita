#include "rcolor.h"

raylib::Color TRNSP(raylib::Color color, float transparent) {
    color.a = round(color.a * transparent);
    return color;
}
#include "rcolor.h"

raylib::Color TRNSP(raylib::Color color, double transparent) {
    color.a = round(color.a * transparent);
    return color;
}
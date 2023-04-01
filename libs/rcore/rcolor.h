#ifndef RCOLOR_H
#define RCOLOR_H

#include <cmath>

#include "../conf_raylib.h"

Color TRNSP(Color color, float transparent);

Color TRANSCOLOR(const Color &source, const Color &destination, float percent);

#endif
#ifndef ccppfuncUNC_H
#define ccppfuncUNC_H

#include <string>
#include <algorithm>
#include <iostream>

#include "../conf_raylib.h"
#include "../global.h"
#include "../rcore/rvector2.h" 

namespace cf {
    std::string num2str(int x);
    double outerNull(const raylib::Vector2 &v);
    double outerCirc(float *size, const raylib::Vector2 &v);
    double outerSqur(float *size, const raylib::Vector2 &v);
}

#endif
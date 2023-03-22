#ifndef ccppfuncUNC_H
#define ccppfuncUNC_H

#include <string>
#include <algorithm>
#include <iostream>

#include "../conf_raylib.h"
#include "../global.h"
#include "../rcore/rvector2.h" 

namespace cf {
    template<typename T>
    T sqr(T x) {
        return x * x;
    }
    std::string num2str(int x);
    raylib::Vector2 outerNull(const raylib::Vector2 &v);
    raylib::Vector2 outerCirc(float *size, const raylib::Vector2 &v);
    raylib::Vector2 outerSqur(float *size, const raylib::Vector2 &v);

    raylib::Vector2 outerCircLeft(float *size, const raylib::Vector2 &v);
    raylib::Vector2 outerCircRight(float *size, const raylib::Vector2 &v);
    raylib::Vector2 outerSqurLeft(float *size, const raylib::Vector2 &v);
    raylib::Vector2 outerSqurRight(float *size, const raylib::Vector2 &v);
}

#endif
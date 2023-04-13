#ifndef ccppfuncUNC_H
#define ccppfuncUNC_H

#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

#include "../conf_raylib.h"
#include "../global.h"
#include "../rcore/rVector2.h" 

namespace cf {
    template<typename T>
    T sqr(T x) {
        return x * x;
    }
    std::string num2str(int num);
    std::string double2str(double num);

    int str2num(const std::string &str);
    int str2num(const char* str);

    void fixNumStr(std::string &num);

    int getRandomNode();
    
    Vector2 outerNull(const Vector2 &v);
    Vector2 outerCirc(float *size, const Vector2 &v);
    Vector2 outerSqur(float *size, const Vector2 &v);

    Vector2 outerCircLeft(float *size, const Vector2 &v);
    Vector2 outerCircRight(float *size, const Vector2 &v);
    Vector2 outerSqurLeft(float *size, const Vector2 &v);
    Vector2 outerSqurRight(float *size, const Vector2 &v);
}

#endif
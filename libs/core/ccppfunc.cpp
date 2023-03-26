#include "ccppfunc.h"

std::string cf::num2str(int num) {
    if (num == 0) {
        return "0";
    } else {
        std::string str;
        while (num > 0) {
            str += num % 10 +  '0';
            num /= 10;
        }
        std::reverse(str.begin(),str.end());
        return str;
    }
}

int cf::str2num(const std::string &str) {
    int num = 0;
    for (int i = 0; i < (int)str.size(); ++i) {
        num = num * 10 + (str[i] - '0');
    }
    return num;
}


raylib::Vector2 cf::outerNull(const raylib::Vector2 &v) {
    return Z_VECT;
}

raylib::Vector2 cf::outerCirc(float *size, const raylib::Vector2 &v) {
    return resizeVector(v, *size/2);
}

raylib::Vector2 cf::outerSqur(float *size, const raylib::Vector2 &v) {
    double a = angle(X_AXIS, v);
    while (a > Geo::RAD90) {
        a -= Geo::RAD90;
    }
    if (a > Geo::RAD45) {
        a = Geo::RAD90 - a;
    }
    return resizeVector(v, *size / 2 / cos(a));
}

raylib::Vector2 cf::outerCircLeft(float *size, const raylib::Vector2 &v) {
    double d = *size/6;
    return resizeVector(normVector(v), d) + resizeVector(v, sqrt(sqr(*size/2) - sqr(d)));
}

raylib::Vector2 cf::outerCircRight(float *size, const raylib::Vector2 &v) {
    double d = *size/6;
    return resizeVector(revVector(normVector(v)), d) + resizeVector(v, sqrt(sqr(*size/2) - sqr(d)));
}

raylib::Vector2 cf::outerSqurLeft(float *size, const raylib::Vector2 &v) {
    double d = *size/6;
    double a = angle2(X_AXIS, v);
    while (a < 0) {
        a += Geo::RAD90;
    }
    while (a > Geo::RAD90) {
        a -= Geo::RAD90;
    }
    double leng = 0;
    double cross = (double)(*size) / sqrt(2);
    double alpha = fabs(Geo::RAD45 - a);
    double pivot = cross * sin(alpha);
    if (a <= Geo::RAD45) {
        double rem = fabs(pivot - d);
        double beta = d >= pivot ? Geo::RAD45 - alpha : Geo::RAD45 + alpha;
        leng = cross * cos(alpha) - rem / tan(beta);
    } else {
        double beta = Geo::RAD45 + alpha;
        leng = cross * cos(alpha) - (pivot + d) / tan(beta);
    }
    return resizeVector(normVector(v), d) + resizeVector(v, leng);
}

raylib::Vector2 cf::outerSqurRight(float *size, const raylib::Vector2 &v) {
    double d = *size/6;
    double a = angle2(X_AXIS, v);
    while (a > 0) {
        a -= Geo::RAD90;
    }
    while (a < -Geo::RAD90) {
        a += Geo::RAD90;
    }
    double leng = 0;
    double cross = (double)(*size) / sqrt(2);
    double alpha = fabs(-Geo::RAD45 - a);
    double pivot = cross * sin(alpha);
    if (a >= -Geo::RAD45) {
        double rem = fabs(pivot - d);
        double beta = d >= pivot ? Geo::RAD45 - alpha : Geo::RAD45 + alpha;
        leng = cross * cos(alpha) - rem / tan(beta);
    } else {
        double beta = Geo::RAD45 + alpha;
        leng = cross * cos(alpha) - (pivot + d) / tan(beta);
    }
    return resizeVector(revVector(normVector(v)), d) + resizeVector(v, leng);
}
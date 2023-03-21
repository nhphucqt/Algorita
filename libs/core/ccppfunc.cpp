#include "ccppfunc.h"

std::string cf::num2str(int x) {
    if (x == 0) {
        return "0";
    } else {
        std::string ans;
        while (x > 0) {
            ans += x % 10 +  '0';
            x /= 10;
        }
        std::reverse(ans.begin(),ans.end());
        return ans;
    }
}

double cf::outerNull(const raylib::Vector2 &v) {
    return 0;
}

double cf::outerCirc(float *size, const raylib::Vector2 &v) {
    return *size / 2;
}

double cf::outerSqur(float *size, const raylib::Vector2 &v) {
    double a = angle(X_AXIS, v);
    while (a > Geo::RAD90) {
        a -= Geo::RAD90;
    }
    if (a > Geo::RAD45) {
        a = Geo::RAD90 - a;
    }
    std::cerr << " +++ " << a * 180 / Geo::PI << '\n';
    return *size / 2 / cos(a);
}


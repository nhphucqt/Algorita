#include "animation.h"

double Animate::bezier(double t) {
    std::pair<double,double> A(0.0, 0.0);
    std::pair<double,double> B(0.42, 0.0);
    std::pair<double,double> C(0.58, 1.0);
    std::pair<double,double> D(1.0, 1.0);
    double tA = -t*t*t + 3*t*t - 3*t + 1;
    double tB = 3*t*t*t - 6*t*t + 3*t;
    double tC = -3*t*t*t + 3*t*t;
    double tD = t*t*t;
    double rY = A.second * tA + B.second * tB + C.second * tC + D.second * tD;
    return rY;

    // -- Elastic out
    // return S * (sin(-13.0 * (t + 1.0) * acos(-1)/2) * pow(2.0, -10.0 * t) + 1.0);
    // --

    // -- Bounce out
    // const double nl = 7.5625;
    // const double dl = 2.75;
    // if (t < 1.0 / dl) {
    //     return nl * t * t;
    // } else if (t < 2.0 / dl) {
    //     t -= 1.5 / dl;
    //     return nl * t * t + 0.75;
    // } else if (t < 2.5 / dl) {
    //     t -= 2.25 / dl;
    //     return nl * t * t + 0.9375;
    // } else {
    //     t -= 2.625 / dl;
    //     return nl * t * t + 0.984375;
    // }
    // --
}

bool Animate::delay(double* currTime, bool* isReversed) {
    return *isReversed ? *currTime <= 0 : *currTime >= DELAY_TIME;
}

bool Animate::transColor(Color* obj, Color** robj, Color* src, Color* snk, double* currTime, bool* isReversed) {
    if (*isReversed && *currTime <= 0) {
        *robj = src;
        return true;
    }
    if (!*isReversed && *currTime >= TRANS_TIME) {
        *robj = snk;
        return true;
    }
    *robj = nullptr;
    *obj = TRANSCOLOR(*src, *snk, bezier((*currTime) / TRANS_TIME));
    return false;
}

Animate::QueueOfScenes::QueueOfScenes() {
    q = std::list<std::function<bool()>>();
}

void Animate::QueueOfScenes::clearScenes() {
    q.clear();
}

void Animate::QueueOfScenes::push(const std::function<bool()> &func) {
    q.push_back(func);
}

bool Animate::QueueOfScenes::run() {
    bool done = true;
    for (std::list<std::function<bool()>>::iterator curAnim = q.begin(); curAnim != q.end(); ++curAnim) {
        done &= (*curAnim)();
    }
    return done;
}
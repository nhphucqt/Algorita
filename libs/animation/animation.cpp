#include "animation.h"

double Animate::bezier(double S, double T, double t) {
    double p = t / T;

    // std::pair<double,double> A(0,0);
    // std::pair<double,double> B(T+500000,-500);
    // std::pair<double,double> C(0-500000,S+500);
    // std::pair<double,double> D(T,S);

    std::pair<double,double> A(0,0);
    std::pair<double,double> B(T,0);
    std::pair<double,double> C(0,S);
    std::pair<double,double> D(T,S);
    // A -> B -> C -> D
    double tA = -p*p*p + 3*p*p - 3*p + 1;
    double tB = 3*p*p*p - 6*p*p + 3*p;
    double tC = -3*p*p*p + 3*p*p;
    double tD = p*p*p;
    double rY = A.second * tA + B.second * tB + C.second * tC + D.second * tD;
    return rY;

    // -- Elastic out
    // return S * (sin(-13.0 * (p + 1.0) * acos(-1)/2) * pow(2.0, -10.0 * p) + 1.0);
    // --

    // -- Bounce out
    // const double nl = 7.5625;
    // const double dl = 2.75;
    // if (p < 1.0 / dl) {
    //     return S * nl * p * p;
    // } else if (p < 2.0 / dl) {
    //     p -= 1.5 / dl;
    //     return S * (nl * p * p + 0.75);
    // } else if (p < 2.5 / dl) {
    //     p -= 2.25 / dl;
    //     return S * (nl * p * p + 0.9375);
    // } else {
    //     p -= 2.625 / dl;
    //     return S * (nl * p * p + 0.984375);
    // }
    // --
}

Animate::QueueOfScenes::QueueOfScenes() {
    currTime = 0.0;
    q = std::list<std::list<std::function<bool()>>>();
}

void Animate::QueueOfScenes::pushToFrontScene(const std::function<bool()> &func) {
    q.front().push_back(func);
}

void Animate::QueueOfScenes::pushToKthScene(int k, const std::function<bool()> &func) {
    assert(k < (int)q.size());
    std::list<std::list<std::function<bool()>>>::iterator it = q.begin();
    while (k--) {
        ++it;
    }
    it->push_back(func);
}

void Animate::QueueOfScenes::pushToBackScene(const std::function<bool()> &func) {
    q.back().push_back(func);
}

void Animate::QueueOfScenes::pushToNewScene(const std::function<bool()> &func) {
    q.push_back({func});
}

void Animate::QueueOfScenes::pushToNewKthScene(int k, const std::function<bool()> &func) {
    assert(k <= (int)q.size());
    addBlankSceneToKth(k);
    pushToKthScene(k, func);
}

void Animate::QueueOfScenes::pushSceneToBack(const std::list<std::function<bool()>> &scene) {
    q.push_back(scene);
}

void Animate::QueueOfScenes::pushSceneToKth(int k, const std::list<std::function<bool()>> &funcList) {
    assert(k <= (int)q.size());
    std::list<std::list<std::function<bool()>>>::iterator it = q.begin();
    while (k--) {
        ++it;
    }
    q.insert(it, funcList);
}

void Animate::QueueOfScenes::addBlankScene() {
    q.push_back(std::list<std::function<bool()>>());
}

void Animate::QueueOfScenes::addBlankSceneToKth(int k) {
    assert(k <= (int)q.size());
    std::list<std::list<std::function<bool()>>>::iterator it = q.begin();
    while (k--) {
        ++it;
    }
    q.insert(it, std::list<std::function<bool()>>());
}

void Animate::QueueOfScenes::run() {
    if (!q.empty()) {
        for (auto it = q.front().begin(); it != q.front().end(); ) {
            // std::cerr << q.size() << ' ' << q.front().size() << '\n';
            // std::cerr << &(*it) << '\n';
            ++it;
            if ((*prev(it))()) {
                q.front().erase(prev(it));
            }
        }
        if (q.front().empty()) {
            q.pop_front();
            currTime = 0;
        } else {
            currTime += elapseTime;
        }
    }
}
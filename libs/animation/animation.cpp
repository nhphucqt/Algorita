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

bool Animate::delay(double* currTime, bool* isReversed) {
    return *currTime + elapseTime >= DELAY_TIME;
}

Animate::QueueOfScenes::QueueOfScenes() {
    q = std::list<std::list<std::function<bool()>>>();
    resetCur();

    std::cerr << "QOS::() iter end -> " << (iter == q.end()) << '\n';

}

void Animate::QueueOfScenes::setReverse(bool _r) {
    isReversed = _r;
}

void Animate::QueueOfScenes::clearScenes() {
    q.clear();
    resetCur();
    std::cerr << "QOS::clearS() iter end -> " << (iter == q.end()) << '\n';
}

std::list<std::list<std::function<bool()>>>::iterator Animate::QueueOfScenes::curScene() const {
    if (!isReversed) {
        return prev(iter);
    }
    return iter;
}


void Animate::QueueOfScenes::resetCur() {
    isReversed = false;
    currTime = 0.0;
    iter = q.end();
    std::cerr << "QOS::resetCur() iter end -> " << (iter == q.end()) << '\n';
}

bool Animate::QueueOfScenes::isLeftEnd() const {
    std::cerr << "QOS::isLeftEnd()\n";
    return iter == q.begin();
}

bool Animate::QueueOfScenes::isRightEnd() const {
    std::cerr << "QOS::isRightEnd()\n";
    return iter == q.end();
}

bool Animate::QueueOfScenes::isEnd() const {
    std::cerr << "QOS::isEnd()\n";
    return isLeftEnd() || isRightEnd();
}

bool Animate::QueueOfScenes::canRun() const {
    std::cerr << "QOS::canRun()\n";
    return (!isReversed && !isLeftEnd()) || (isReversed && !isRightEnd());
}

bool Animate::QueueOfScenes::goTo() {
    std::cerr << "QOS::goTo()\n";
    assert(canRun());
    if (!isReversed) {
        return goNext();
    } else {
        return goPrev();
    }
}

bool Animate::QueueOfScenes::goNext() {
    std::cerr << "QOS::goNext()\n";
    assert(!isLeftEnd());
    return --iter == q.begin();
}

bool Animate::QueueOfScenes::goPrev() {
    std::cerr << "QOS::goPrev()\n";
    assert(!isRightEnd());
    return ++iter == q.end();
}

void Animate::QueueOfScenes::pushToBackScene(const std::function<bool()> &func) {
    q.front().push_back(func);
    std::cerr << "QOS::pushToBack() iter end -> " << (iter == q.end()) << '\n';
}

void Animate::QueueOfScenes::pushToNewScene(const std::function<bool()> &func) {
    addBlankScene();
    pushToBackScene(func);
    std::cerr << "QOS::pushToNew() iter end -> " << (iter == q.end()) << '\n';
}

void Animate::QueueOfScenes::addBlankScene() {
    q.push_front(std::list<std::function<bool()>>());
    std::cerr << "QOS::addBlank() iter end -> " << (iter == q.end()) << '\n';
}


bool Animate::QueueOfScenes::run() {
    // std::cerr << " before cSceme >> " << iter << '\n';

    std::cerr << "QOS::run() iter end -> " << (iter == q.end()) << '\n';

    std::cerr << " check can move\n";
    if (!canRun()) {
        return true;
    }
    std::cerr << " check is end\n";
    currTime += elapseTime;
    bool done = true;

    std::cerr << " iter == q.end() " << (iter == q.end()) << '\n';
    std::cerr << " curS == q.end() " << (curScene() == q.end()) << '\n';

    for (std::list<std::function<bool()>>::iterator curAnim = curScene()->begin(); curAnim != curScene()->end(); ++curAnim) {
        std::cerr << " enter loop\n";
        // std::cerr << " iter,i -> " << iter << ' ' << i << ' ' << q.size() << ' ' << q[iter].size() << '\n';
        done &= (*curAnim)();
    }
    std::cerr << " done\n";
    if (done) {
        goTo();
        currTime = 0.0;
    }
    // std::cerr << " after cSceme >> " << iter << '\n';
    return false;
}
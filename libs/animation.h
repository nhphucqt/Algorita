#ifndef ANIMATION_H
#define ANIMATION_H

#include <queue>
#include <vector>
#include <functional>

#include "nodelib.h"

// NOTE: Templated function cannot be seperated into multiple files

double bezier(double S, double T, double t);

template<typename T>
bool nodeFadeIn(T* pNode, double* elapseTime) {
    double inc = Animate::FADEIN_SPEED * *elapseTime;
    if ((pNode->transparent+=inc) >= pNode->trueColor.a) {
        pNode->currColor.a = pNode->trueColor.a;
        return true;
    } else {
        pNode->currColor.a = pNode->transparent;
        return false;
    }
}

template<typename T>
bool nodeFadeOut(T* pNode, double* elapseTime) {
    double dec = Animate::FADEOUT_SPEED * *elapseTime;
    if ((pNode->transparent-=dec) <= 0) {
        pNode->currColor.a = 0;
        return true;
    } else {
        pNode->currColor.a = pNode->transparent;
        return false;
    }
}

template<typename T>
bool nodeTransform(T* pNode, int Tx, int Ty, double* elapseTime, double* currTime, double transTime) {
    double Ux = Tx - pNode->lx;
    double Uy = Ty - pNode->ly;
    double leng = sqrt(Ux*Ux + Uy*Uy);
    double distance = bezier(leng, transTime, std::min(transTime, (*currTime) + (*elapseTime)));
    pNode->x = pNode->lx + Ux / leng * distance;
    pNode->y = pNode->ly + Uy / leng * distance;
    if ((*currTime) + (*elapseTime) >= transTime) {
        pNode->lx = pNode->x = Tx;
        pNode->ly = pNode->y = Ty;
        return true;
    } else {
        return false;
    }
}

void runScenes(std::queue<std::vector<std::function<bool()>>> &queueOfScenes, double* currTime, double* elapseTime);

#endif
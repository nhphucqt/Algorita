#ifndef ANIMATION_H
#define ANIMATION_H

#include <queue>
#include <vector>
#include <functional>

#include "GraphicNode.h"

// NOTE: Templated function cannot be seperated into multiple files

namespace Animate {
    double bezier(double S, double T, double t);

    template<typename T>
    bool fadeIn(T* obj, double* elapseTime, double *currTime, double fadeTime) {
        if (*currTime + *elapseTime >= fadeTime) {
            obj->transparent = 1;
            return true;
        } else {
            obj->transparent = (*currTime + *elapseTime) / fadeTime;
            return false;
        }
    }

    template<typename T>
    bool fadeOut(T* obj, double* elapseTime, double *currTime, double fadeTime) {
        if (*currTime + *elapseTime >= fadeTime) {
            obj->transparent = 0;
            return true;
        } else {
            obj->transparent = 1.0 - (*currTime + *elapseTime) / fadeTime;
            return false;
        }
    }

    template<typename T>
    bool transform(T* obj, int Tx, int Ty, double* elapseTime, double* currTime, double transTime) {
        double Ux = Tx - obj->lx;
        double Uy = Ty - obj->ly;
        double leng = sqrt(Ux*Ux + Uy*Uy);
        double distance = bezier(leng, transTime, std::min(transTime, (*currTime) + (*elapseTime)));
        obj->x = obj->lx + Ux / leng * distance;
        obj->y = obj->ly + Uy / leng * distance;
        if ((*currTime) + (*elapseTime) >= transTime) {
            obj->lx = obj->x = Tx;
            obj->ly = obj->y = Ty;
            return true;
        } else {
            return false;
        }
    }

    void runScenes(std::queue<std::vector<std::function<bool()>>> &queueOfScenes, double* currTime, double* elapseTime);
}


#endif
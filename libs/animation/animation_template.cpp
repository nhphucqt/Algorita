#ifndef ANIMATION_TEMPLATE_CPP
#define ANIMATION_TEMPLATE_CPP

#include "animation.h"

// DO NOT USE DIRECTLY
template<typename T> 
bool Animate::fadeIn(T* obj, double* currTime, bool* isReversed) {
    // std::cerr << "Animate::fadein -> " << *currTime << ' ' << *isReversed << '\n';
    if (*isReversed && *currTime <= 0) {
        return obj->vanish(), true;
    }
    if (!*isReversed && *currTime >= FADEIN_TIME) {
        return obj->appear(), true;
    }
    // *currTime = std::max(0.0, std::min((double)FADEIN_TIME, *currTime));
    // std::cerr << "Animate::fadein() -> currTime = " << *currTime << '\n';
    obj->transparent = *currTime / FADEIN_TIME;
    return false;
}

// DO NOT USE DIRECTLY
template<typename T>
bool Animate::fadeOut(T* obj, double *currTime, bool* isReversed) {
    if (*isReversed && (*currTime <= 0)) {
        return obj->appear(), true;
    }
    if (!*isReversed && (*currTime >= FADEOUT_TIME)) {
        return obj->vanish(), true;
    }
    // *currTime = std::max(0.0, std::min((double)FADEOUT_TIME, *currTime));
    obj->transparent = 1.0 - (*currTime) / FADEOUT_TIME;
    return false;
}

// DO NOT USE DIRECTLY
template<typename T>
bool Animate::displace(T* obj, int Sx, int Sy, int Dx, int Dy, double* currTime, bool* isReversed) {
    // std::cerr << "obj->x,y " << obj->lx << ' ' << obj->ly << ' ' << obj->x << ' ' << obj->y << ' ' << *currTime << ' ' << *isReversed << '\n';
    if (*isReversed && (*currTime <= 0)) {
        obj->x = Sx;
        obj->y = Sy;
        return true;
    }
    if (!*isReversed && (*currTime >= TRANS_TIME)) {
        obj->x = Dx;
        obj->y = Dy;
        return true;
    }
    double Ux = Dx - Sx;
    double Uy = Dy - Sy;
    // std::cerr << "Ux,Uy " << Ux << ' ' << Uy << '\n';
    double leng = sqrt(Ux*Ux + Uy*Uy);
    // std::cerr << "leng " << leng << '\n';
    double distance = bezier(leng, TRANS_TIME, std::min((double)TRANS_TIME, *currTime));
    // std::cerr << "distance " << distance << '\n';
    obj->x = Sx + Ux / leng * distance;
    obj->y = Sy + Uy / leng * distance;
    // std::cerr << "new obj->x,y " << obj->x << ' ' << obj->y << '\n';
    return false;
}

// DO NOT USE DIRECTLY
template<typename T>
bool Animate::transform(T* obj, int Sx, int Sy, int Tx, int Ty, double* currTime, bool* isReversed) {
    return displace(obj, Sx, Sy, Sx + Tx, Sy + Ty, currTime, isReversed);
}

// DO NOT USE DIRECTLY
template<typename T>
bool Animate::slideIn(T* obj, double* currTime, bool* isReversed) {
    if (*isReversed && (*currTime <= 0)) {
        return obj->percent = 0.0, true;
    }
    if (!*isReversed && (*currTime >= SLIDE_TIME)) {
        return obj->percent = 1.0, true;
    }
    obj->percent = (*currTime) / SLIDE_TIME;
    return false;
}

// DO NOT USE DIRECTLY
template<typename T>
bool Animate::slideOut(T* obj, double* currTime, bool* isReversed) {
    if (*isReversed && (*currTime <= 0)) {
        return obj->percent = 1.0, true;
    }
    if (!*isReversed && (*currTime >= SLIDE_TIME)) {
        return obj->percent = 0.0, true;
    }
    obj->percent = 1.0 - (*currTime) / SLIDE_TIME;
    return false;
}

// DO NOT USE DIRECTLY
template<typename T>
bool Animate::slideColorIn(T* obj, double* currTime, bool* isReversed) {
    if (*isReversed && (*currTime <= 0)) {
        return obj->slidePercent = 0.0, true;
    }
    if (!*isReversed && (*currTime >= SLIDE_TIME)) {
        return obj->slidePercent = 1.0, true;
    }
    obj->slidePercent = (*currTime) / SLIDE_TIME;
    return false;
}

// DO NOT USE DIRECTLY
template<typename T>
bool Animate::slideColorOut(T* obj, double* currTime, bool* isReversed) {
    if (*isReversed && (*currTime <= 0)) {
        return obj->slidePercent = 1.0, true;
    }
    if (!*isReversed && (*currTime >= SLIDE_TIME)) {
        return obj->slidePercent = 0.0, true;
    }
    obj->slidePercent = 1.0 - (*currTime) / SLIDE_TIME;
    return false;
}

template<typename T> 
bool Animate::transText(T* obj, const std::string &src, const std::string &snk, double* currTime, bool* isReversed) {
    if (*isReversed) {
        obj->assign(src);
    } else {
        obj->assign(snk);
    }
    return true;
}


// DO NOT USE DIRECTLY
template<typename T>
bool Animate::redirect(T* A, T* C, double* currTime, bool* isReversed) {
    assert(A->pNext != nullptr);

    Vector2 cA = A->aNext.pA + toSqrVector2(*A->aNext.sA / 2);
    Vector2 cB = A->aNext.pB + toSqrVector2(*A->aNext.sB / 2);
    Vector2 cC = toVector2(C->x, C->y) + toSqrVector2(C->size / 2);

    Vector2 AB = cB - cA;
    Vector2 BA = cA - cB;
    Vector2 CA = cA - cC;
    Vector2 AC = cC - cA;

    Vector2 newB = cB + A->aNext.ftB(BA);
    Vector2 newC = cC + C->outerShapeIn(CA);

    Vector2 BC = newC - newB;

    if (*isReversed && *currTime <= 0.0) {
        A->aNext.transA = A->outerShapeOut(AC) - A->outerShapeOut(AB);
        A->aNext.transB = BC;
        return true;
    }

    if (!*isReversed && *currTime >= TRAVEL_TIME) {
        A->aNext.transA = Z_VECT;
        A->aNext.transB = Z_VECT;
        return true;
    }
    A->aNext.transB = BC * (1.0 - ((*currTime) / TRAVEL_TIME));
    A->aNext.transA = A->outerShapeOut(newB + A->aNext.transB - cA) - A->outerShapeOut(AB);

    return false;
}

#endif
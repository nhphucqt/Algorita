#ifndef ANIMATION_TEMPLATE_CPP
#define ANIMATION_TEMPLATE_CPP

#include "animation.h"

template<typename T>
bool Animate::assignValue(T* obj, int oldVal, int newVal, double* currTime, bool* isReversed) {
    obj->setValue(*isReversed ? oldVal : newVal);
    return (*isReversed && *currTime <= 0) || (!*isReversed && *currTime >= Animate::ASSIGN_TIME);
}


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
    obj->transparent = bezier(*currTime / FADEIN_TIME);
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
    obj->transparent = bezier(1.0 - (*currTime) / FADEOUT_TIME);
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
    double distance = leng * bezier(std::min((double)TRANS_TIME, *currTime) / TRANS_TIME);
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
    obj->percent = bezier((*currTime) / SLIDE_TIME);
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
    obj->percent = bezier(1.0 - (*currTime) / SLIDE_TIME);
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
    obj->slidePercent = bezier((*currTime) / SLIDE_TIME);
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
    obj->slidePercent = bezier(1.0 - (*currTime) / SLIDE_TIME);
    return false;
}

template<typename T> 
bool Animate::transText(T* obj, const std::string &src, const std::string &snk, double* currTime, bool* isReversed) {
    if (*isReversed) {
        obj->assign(src);
    } else {
        obj->assign(snk);
    }
    return (*isReversed && *currTime <= 0) || (!*isReversed && *currTime >= TRANS_TIME);
}


// DO NOT USE DIRECTLY
template<typename T, typename MT>
bool Animate::redirectHead(T* A, MT* arrow, T* C, double* currTime, bool* isReversed) {
    Vector2 cA = arrow->pA + toSqrVector2(*arrow->sA / 2);
    Vector2 cB = arrow->pB + toSqrVector2(*arrow->sB / 2);
    Vector2 cC = toVector2(C->x, C->y) + toSqrVector2(C->size / 2);

    Vector2 AB = cB - cA;
    Vector2 BA = cA - cB;
    Vector2 AC = cC - cA;
    Vector2 CA = cA - cC;
    Vector2 BC = cC - cB;


    if (*isReversed && *currTime <= 0.0) {
        arrow->transA = arrow->ftA(AC) - arrow->ftA(AB);
        arrow->transB = BC + C->outerShapeIn(CA) - arrow->ftB(BA);
        return true;
    }

    if (!*isReversed && *currTime >= TRAVEL_TIME) {
        arrow->transA = Z_VECT;
        arrow->transB = Z_VECT;
        return true;
    }

    Vector2 pBC = BC * bezier(1.0 - ((*currTime) / TRAVEL_TIME));
    Vector2 nB = cB + pBC;

    arrow->transA = arrow->ftA(nB - cA) - arrow->ftA(AB);
    arrow->transB = pBC + arrow->ftB(cA - nB) - arrow->ftB(BA);

    return false;
}

template<typename T, typename MT> 
bool Animate::redirectTail(T* A, MT* arrow, T* C, double* currTime, bool* isReversed) {
    Vector2 cA = arrow->pA + toSqrVector2(*arrow->sA / 2);
    Vector2 cB = arrow->pB + toSqrVector2(*arrow->sB / 2);
    Vector2 cC = toVector2(C->x, C->y) + toSqrVector2(C->size / 2);

    Vector2 AB = cB - cA;
    Vector2 BA = cA - cB;
    Vector2 BC = cC - cB;
    Vector2 CB = cB - cC;
    Vector2 AC = cC - cA;

    if (*isReversed && *currTime <= 0.0) {
        arrow->transA = AC + C->outerShapeOut(CB) - arrow->ftA(AB);
        arrow->transB = arrow->ftB(BC) - arrow->ftB(BA);
        return true;
    }

    if (!*isReversed && *currTime >= TRAVEL_TIME) {
        arrow->transA = Z_VECT;
        arrow->transB = Z_VECT;
        return true;
    }
    
    Vector2 pAC = AC * bezier(1.0 - ((*currTime) / TRAVEL_TIME));
    Vector2 nA = cA + pAC;

    arrow->transA = pAC - arrow->ftA(AB) + arrow->ftA(cB - nA);
    arrow->transB = arrow->ftB(nA - cB) - arrow->ftB(BA);

    return false;
}

#endif
#ifndef ANIMATION_TEMPLATE_CPP
#define ANIMATION_TEMPLATE_CPP

#include "animation.h"

// DO NOT USE DIRECTLY
template<typename T> 
bool Animate::fadeIn(T* obj, double* currTime, bool* isReversed) {
    std::cerr << "Animate::fadein -> " << *currTime << ' ' << *isReversed << '\n';
    if (*isReversed && *currTime <= 0) {
        return obj->vanish(), true;
    }
    if (!*isReversed && *currTime >= FADEIN_TIME) {
        return obj->appear(), true;
    }
    *currTime = std::max(0.0, std::min((double)FADEIN_TIME, *currTime));
    std::cerr << "Animate::fadein() -> currTime = " << *currTime << '\n';
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
    *currTime = std::max(0.0, std::min((double)FADEOUT_TIME, *currTime));
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

template<typename T>
bool Animate::focus(T* obj, double* currTime, bool* isReversed) {
    if (*isReversed && (*currTime <= 0)) {
        return obj->unfocus(), true;
    }
    if (!*isReversed && (*currTime >= FOCUS_TIME)) {
        return obj->focus(), true;
    }
    obj->focusPercent = (*currTime) / FOCUS_TIME;
    return false;
}

template<typename T>
bool Animate::unfocus(T* obj, double* currTime, bool* isReversed) {
    if (*isReversed && (*currTime <= 0)) {
        return obj->focus(), true;
    }
    if (!*isReversed && (*currTime >= UNFOCUS_TIME)) {
        return obj->unfocus(), true;
    }
    obj->focusPercent = 1.0 - (*currTime) / UNFOCUS_TIME;
    return false;
}

template<typename T> 
bool Animate::focusBorder(T* obj, double* currTime, bool* isReversed) {
    if (*isReversed && (*currTime <= 0)) {
        return obj->unfocusBorder(), true;
    }
    if (!*isReversed && (*currTime >= FOCUS_TIME)) {
        return obj->focusBorder(), true;
    }
    obj->focusBorderPercent = (*currTime) / FOCUS_TIME;
    return false;
}

template<typename T> 
bool Animate::unfocusBorder(T* obj, double* currTime, bool* isReversed) {
    if (*isReversed && (*currTime <= 0)) {
        return obj->focusBorder(), true;
    }
    if (!*isReversed && (*currTime >= UNFOCUS_TIME)) {
        return obj->unfocusBorder(), true;
    }
    obj->focusBorderPercent = 1.0 - (*currTime) / UNFOCUS_TIME;
    return false;
}

template<typename T>
bool Animate::fadeInKthNode(T* obj, int k, double *currTime, bool* isReversed) {
    return fadeIn(obj->KthNode(k), currTime, isReversed);
}

template<typename T>
bool Animate::fadeOutKthNode(T* obj, int k, double *currTime, bool* isReversed) {
    return fadeOut(obj->KthNode(k), currTime, isReversed);
}

template<typename T> 
bool Animate::fadeInKthArrow(T* obj, int k, double *currTime, bool* isReversed) {
    return fadeIn(&obj->KthNode(k)->aNext, currTime, isReversed);
}

template<typename T> 
bool Animate::fadeOutKthArrow(T* obj, int k, double *currTime, bool* isReversed) {
    return fadeOut(&obj->KthNode(k)->aNext, currTime, isReversed);
}

template<typename T> 
bool Animate::focusKthNode(T* obj, int k, double *currTime, bool* isReversed) {
    return focus(obj->KthNode(k), currTime, isReversed);
}

template<typename T> 
bool Animate::unfocusKthNode(T* obj, int k, double *currTime, bool* isReversed) {
    return unfocus(obj->KthNode(k), currTime, isReversed);
}

template<typename T> 
bool Animate::focusKthNodeBorder(T* obj, int k, double *currTime, bool* isReversed) {
    return focusBorder(obj->KthNode(k), currTime, isReversed);
}

template<typename T> 
bool Animate::unfocusKthNodeBorder(T* obj, int k, double *currTime, bool* isReversed) {
    return unfocusBorder(obj->KthNode(k), currTime, isReversed);
}

template<typename T> 
bool Animate::focusKthArrow(T* obj, int k, double *currTime, bool* isReversed) {
    return focus(&obj->KthNode(k)->aNext, currTime, isReversed);
}

template<typename T> 
bool Animate::unfocusKthArrow(T* obj, int k, double *currTime, bool* isReversed) {
    return unfocus(&obj->KthNode(k)->aNext, currTime, isReversed);
}

template<typename T> 
bool Animate::displaceKthNode(T* obj, int k, int Sx, int Sy, int Dx, int Dy, double *currTime, bool* isReversed) {
    return displace(obj->KthNode(k), Sx, Sy, Dx, Dy, currTime, isReversed);
}

template<typename T> 
bool Animate::transformKthNode(T* obj, int k, int Sx, int Sy, int Tx, int Ty, double *currTime, bool* isReversed) {
    return transform(obj->KthNode(k), Sx, Sy, Tx, Ty, currTime, isReversed);
}

template<typename T> 
bool Animate::slideInKthArrow(T* obj, int k, double *currTime, bool* isReversed) {
    return slideIn(&obj->KthNode(k)->aNext, currTime, isReversed);
}

template<typename T> 
bool Animate::slideOutKthArrow(T* obj, int k, double *currTime, bool* isReversed) {
    return slideOut(&obj->KthNode(k)->aNext, currTime, isReversed);
}

template<typename OT, typename MT>
bool Animate::unfocusAllNodes(OT* obj, double* currTime, bool* isReversed) {
    // std::cerr << " start unfocusAllNodes\n";
    bool done = true;
    for (MT* curr = obj->pHead; curr != nullptr; curr = curr->pNext) {
        // std::cerr << curr << ' ' << curr->isFocus << '\n';
        if ((*isReversed && curr->isFocus) || (!*isReversed && !curr->isFocus)) {
            done &= unfocus(curr, currTime, isReversed);
        }
        // std::cerr << curr << ' ' << curr->isFocusBorder << '\n';
        if ((*isReversed && curr->isFocusBorder) || (!*isReversed && !curr->isFocusBorder)) {
            done &= unfocusBorder(curr, currTime, isReversed);
        }
        // std::cerr << curr << ' ' << curr->aNext.isFocus << '\n';
        if ((*isReversed && curr->aNext.isFocus) || (!*isReversed && !curr->aNext.isFocus)) {
            done &= unfocus(&curr->aNext, currTime, isReversed);
        }
    }
    // std::cerr << " done unfocusAllNodes " << done << '\n';
    return done;
}

template<typename OT, typename MT> 
bool Animate::fadeInAllNodes(OT* obj, double* currTime, bool* isReversed) {
    std::cerr << "Animate::fadeInAllNodes " << *currTime << ' ' << *isReversed << '\n';
    bool done = true;
    for (MT* curr = obj->pHead; curr != nullptr; curr = curr->pNext) {
        std::cerr << " run loop " << curr << '\n';
        if ((*isReversed && curr->isAppear) || (!*isReversed && !curr->isAppear)) {
            done &= fadeIn(curr, currTime, isReversed);
        }
        if ((*isReversed && curr->aNext.isAppear) || (!*isReversed && !curr->aNext.isAppear)) {
            done &= fadeIn(&curr->aNext, currTime, isReversed);
        }
    }
    std::cerr << " >> done = " << done << '\n';
    return done;
}

template<typename OT, typename MT> 
bool Animate::fadeOutAllNodes(OT* obj, double* currTime, bool* isReversed) {
    bool done = true;
    for (MT* curr = obj->pHead; curr != nullptr; curr = curr->pNext) {
        if ((*isReversed && !curr->isAppear) || (!*isReversed && curr->isAppear)) {
            done &= fadeOut(curr, currTime, isReversed);
        }
        if ((*isReversed && !curr->aNext.isAppear) || (!*isReversed && curr->aNext.isAppear)) {
            done &= fadeOut(&curr->aNext, currTime, isReversed);
        }
    }
    return done;
}

#endif
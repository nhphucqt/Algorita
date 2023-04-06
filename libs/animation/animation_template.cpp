#ifndef ANIMATION_TEMPLATE_CPP
#define ANIMATION_TEMPLATE_CPP

#include "animation.h"

// DO NOT USE DIRECTLY
template<typename T> 
bool Animate::fadeIn(T* obj, double* currTime, bool* isReversed) {
    if (*currTime >= FADEIN_TIME) {
        obj->appear();
        return true;
    } else {
        obj->transparent = *currTime / FADEIN_TIME;
        return false;
    }
}

// DO NOT USE DIRECTLY
template<typename T>
bool Animate::fadeOut(T* obj, double *currTime, bool* isReversed) {
    if (*currTime >= FADEOUT_TIME) {
        obj->vanish();
        return true;
    } else {
        obj->transparent = 1.0 - (*currTime) / FADEOUT_TIME;
        return false;
    }
}

// DO NOT USE DIRECTLY
template<typename T>
bool Animate::displace(T* obj, int Dx, int Dy, double* currTime, bool* isReversed) {
    std::cerr << "obj->x,y " << obj->lx << ' ' << obj->ly << ' ' << obj->x << ' ' << obj->y << ' ' << *currTime << ' ' << *isReversed << '\n';
    if (*currTime >= TRANS_TIME) {
        obj->lx = obj->x = Dx;
        obj->ly = obj->y = Dy;
        return true;
    } else {
        double Ux = Dx - obj->lx;
        double Uy = Dy - obj->ly;
        std::cerr << "Ux,Uy " << Ux << ' ' << Uy << '\n';
        double leng = sqrt(Ux*Ux + Uy*Uy);
        std::cerr << "leng " << leng << '\n';
        double distance = bezier(leng, TRANS_TIME, std::min((double)TRANS_TIME, *currTime));
        std::cerr << "distance " << distance << '\n';
        obj->x = obj->lx + Ux / leng * distance;
        obj->y = obj->ly + Uy / leng * distance;
        std::cerr << "new obj->x,y " << obj->x << ' ' << obj->y << '\n';
        return false;
    }
}

// DO NOT USE DIRECTLY
template<typename T>
bool Animate::transform(T* obj, int Tx, int Ty, double* currTime, bool* isReversed) {
    return displace(obj, obj->lx + Tx, obj->ly + Ty, currTime, isReversed);
}

// DO NOT USE DIRECTLY
template<typename T>
bool Animate::slideIn(T* obj, double* currTime, bool* isReversed) {
    if (*currTime >= SLIDE_TIME) {
        obj->percent = 1;
        return true;
    } else {
        obj->percent = (*currTime) / SLIDE_TIME;
        return false;
    }
}

// DO NOT USE DIRECTLY
template<typename T>
bool Animate::slideOut(T* obj, double* currTime, bool* isReversed) {
    if (*currTime >= SLIDE_TIME) {
        obj->percent = 0;
        return true;
    } else {
        obj->percent = 1.0 - (*currTime) / SLIDE_TIME;
        return false;
    }
}

// DO NOT USE DIRECTLY
template<typename T>
bool Animate::redirect(T* A, T* C, double* currTime, bool* isReversed) {
    assert(A->pNext != nullptr);
    if (*currTime >= TRAVEL_TIME) {
        float _transparent = A->aNext.transparent;
        float _percent = A->aNext.percent;
        A->updateNext(C);
        A->aNext.setTransparent(_transparent);
        A->aNext.setPercent(_percent);
        return true;
    }
    Vector2 cA = A->aNext.pA + toVector2(*A->aNext.sA / 2, *A->aNext.sA / 2);
    Vector2 cB = A->aNext.pB + toVector2(*A->aNext.sB / 2, *A->aNext.sB / 2);
    Vector2 cC = toVector2(C->x, C->y) + toVector2(C->size / 2, C->size / 2);

    if (dist(cA, cB) <= *A->aNext.sA / 2 + *A->aNext.sB / 2) {
        return false;
    }

    Vector2 AB = cB - cA;
    Vector2 BA = cA - cB;
    Vector2 CA = cA - cC;

    Vector2 newB = cB + A->aNext.ftB(BA);
    Vector2 newC = cC + C->outerShapeIn(CA);

    // newB -> newC
    Vector2 BC = newC - newB;

    A->aNext.transB = BC * ((*currTime) / TRAVEL_TIME);

    // newB + A->aNext.transB
    A->aNext.transA = A->outerShapeOut(newB + A->aNext.transB - cA) - A->outerShapeOut(AB);

    return false;
}

template<typename T>
bool Animate::focus(T* obj, double* currTime, bool* isReversed) {
    if (*currTime >= FOCUS_TIME) {
        obj->focus();
        return true;
    }
    obj->focusPercent = (*currTime) / FOCUS_TIME;
    return false;
}

template<typename T>
bool Animate::unfocus(T* obj, double* currTime, bool* isReversed) {
    if (*currTime >= UNFOCUS_TIME) {
        obj->unfocus();
        return true;
    }
    obj->focusPercent = 1.0 - (*currTime) / UNFOCUS_TIME;
    return false;
}

template<typename T> 
bool Animate::focusBorder(T* obj, double* currTime, bool* isReversed) {
    if (*currTime >= FOCUS_TIME) {
        obj->focusBorder();
        return true;
    }
    obj->focusBorderPercent = (*currTime) / FOCUS_TIME;
    return false;
}

template<typename T> 
bool Animate::unfocusBorder(T* obj, double* currTime, bool* isReversed) {
    if (*currTime >= UNFOCUS_TIME) {
        obj->unfocusBorder();
        return true;
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
bool Animate::displaceKthNode(T* obj, int k, int Dx, int Dy, double *currTime, bool* isReversed) {
    return displace(obj->KthNode(k), Dx, Dy, currTime, isReversed);
}

template<typename T> 
bool Animate::transformKthNode(T* obj, int k, int Tx, int Ty, double *currTime, bool* isReversed) {
    return transform(obj->KthNode(k), Tx, Ty, currTime, isReversed);
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
    std::cerr << " start unfocusAllNodes\n";
    bool done = true;
    for (MT* curr = obj->pHead; curr != nullptr; curr = curr->pNext) {
        std::cerr << curr << ' ' << curr->isFocus << '\n';
        if (curr->isFocus) {
            done &= unfocus(curr, currTime, isReversed);
        }
        std::cerr << curr << ' ' << curr->isFocusBorder << '\n';
        if (curr->isFocusBorder) {
            done &= unfocusBorder(curr, currTime, isReversed);
        }
        std::cerr << curr << ' ' << curr->aNext.isFocus << '\n';
        if (curr->aNext.isFocus) {
            done &= unfocus(&curr->aNext, currTime, isReversed);
        }
    }
    std::cerr << " done unfocusAllNodes " << done << '\n';
    return done;
}

template<typename OT, typename MT> 
bool Animate::fadeInAllNodes(OT* obj, double* currTime, bool* isReversed) {
    bool done = true;
    for (MT* curr = obj->pHead; curr != nullptr; curr = curr->pNext) {
        if (!curr->isAppear) {
            done &= fadeIn(curr, currTime, isReversed);
        }
        if (!curr->aNext.isAppear) {
            done &= fadeIn(&curr->aNext, currTime, isReversed);
        }
    }
    return done;
}

template<typename OT, typename MT> 
bool Animate::fadeOutAllNodes(OT* obj, double* currTime, bool* isReversed) {
    bool done = true;
    for (MT* curr = obj->pHead; curr != nullptr; curr = curr->pNext) {
        if (curr->isAppear) {
            done &= fadeOut(curr, currTime, isReversed);
        }
        if (curr->aNext.isAppear) {
            done &= fadeOut(&curr->aNext, currTime, isReversed);
        }
    }
    return done;
}

template<typename OT, typename MT> 
bool Animate::transformAllNodesFrom(OT* obj, int k, int Tx, int Ty, double* currTime, bool* isReversed) {
    bool done = true;
    for (MT* curr = obj->KthNode(k); curr != nullptr; curr = curr->pNext) {
        done &= transform(curr, Tx, Ty, currTime, isReversed);
    }
    return done;
}

#endif
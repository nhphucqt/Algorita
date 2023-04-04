#ifndef ANIMATION_TEMPLATE_CPP
#define ANIMATION_TEMPLATE_CPP

#include "animation.h"

// DO NOT USE DIRECTLY
template<typename T> 
bool Animate::fadeIn(T* obj, double* currTime, double fadeTime) {
    if (*currTime + elapseTime >= fadeTime) {
        obj->transparent = 1;
        return true;
    } else {
        obj->transparent = (*currTime + elapseTime) / fadeTime;
        return false;
    }
}

// DO NOT USE DIRECTLY
template<typename T>
bool Animate::fadeOut(T* obj, double *currTime, double fadeTime) {
    if (*currTime + elapseTime >= fadeTime) {
        obj->transparent = 0;
        return true;
    } else {
        obj->transparent = 1.0 - (*currTime + elapseTime) / fadeTime;
        return false;
    }
}

// DO NOT USE DIRECTLY
template<typename T>
bool Animate::displace(T* obj, int Dx, int Dy, double* currTime, double transTime) {
    double Ux = Dx - obj->lx;
    double Uy = Dy - obj->ly;
    double leng = sqrt(Ux*Ux + Uy*Uy);
    double distance = bezier(leng, transTime, std::min(transTime, (*currTime) + (elapseTime)));
    obj->x = obj->lx + Ux / leng * distance;
    obj->y = obj->ly + Uy / leng * distance;
    if ((*currTime) + elapseTime >= transTime) {
        obj->lx = obj->x = Dx;
        obj->ly = obj->y = Dy;
        return true;
    } else {
        return false;
    }
}

// DO NOT USE DIRECTLY
template<typename T>
bool Animate::transform(T* obj, int Tx, int Ty, double* currTime, double transTime) {
    return displace(obj, obj->lx + Tx, obj->ly + Ty, currTime, transTime);
}

// DO NOT USE DIRECTLY
template<typename T>
bool Animate::slideIn(T* obj, double* currTime, double slideTime) {
    if (*currTime + elapseTime >= slideTime) {
        obj->percent = 1;
        return true;
    } else {
        obj->percent = (*currTime + elapseTime) / slideTime;
        return false;
    }
}

// DO NOT USE DIRECTLY
template<typename T>
bool Animate::slideOut(T* obj, double* currTime, double slideTime) {
    if (*currTime + elapseTime >= slideTime) {
        obj->percent = 0;
        return true;
    } else {
        obj->percent = 1.0 - (*currTime + elapseTime) / slideTime;
        return false;
    }
}

// DO NOT USE DIRECTLY
template<typename T>
bool Animate::redirect(T* A, T* C, double* currTime, double travelTime) {
    assert(A->pNext != nullptr);
    if (*currTime + elapseTime >= travelTime) {
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

    A->aNext.transB = BC * (*currTime / travelTime);

    // newB + A->aNext.transB
    A->aNext.transA = A->outerShapeOut(newB + A->aNext.transB - cA) - A->outerShapeOut(AB);

    return false;
}

template<typename T>
bool Animate::focus(T* obj, double* currTime, double focusTime) {
    if (*currTime + elapseTime >= focusTime) {
        obj->focus();
        return true;
    }
    obj->focusPercent = (*currTime + elapseTime) / focusTime;
    return false;
}

template<typename T>
bool Animate::unfocus(T* obj, double* currTime, double unfocusTime) {
    if (*currTime + elapseTime >= unfocusTime) {
        obj->unfocus();
        return true;
    }
    obj->focusPercent = 1.0 - (*currTime + elapseTime) / unfocusTime;
    return false;
}

template<typename T> 
bool Animate::focusBorder(T* obj, double* currTime, double focusTime) {
    if (*currTime + elapseTime >= focusTime) {
        obj->focusBorder();
        return true;
    }
    obj->focusBorderPercent = (*currTime + elapseTime) / focusTime;
    return false;
}

template<typename T> 
bool Animate::unfocusBorder(T* obj, double* currTime, double unfocusTime) {
    if (*currTime + elapseTime >= unfocusTime) {
        obj->unfocusBorder();
        return true;
    }
    obj->focusBorderPercent = 1.0 - (*currTime + elapseTime) / unfocusTime;
    return false;
}

template<typename T>
bool Animate::fadeInKthNode(T* obj, int k, double *currTime, double fadeTime) {
    return fadeIn(obj->KthNode(k), currTime, fadeTime);
}

template<typename T>
bool Animate::fadeOutKthNode(T* obj, int k, double *currTime, double fadeTime) {
    return fadeOut(obj->KthNode(k), currTime, fadeTime);
}

template<typename T> 
bool Animate::focusKthNode(T* obj, int k, double *currTime, double focusTime) {
    return focus(obj->KthNode(k), currTime, focusTime);
}

template<typename T> 
bool Animate::unfocusKthNode(T* obj, int k, double *currTime, double unfocusTime) {
    return unfocus(obj->KthNode(k), currTime, unfocusTime);
}

template<typename T> 
bool Animate::focusKthNodeBorder(T* obj, int k, double *currTime, double focusTime) {
    return focusBorder(obj->KthNode(k), currTime, focusTime);
}

template<typename T> 
bool Animate::unfocusKthNodeBorder(T* obj, int k, double *currTime, double unfocusTime) {
    return unfocusBorder(obj->KthNode(k), currTime, unfocusTime);
}

template<typename T> 
bool Animate::focusKthArrow(T* obj, int k, double *currTime, double focusTime) {
    return focus(&obj->KthNode(k)->aNext, currTime, focusTime);
}

template<typename T> 
bool Animate::unfocusKthArrow(T* obj, int k, double *currTime, double unfocusTime) {
    return unfocus(&obj->KthNode(k)->aNext, currTime, unfocusTime);
}

template<typename OT, typename MT>
bool Animate::unfocusAllNodes(OT* obj, double* currTime, double unfocusTime) {
    bool done = true;
    for (MT* curr = obj->pHead; curr != nullptr; curr = curr->pNext) {
        if (curr->isFocus) {
            done &= unfocus(curr, currTime, unfocusTime);
        }
        if (curr->isFocusBorder) {
            done &= unfocusBorder(curr, currTime, unfocusTime);
        }
        if (curr->aNext.isFocus) {
            done &= unfocus(&curr->aNext, currTime, unfocusTime);
        }
    }
    return done;
}


// Push To Front Scene
template<typename T>
void Animate::QueueOfScenes::pushFadeInToFrontScene(T* obj, double fadeTime) {
    pushToFrontScene(
        std::bind(&fadeIn<T>, obj, &currTime, fadeTime)
    );
}

template<typename T>
void Animate::QueueOfScenes::pushFadeOutToFrontScene(T* obj, double fadeTime) {
    pushToFrontScene(
        std::bind(&fadeOut<T>, obj, &currTime, fadeTime)
    );
}

template<typename T>
void Animate::QueueOfScenes::pushDisplaceToFrontScene(T* obj, int Dx, int Dy, double transTime) {
    pushToFrontScene(std::bind(&displace<T>, obj, Dx, Dy, &currTime, transTime));
}

template<typename T>
void Animate::QueueOfScenes::pushTransformToFrontScene(T* obj, int Tx, int Ty, double transTime) {
    pushToFrontScene(std::bind(&transform<T>, obj, Tx, Ty, &currTime, transTime));
}

// Push To Back Scene
template<typename T>
void Animate::QueueOfScenes::pushFadeInToBackScene(T* obj, double fadeTime) {
    pushToBackScene(std::bind(&fadeIn<T>, obj, &currTime, fadeTime));
}

template<typename T>
void Animate::QueueOfScenes::pushFadeOutToBackScene(T* obj, double fadeTime) {
    pushToBackScene(std::bind(&fadeOut<T>, obj, &currTime, fadeTime));
}

template<typename T>
void Animate::QueueOfScenes::pushDisplaceToBackScene(T* obj, int Dx, int Dy, double transTime) {
    pushToBackScene(std::bind(&displace<T>, obj, Dx, Dy, &currTime, transTime));
}

template<typename T>
void Animate::QueueOfScenes::pushFocusToBackScene(T* obj, double focusTime) {
    pushToBackScene(std::bind(&focus<T>, obj, &currTime, focusTime));
}

template<typename T>
void Animate::QueueOfScenes::pushUnfocusToBackScene(T* obj, double unfocusTime) {
    pushToBackScene(std::bind(&unfocus<T>, obj, &currTime, unfocusTime));
}

// Push To Kth Scene
template<typename T>
void Animate::QueueOfScenes::pushFadeInToKthScene(int k, T* obj, double fadeTime) {
    pushToKthScene(k, std::bind(&fadeIn<T>, obj, &currTime, fadeTime));
}


template<typename T>
void Animate::QueueOfScenes::pushFadeOutToKthScene(int k, T* obj, double fadeTime) {
    pushToKthScene(k, std::bind(&fadeOut<T>, obj, &currTime, fadeTime));
}

template<typename T>
void Animate::QueueOfScenes::pushTransformToKthScene(int k, T* obj, int Tx, int Ty, double transTime) {
    pushToKthScene(k, std::bind(&transform<T>, obj, Tx, Ty, &currTime, transTime));
}

template<typename T>
void Animate::QueueOfScenes::pushDisplaceToKthScene(int k, T* obj, int Tx, int Ty, double transTime) {
    pushToKthScene(k, std::bind(&displace<T>, obj, Tx, Ty, &currTime, transTime));
}

template<typename T>
void Animate::QueueOfScenes::pushSlideInToKthScene(int k, T* obj, double slideTime) {
    pushToKthScene(k, std::bind(&slideIn<T>, obj, &currTime, slideTime));
}

template<typename T>
void Animate::QueueOfScenes::pushSlideOutToKthScene(int k, T* obj, double slideTime) {
    pushToKthScene(k, std::bind(&slideOut<T>, obj, &currTime, slideTime));
}

template<typename T>
void Animate::QueueOfScenes::pushRedirectToKthScene(int k, T* A, T* C, double travelTime) {
    pushToKthScene(k, std::bind(&redirect<T>, A, C, &currTime, travelTime));
}

template<typename T>
void Animate::QueueOfScenes::pushFocusToKthScene(int k, T* obj, double unfocusTime) {
    pushToKthScene(k, std::bind(&focus<T>, obj, &currTime, unfocusTime));
}

template<typename T>
void Animate::QueueOfScenes::pushUnfocusToKthScene(int k, T* obj, double unfocusTime) {
    pushToKthScene(k, std::bind(&unfocus<T>, obj, &currTime, unfocusTime));
}

// Push To New Scene
template<typename T>
void Animate::QueueOfScenes::pushFadeInToNewScene(T* obj, double fadeTime) {
    addBlankScene();
    pushFadeInToBackScene(obj, fadeTime);
}

template<typename T>
void Animate::QueueOfScenes::pushFadeOutToNewScene(T* obj, double fadeTime) {
    addBlankScene();
    pushFadeOutToBackScene(obj, fadeTime);
}

template<typename T>
void Animate::QueueOfScenes::pushDisplaceToNewScene(T* obj, int Dx, int Dy, double transTime) {
    addBlankScene();
    pushDisplaceToBackScene(obj, Dx, Dy, transTime);
}

template<typename T>
void Animate::QueueOfScenes::pushFocusToNewScene(T* obj, double focusTime) {
    addBlankScene();
    pushFocusToBackScene(obj, focusTime);
}

template<typename T>
void Animate::QueueOfScenes::pushUnfocusToNewScene(T* obj, double unfocusTime) {
    addBlankScene();
    pushUnfocusToBackScene(obj, unfocusTime);
}

// Push To New Kth Scene
template<typename T>
void Animate::QueueOfScenes::pushFadeInToNewKthScene(int k, T* obj, double fadeTim) {
    addBlankSceneToKth(k);
    pushFadeInToKthScene(k, obj, fadeTim);
}

template<typename T>
void Animate::QueueOfScenes::pushFadeOutToNewKthScene(int k, T* obj, double fadeTime) {
    addBlankSceneToKth(k);
    pushFadeOutToKthScene(k, obj, fadeTime);
}

template<typename T>
void Animate::QueueOfScenes::pushTransformToNewKthScene(int k, T* obj, int Tx, int Ty, double transTime) {
    pushToNewKthScene(k, std::bind(&transform<T>, obj, Tx, Ty, &currTime, transTime));
}

template<typename T>
void Animate::QueueOfScenes::pushSlideInToNewKthScene(int k, T* obj, double slideTime) {
    addBlankSceneToKth(k);
    pushSlideInToKthScene(k, obj, slideTime);
}

template<typename T>
void Animate::QueueOfScenes::pushSlideOutToNewKthScene(int k, T* obj, double slideTime) {
    addBlankSceneToKth(k);
    pushSlideOutToKthScene(k, obj, slideTime);
}

template<typename T>
void Animate::QueueOfScenes::pushRedirectToNewKthScene(int k, T* A, T* C, double travelTime) {
    addBlankSceneToKth(k);
    pushRedirectToKthScene(k, A, C, travelTime);
}

template<typename T>
void Animate::QueueOfScenes::pushFocusToNewKthScene(int k, T* obj, double focusTime) {
    addBlankSceneToKth(k);
    pushFocusToKthScene(k, obj, focusTime);
}

template<typename T>
void Animate::QueueOfScenes::pushUnfocusToNewKthScene(int k, T* obj, double unfocusTime) {
    addBlankSceneToKth(k);
    pushUnfocusToKthScene(k, obj, unfocusTime);
}

#endif
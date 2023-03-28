#ifndef ANIMATION_H
#define ANIMATION_H

#include <list>
// #include <queue>
#include <vector>
#include <functional>

#include "../core/ccppclass.h"
#include "../core/ccppfunc.h"

// NOTE: Templated function cannot be seperated into multiple files

namespace Animate {
    double bezier(double S, double T, double t);

    // DO NOT USE DIRECTLY
    template<typename T> 
    bool fadeIn(T* obj, double* currTime, double fadeTime) {
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
    bool fadeOut(T* obj, double *currTime, double fadeTime) {
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
    bool displace(T* obj, int Dx, int Dy, double* currTime, double transTime) {
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
    bool transform(T* obj, int Tx, int Ty, double* currTime, double transTime) {
        return displace(obj, obj->lx + Tx, obj->ly + Ty, currTime, transTime);
    }

    // DO NOT USE DIRECTLY
    template<typename T>
    bool slideIn(T* obj, double* currTime, double slideTime) {
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
    bool slideOut(T* obj, double* currTime, double slideTime) {
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
    bool redirect(T* A, T* C, double* currTime, double travelTime) {
        assert(A->pNext != nullptr);
        if (*currTime + elapseTime >= travelTime) {
            float _transparent = A->aNext.transparent;
            float _percent = A->aNext.percent;
            A->setNext(C);
            A->aNext.setTransparent(_transparent);
            A->aNext.setPercent(_percent);
            return true;
        }
        raylib::Vector2 cA = A->aNext.pA + toVector2(*A->aNext.sA / 2, *A->aNext.sA / 2);
        raylib::Vector2 cB = A->aNext.pB + toVector2(*A->aNext.sB / 2, *A->aNext.sB / 2);
        raylib::Vector2 cC = toVector2(C->x, C->y) + toVector2(C->size / 2, C->size / 2);

        if (dist(cA, cB) <= *A->aNext.sA / 2 + *A->aNext.sB / 2) {
            return false;
        }

        raylib::Vector2 AB = cB - cA;
        raylib::Vector2 BA = cA - cB;
        raylib::Vector2 CA = cA - cC;

        raylib::Vector2 newB = cB + A->aNext.ftB(BA);
        raylib::Vector2 newC = cC + C->outerShapeIn(CA);

        // newB -> newC
        raylib::Vector2 BC = newC - newB;

        A->aNext.transB = BC * (*currTime / travelTime);

        // newB + A->aNext.transB
        A->aNext.transA = A->outerShapeOut(newB + A->aNext.transB - cA) - A->outerShapeOut(AB);

        return false;
    }

    template<typename T>
    bool focus(T* obj, double* currTime, double focusTime = FOCUS_TIME) {
        if (*currTime + elapseTime >= focusTime) {
            obj->isFocus = false;
            return true;
        }
        obj->isFocus = true;
        return false;
    }

    class QueueOfScenes {
    public:
        double currTime;
        // std::queue<std::vector<std::function<bool()>>> q;
        std::list<std::list<std::function<bool()>>> q;

        QueueOfScenes();

        void pushToFrontScene(const std::function<bool()> &func);
        void pushToKthScene(int k, const std::function<bool()> &func);
        void pushToBackScene(const std::function<bool()> &func);
        void pushToNewScene(const std::function<bool()> &func);
        void pushToNewKthScene(int k, const std::function<bool()> &func);
        void pushSceneToBack(const std::list<std::function<bool()>> &scene);
        void pushSceneToKth(int k, const std::list<std::function<bool()>> &funcList);
        void addBlankScene();
        void addBlankSceneToKth(int k);
        
        void run();

        // Push To Front Scene
        template<typename T>
        void pushFadeInToFrontScene(T* obj, double fadeTime = FADEIN_TIME) {
            pushToFrontScene(
                std::bind(&fadeIn<T>, obj, &currTime, fadeTime)
            );
        }

        template<typename T>
        void pushFadeOutToFrontScene(T* obj, double fadeTime = FADEOUT_TIME) {
            pushToFrontScene(
                std::bind(&fadeOut<T>, obj, &currTime, fadeTime)
            );
        }

        template<typename T>
        void pushDisplaceToFrontScene(T* obj, int Dx, int Dy, double transTime = TRANS_TIME) {
            pushToFrontScene(std::bind(&displace<T>, obj, Dx, Dy, &currTime, transTime));
        }

        template<typename T>
        void pushTransformToFrontScene(T* obj, int Tx, int Ty, double transTime = TRANS_TIME) {
            pushToFrontScene(std::bind(&transform<T>, obj, Tx, Ty, &currTime, transTime));
        }

        // Push To Back Scene
        template<typename T>
        void pushFadeInToBackScene(T* obj, double fadeTime = FADEIN_TIME) {
            pushToBackScene(std::bind(&fadeIn<T>, obj, &currTime, fadeTime));
        }

        template<typename T>
        void pushFadeOutToBackScene(T* obj, double fadeTime = FADEOUT_TIME) {
            pushToBackScene(std::bind(&fadeOut<T>, obj, &currTime, fadeTime));
        }

        template<typename T>
        void pushDisplaceToBackScene(T* obj, int Dx, int Dy, double transTime = TRANS_TIME) {
            pushToBackScene(std::bind(&displace<T>, obj, Dx, Dy, &currTime, transTime));
        }

        // Push To Kth Scene
        template<typename T>
        void pushFadeInToKthScene(int k, T* obj, double fadeTime = FADEIN_TIME) {
            pushToKthScene(k, std::bind(&fadeIn<T>, obj, &currTime, fadeTime));
        }


        template<typename T>
        void pushFadeOutToKthScene(int k, T* obj, double fadeTime = FADEOUT_TIME) {
            pushToKthScene(k, std::bind(&fadeOut<T>, obj, &currTime, fadeTime));
        }

        template<typename T>
        void pushTransformToKthScene(int k, T* obj, int Tx, int Ty, double transTime = TRANS_TIME) {
            pushToKthScene(k, std::bind(&transform<T>, obj, Tx, Ty, &currTime, transTime));
        }

        template<typename T>
        void pushDisplaceToKthScene(int k, T* obj, int Tx, int Ty, double transTime = TRANS_TIME) {
            pushToKthScene(k, std::bind(&displace<T>, obj, Tx, Ty, &currTime, transTime));
        }

        template<typename T>
        void pushSlideInToKthScene(int k, T* obj, double slideTime = SLIDE_TIME) {
            pushToKthScene(k, std::bind(&slideIn<T>, obj, &currTime, slideTime));
        }

        template<typename T>
        void pushSlideOutToKthScene(int k, T* obj, double slideTime = SLIDE_TIME) {
            pushToKthScene(k, std::bind(&slideOut<T>, obj, &currTime, slideTime));
        }

        template<typename T>
        void pushRedirectToKthScene(int k, T* A, T* C, double travelTime = TRAVEL_TIME) {
            pushToKthScene(k, std::bind(&redirect<T>, A, C, &currTime, travelTime));
        }

        template<typename T>
        void pushFocusToKthScene(int k, T* obj, double focusTime = FOCUS_TIME) {
            pushToKthScene(k, std::bind(&focus<T>, obj, &currTime, focusTime));
        }

        // Push To New Scene
        template<typename T>
        void pushFadeInToNewScene(T* obj, double fadeTime = FADEIN_TIME) {
            addBlankScene();
            pushFadeInToBackScene(obj, fadeTime);
        }

        template<typename T>
        void pushFadeOutToNewScene(T* obj, double fadeTime = FADEOUT_TIME) {
            addBlankScene();
            pushFadeOutToBackScene(obj, fadeTime);
        }

        template<typename T>
        void pushDisplaceToNewScene(T* obj, int Dx, int Dy, double transTime = TRANS_TIME) {
            addBlankScene();
            pushDisplaceToBackScene(obj, Dx, Dy, transTime);
        }

        // Push To New Kth Scene
        template<typename T>
        void pushFadeInToNewKthScene(int k, T* obj, double fadeTim = FADEIN_TIME) {
            addBlankSceneToKth(k);
            pushFadeInToKthScene(k, obj, fadeTim);
        }

        template<typename T>
        void pushFadeOutToNewKthScene(int k, T* obj, double fadeTime = FADEIN_TIME) {
            addBlankSceneToKth(k);
            pushFadeOutToKthScene(k, obj, fadeTime);
        }

        template<typename T>
        void pushTransformToNewKthScene(int k, T* obj, int Tx, int Ty, double transTime = TRANS_TIME) {
            pushToNewKthScene(k, std::bind(&transform<T>, obj, Tx, Ty, &currTime, transTime));
        }

        template<typename T>
        void pushSlideInToNewKthScene(int k, T* obj, double slideTime = SLIDE_TIME) {
            addBlankSceneToKth(k);
            pushSlideInToKthScene(k, obj, slideTime);
        }

        template<typename T>
        void pushSlideOutToNewKthScene(int k, T* obj, double slideTime = SLIDE_TIME) {
            addBlankSceneToKth(k);
            pushSlideOutToKthScene(k, obj, slideTime);
        }

        template<typename T>
        void pushRedirectToNewKthScene(int k, T* A, T* C, double travelTime = TRAVEL_TIME) {
            addBlankSceneToKth(k);
            pushRedirectToKthScene(k, A, C, travelTime);
        }

        template<typename T>
        void pushFocusToNewKthScene(int k, T* obj, double focusTime = FOCUS_TIME) {
            addBlankSceneToKth(k);
            pushFocusToKthScene(k, obj, focusTime);
        }
    };

    inline QueueOfScenes queueOfScenes;
}

#endif
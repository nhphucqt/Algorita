#ifndef ANIMATION_H
#define ANIMATION_H

#include <list>
// #include <queue>
// #include <vector>
#include <functional>

#include "../core/ccppclass.h"
#include "../core/ccppfunc.h"

// NOTE: Templated function cannot be seperated into multiple files

namespace Animate {
    double bezier(double S, double T, double t);
    bool delay(double* currTime, bool* isReversed);

    template<typename T> bool fadeIn(T* obj, double* currTime, bool* isReversed);
    template<typename T> bool fadeOut(T* obj, double* currTime, bool* isReversed);

    template<typename T> bool displace(T* obj, int Sx, int Sy, int Dx, int Dy, double* currTime, bool* isReversed);
    template<typename T> bool transform(T* obj, int Sx, int Sy, int Tx, int Ty, double* currTime, bool* isReversed);

    template<typename T> bool slideIn(T* obj, double* currTime, bool* isReversed);
    template<typename T> bool slideOut(T* obj, double* currTime, bool* isReversed);

    // template<typename T> bool redirect(T* A, T* C, double* currTime, bool* isReversed);

    template<typename T> bool focus(T* obj, double* currTime, bool* isReversed);
    template<typename T> bool unfocus(T* obj, double* currTime, bool* isReversed);

    template<typename T> bool focusBorder(T* obj, double* currTime, bool* isReversed);
    template<typename T> bool unfocusBorder(T* obj, double* currTime, bool* isReversed);

    template<typename T> bool fadeInKthNode(T* obj, int k, double *currTime, bool* isReversed);
    template<typename T> bool fadeOutKthNode(T* obj, int k, double *currTime, bool* isReversed);

    template<typename T> bool fadeInKthArrow(T* obj, int k, double *currTime, bool* isReversed);
    template<typename T> bool fadeOutKthArrow(T* obj, int k, double *currTime, bool* isReversed);

    template<typename T> bool focusKthNode(T* obj, int k, double *currTime, bool* isReversed);
    template<typename T> bool unfocusKthNode(T* obj, int k, double *currTime, bool* isReversed);

    template<typename T> bool focusKthNodeBorder(T* obj, int k, double *currTime, bool* isReversed);
    template<typename T> bool unfocusKthNodeBorder(T* obj, int k, double *currTime, bool* isReversed);

    template<typename T> bool focusKthArrow(T* obj, int k, double *currTime, bool* isReversed);
    template<typename T> bool unfocusKthArrow(T* obj, int k, double *currTime, bool* isReversed);

    template<typename T> bool displaceKthNode(T* obj, int k, int Sx, int Sy, int Dx, int Dy, double *currTime, bool* isReversed);
    template<typename T> bool transformKthNode(T* obj, int k, int Sx, int Sy, int Tx, int Ty, double *currTime, bool* isReversed);

    template<typename T> bool slideInKthArrow(T* obj, int k, double *currTime, bool* isReversed);
    template<typename T> bool slideOutKthArrow(T* obj, int k, double *currTime, bool* isReversed);

    template<typename T> bool redirect(T* A, T* C, double *currTime, bool* isReversed);

    template<typename OT, typename MT> bool unfocusAllNodes(OT* obj, double* currTime, bool* isReversed);
    template<typename OT, typename MT> bool fadeInAllNodes(OT* obj, double* currTime, bool* isReversed);
    template<typename OT, typename MT> bool fadeOutAllNodes(OT* obj, double* currTime, bool* isReversed);

    class QueueOfScenes {
    public:
        std::list<std::function<bool()>> q;

        QueueOfScenes();

        void clearScenes();
        void push(const std::function<bool()> &func);
        bool run();
    };
}

#include "animation_template.cpp"
#endif
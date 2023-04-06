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
    template<typename T> bool fadeOut(T* obj, double *currTime, bool* isReversed);

    template<typename T> bool displace(T* obj, int Dx, int Dy, double* currTime, bool* isReversed);
    template<typename T> bool transform(T* obj, int Tx, int Ty, double* currTime, bool* isReversed);

    template<typename T> bool slideIn(T* obj, double* currTime, bool* isReversed);
    template<typename T> bool slideOut(T* obj, double* currTime, bool* isReversed);

    template<typename T> bool redirect(T* A, T* C, double* currTime, bool* isReversed);

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

    template<typename T> bool displaceKthNode(T* obj, int k, int Dx, int Dy, double *currTime, bool* isReversed);
    template<typename T> bool transformKthNode(T* obj, int k, int Tx, int Ty, double *currTime, bool* isReversed);

    template<typename T> bool slideInKthArrow(T* obj, int k, double *currTime, bool* isReversed);
    template<typename T> bool slideOutKthArrow(T* obj, int k, double *currTime, bool* isReversed);

    template<typename OT, typename MT> bool unfocusAllNodes(OT* obj, double* currTime, bool* isReversed);
    template<typename OT, typename MT> bool fadeInAllNodes(OT* obj, double* currTime, bool* isReversed);
    template<typename OT, typename MT> bool fadeOutAllNodes(OT* obj, double* currTime, bool* isReversed);
    template<typename OT, typename MT> bool transformAllNodesFrom(OT* obj, int k, int Tx, int Ty, double* currTime, bool* isReversed);

    class QueueOfScenes {
    public:
        bool isReversed;
        double currTime;
        std::list<std::list<std::function<bool()>>> q;
        std::list<std::list<std::function<bool()>>>::iterator iter;

        QueueOfScenes();

        void setReverse(bool _r);
        void clearScenes();

        std::list<std::list<std::function<bool()>>>::iterator curScene() const;
        void resetCur();

        bool isLeftEnd() const;
        bool isRightEnd() const;
        bool isEnd() const;

        bool canRun() const;

        bool goTo();
        bool goNext();
        bool goPrev();

        void pushToBackScene(const std::function<bool()> &func);
        void pushToNewScene(const std::function<bool()> &func);
        
        void addBlankScene();

        bool run();
    };
}

#include "animation_template.cpp"
#endif
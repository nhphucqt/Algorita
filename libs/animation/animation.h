#ifndef ANIMATION_H
#define ANIMATION_H

#include <list>
#include <string>
#include <functional>

#include "../core/ccppclass.h"
#include "../core/ccppfunc.h"
#include "../rcore/rColor.h"

// NOTE: Templated function cannot be seperated into multiple files

namespace Animate {
    double bezier(double t);
    bool delay(double* currTime, bool* isReversed);

    template<typename T> bool assignValue(T* obj, int oldVal, int newVal, double* currTime, bool* isReversed);

    template<typename T> bool fadeIn(T* obj, double* currTime, bool* isReversed);
    template<typename T> bool fadeOut(T* obj, double* currTime, bool* isReversed);

    template<typename T> bool displace(T* obj, int Sx, int Sy, int Dx, int Dy, double* currTime, bool* isReversed);
    template<typename T> bool transform(T* obj, int Sx, int Sy, int Tx, int Ty, double* currTime, bool* isReversed);

    template<typename T> bool fadeOutDisplace(T* obj, int Sx, int Sy, int Dx, int Dy, double* currTime, bool* isReversed);
    template<typename T> bool fadeOutTransform(T* obj, int Sx, int Sy, int Tx, int Ty, double* currTime, bool* isReversed);

    template<typename T> bool slideIn(T* obj, double* currTime, bool* isReversed);
    template<typename T> bool slideOut(T* obj, double* currTime, bool* isReversed);

    template<typename T> bool slideColorIn(T* obj, double* currTime, bool* isReversed);
    template<typename T> bool slideColorOut(T* obj, double* currTime, bool* isReversed);

    bool transColor(Color* obj, Color** robj, Color* src, Color* snk, double* currTime, bool* isReversed);

    template<typename T> bool transText(T* obj, const std::string &src, const std::string &snk, double* currTime, bool* isReversed);

    template<typename T, typename MT> bool redirectHead(T* A, MT* arrow, T* C, double* currTime, bool* isReversed);
    template<typename T, typename MT> bool redirectTail(T* A, MT* arrow, T* C, double* currTime, bool* isReversed);

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
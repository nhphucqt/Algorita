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

    template<typename T> bool fadeIn(T* obj, double* currTime, double fadeTime = FADEIN_TIME);    
    template<typename T> bool fadeOut(T* obj, double *currTime, double fadeTime = FADEOUT_TIME);

    template<typename T> bool displace(T* obj, int Dx, int Dy, double* currTime, double transTime = TRANS_TIME);
    template<typename T> bool transform(T* obj, int Tx, int Ty, double* currTime, double transTime = TRANS_TIME);

    template<typename T> bool slideIn(T* obj, double* currTime, double slideTime = SLIDE_TIME);
    template<typename T> bool slideOut(T* obj, double* currTime, double slideTime = SLIDE_TIME);

    template<typename T> bool redirect(T* A, T* C, double* currTime, double travelTime = TRAVEL_TIME);

    template<typename T> bool focus(T* obj, double* currTime, double focusTime = FOCUS_TIME);
    template<typename T> bool unfocus(T* obj, double* currTime, double unfocusTime = UNFOCUS_TIME);

    template<typename T> bool focusBorder(T* obj, double* currTime, double focusTime = FOCUS_TIME);
    template<typename T> bool unfocusBorder(T* obj, double* currTime, double unfocusTime = UNFOCUS_TIME);

    template<typename T> bool fadeInKthNode(T* obj, int k, double *currTime, double fadeTime = FADEIN_TIME);
    template<typename T> bool fadeOutKthNode(T* obj, int k, double *currTime, double fadeTime = FADEOUT_TIME);

    template<typename T> bool focusKthNode(T* obj, int k, double *currTime, double focusTime = FOCUS_TIME);
    template<typename T> bool unfocusKthNode(T* obj, int k, double *currTime, double unfocusTime = UNFOCUS_TIME);

    template<typename T> bool focusKthNodeBorder(T* obj, int k, double *currTime, double focusTime = FOCUS_TIME);
    template<typename T> bool unfocusKthNodeBorder(T* obj, int k, double *currTime, double unfocusTime = UNFOCUS_TIME);

    template<typename T> bool focusKthArrow(T* obj, int k, double *currTime, double focusTime = FOCUS_TIME);
    template<typename T> bool unfocusKthArrow(T* obj, int k, double *currTime, double unfocusTime = UNFOCUS_TIME);

    template<typename OT, typename MT> bool unfocusAllNodes(OT* obj, double* currTime, double unfocusTime = UNFOCUS_TIME);

    class QueueOfScenes {
    public:
        double currTime;
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
        template<typename T> void pushFadeInToFrontScene(T* obj, double fadeTime = FADEIN_TIME);
        template<typename T> void pushFadeOutToFrontScene(T* obj, double fadeTime = FADEOUT_TIME);
        template<typename T> void pushDisplaceToFrontScene(T* obj, int Dx, int Dy, double transTime = TRANS_TIME);
        template<typename T> void pushTransformToFrontScene(T* obj, int Tx, int Ty, double transTime = TRANS_TIME);

        // Push To Back Scene
        template<typename T> void pushFadeInToBackScene(T* obj, double fadeTime = FADEIN_TIME);
        template<typename T> void pushFadeOutToBackScene(T* obj, double fadeTime = FADEOUT_TIME);
        template<typename T> void pushDisplaceToBackScene(T* obj, int Dx, int Dy, double transTime = TRANS_TIME);
        template<typename T> void pushFocusToBackScene(T* obj, double focusTime = FOCUS_TIME);
        template<typename T> void pushUnfocusToBackScene(T* obj, double unfocusTime = UNFOCUS_TIME);

        // Push To Kth Scene
        template<typename T> void pushFadeInToKthScene(int k, T* obj, double fadeTime = FADEIN_TIME);
        template<typename T> void pushFadeOutToKthScene(int k, T* obj, double fadeTime = FADEOUT_TIME);
        template<typename T> void pushTransformToKthScene(int k, T* obj, int Tx, int Ty, double transTime = TRANS_TIME);
        template<typename T> void pushDisplaceToKthScene(int k, T* obj, int Tx, int Ty, double transTime = TRANS_TIME);
        template<typename T> void pushSlideInToKthScene(int k, T* obj, double slideTime = SLIDE_TIME);
        template<typename T> void pushSlideOutToKthScene(int k, T* obj, double slideTime = SLIDE_TIME);
        template<typename T> void pushRedirectToKthScene(int k, T* A, T* C, double travelTime = TRAVEL_TIME);
        template<typename T> void pushFocusToKthScene(int k, T* obj, double unfocusTime = UNFOCUS_TIME);
        template<typename T> void pushUnfocusToKthScene(int k, T* obj, double unfocusTime = UNFOCUS_TIME);

        // Push To New Scene
        template<typename T> void pushFadeInToNewScene(T* obj, double fadeTime = FADEIN_TIME);
        template<typename T> void pushFadeOutToNewScene(T* obj, double fadeTime = FADEOUT_TIME);
        template<typename T> void pushDisplaceToNewScene(T* obj, int Dx, int Dy, double transTime = TRANS_TIME);
        template<typename T> void pushFocusToNewScene(T* obj, double focusTime = FOCUS_TIME);
        template<typename T> void pushUnfocusToNewScene(T* obj, double unfocusTime = UNFOCUS_TIME);

        // Push To New Kth Scene
        template<typename T> void pushFadeInToNewKthScene(int k, T* obj, double fadeTim = FADEIN_TIME);
        template<typename T> void pushFadeOutToNewKthScene(int k, T* obj, double fadeTime = FADEIN_TIME);
        template<typename T> void pushTransformToNewKthScene(int k, T* obj, int Tx, int Ty, double transTime = TRANS_TIME);
        template<typename T> void pushSlideInToNewKthScene(int k, T* obj, double slideTime = SLIDE_TIME);
        template<typename T> void pushSlideOutToNewKthScene(int k, T* obj, double slideTime = SLIDE_TIME);
        template<typename T> void pushRedirectToNewKthScene(int k, T* A, T* C, double travelTime = TRAVEL_TIME);
        template<typename T> void pushFocusToNewKthScene(int k, T* obj, double focusTime = FOCUS_TIME);
        template<typename T> void pushUnfocusToNewKthScene(int k, T* obj, double unfocusTime = UNFOCUS_TIME);
    };

    inline QueueOfScenes queueOfScenes;
}

#include "animation_template.cpp"
#endif
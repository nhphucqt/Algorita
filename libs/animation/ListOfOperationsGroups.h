#ifndef LIST_OF_OPERATIONS_GROUPS_H
#define LIST_OF_OPERATIONS_GROUPS_H

// #include <vector>
#include <list>

#include "animation.h"
#include "OperationsGroups.h"
#include "../graphic/gui/Codeblock.h"
#include "../core/ExitStatus.h"

template<typename T>
class ListOfOperationsGroups {
// public:
private:
    static const int NUM_SPEED = 6;
    const double SPEED_SIGNATURE[NUM_SPEED] = {0.25, 0.5, 1.0, 2.0, 3.0, 4.0};

    Animate::RunType runType;

    bool isReversed;
    double currTime;
    double speed;
    int progress;

    T* mainObj;
    std::list<OperationsGroups<T>> groups;
    typename std::list<OperationsGroups<T>>::iterator iter;
    Codeblock codeblock;

public:
    ListOfOperationsGroups();

    double* getCurrTime();
    bool* getIsReversed();

    typename std::list<OperationsGroups<T>>::iterator curGroup() const;

    void setMainObj(T* _mainObj);

    void loadCode(const std::string &path);
    void updateCode();
    void resetCode();

    void addNewGroup();

    OperationsGroups<T>* backGroup();

    ExitStatus runNext(Animate::RunType rt);
    ExitStatus runPrev(Animate::RunType rt);

    ExitStatus toggleRun();

    void build();

    void updateCurrTime();
    void resetCurrTime();

    void updateProgress();

    bool canRunOper() const;
    bool canRunScene() const;
    bool run();

    ExitStatus toFirstState();
    ExitStatus toLastState();

    void clearGroup();
    
    double closestSpeed(double s);
    double getProgress();

    void draw();

    void destroy();
    
    void animateDelay();

    template<typename OT> void animateFadeIn(OT* obj);
    template<typename OT> void animateFadeOut(OT* obj);

    template<typename OT> void animateTransColor(OT* obj, OT src, OT snk);

    template<typename OT> void animateTransText(OT* obj, const std::string &src, const std::string &snk);

    template<typename OT> void animateDisplace(OT* obj, int Sx, int Sy, int Dx, int Dy);
    template<typename OT> void animateTransform(OT* obj, int Sx, int Sy, int Tx, int Ty);

    template<typename OT> void animateSlideIn(OT* obj);
    template<typename OT> void animateSlideOut(OT* obj);

    template<typename OT> void animateSlideColorIn(OT* obj);
    template<typename OT> void animateSlideColorOut(OT* obj);

    template<typename OT> void animateRedirect(OT* A, OT* C);

    template<typename OT> void animateNodeFromNormalToIter(OT* node);
    template<typename OT> void animateNodeFromNormalToFocus(OT* node);
    template<typename OT> void animateNodeFromNormalToRefer(OT* node);
    template<typename OT> void animateNodeFromNormalToRemove(OT* node);

    template<typename OT> void animateNodeFromIterToNormal(OT* node);
    template<typename OT> void animateNodeFromIterToNearIter(OT* node);
    template<typename OT> void animateNodeFromIterToFocus(OT* node);

    template<typename OT> void animateNodeFromNearIterToNormal(OT* node);

    template<typename OT> void animateNodeFromFocusToIter(OT* node);

    template<typename OT> void animateNodeFromReferToNormal(OT* node);

    template<typename OT> void animateArrowFromNormalToIter(OT* node);
    template<typename OT> void animateArrowFromNormalToFocus(OT* node);

    template<typename OT> void animateArrowFromIterToNormal(OT* node);

    template<typename OT> void animateArrowFromFocusToNormal(OT* node);
    
    template<typename OT> void animateArrowSlideFromIterToNormal(OT* node);

    template<typename OT> void animateArrowSlideFromNormalToIter(OT* node);
};

#include "ListOfOperationsGroups.cpp"
#endif
#ifndef LIST_OF_OPERATIONS_GROUPS_H
#define LIST_OF_OPERATIONS_GROUPS_H

#include <list>

#include "animation.h"
#include "OperationsGroups.h"
#include "../graphic/gui/Codeblock.h"
#include "../core/ExitStatus.h"

class ListOfOperationsGroups {
// public:
private:
    static const int NUM_SPEED = 9;
    const double SPEED_SIGNATURE[NUM_SPEED] = {0.1, 0.25, 0.5, 0.75, 1.0, 2.0, 3.0, 4.0, 8.0};

    Animate::RunType runType;

    bool isReversed;
    double currTime;
    int speedID;

    std::list<OperationsGroups> groups;
    std::list<OperationsGroups>::iterator iter;
    Codeblock codeblock;

public:
    ListOfOperationsGroups();

    double* getCurrTime();
    bool* getIsReversed();

    std::list<OperationsGroups>::iterator curGroup() const;

    void loadCode(const std::string &path);
    void updateCode();
    void resetCode();

    void addNewGroup();

    OperationsGroups* backGroup();

    ExitStatus runNext(Animate::RunType rt);
    ExitStatus runPrev(Animate::RunType rt);

    bool isPaused() const;
    bool isFinished() const;

    ExitStatus toggleRun();

    void build();

    void updateCurrTime();
    void resetCurrTime();

    bool canRunOper() const;
    bool canRunScene() const;
    bool run();

    ExitStatus toFirstState();
    ExitStatus toLastState();
    ExitStatus replay();

    void clearGroup();
    
    int closestSpeedID(double s);
    void decSpeed();
    void incSpeed();
    void resetSpeed();

    double getProgress();

    void draw(bool keyActive);

    void destroy();
    
    template<typename OT> void animateAssignValue(OT* obj, int oldVal, int newVal);

    void animateDelay();

    template<typename OT> void animateFadeIn(OT* obj);
    template<typename OT> void animateFadeOut(OT* obj);

    void animateTransColor(Color* obj, Color** robj, Color* src, Color* snk);

    template<typename OT> void animateTransText(OT* obj, const std::string &src, const std::string &snk);

    template<typename OT> void animateDisplace(OT* obj, double Sx, double Sy, double Dx, double Dy);
    template<typename OT> void animateTransform(OT* obj, double Sx, double Sy, double Tx, double Ty);

    template<typename OT> void animateSlideIn(OT* obj);
    template<typename OT> void animateSlideOut(OT* obj);

    template<typename OT> void animateSlideColorIn(OT* obj);
    template<typename OT> void animateSlideColorOut(OT* obj);

    template<typename OT, typename MT> void animateRedirectHead(OT* A, MT* arrow, OT* C);
    template<typename OT, typename MT> void animateRedirectTail(OT* A, MT* arrow, OT* C);

    template<typename OT> void animateNodeFromNormalToHighlight(OT* node, int i);

    template<typename OT> void animateNodeFromNormalToIter(OT* node);
    template<typename OT> void animateNodeFromNormalToNearIter(OT* node);
    template<typename OT> void animateNodeFromNormalToFocus(OT* node);
    template<typename OT> void animateNodeFromNormalToRefer(OT* node);
    template<typename OT> void animateNodeFromNormalToRemove(OT* node);
    template<typename OT> void animateNodeFromNormalToDisabled(OT* node);

    template<typename OT> void animateNodeFromIterToNormal(OT* node);
    template<typename OT> void animateNodeFromIterToNearIter(OT* node);
    template<typename OT> void animateNodeFromIterToFocus(OT* node);
    template<typename OT> void animateNodeFromIterToRemove(OT* node);
    template<typename OT> void animateNodeFromIterToDisabled(OT* node);

    template<typename OT> void animateNodeFromNearIterToNormal(OT* node);
    template<typename OT> void animateNodeFromNearIterToIter(OT* node);
    template<typename OT> void animateNodeFromNearIterToFocus(OT* node);
    template<typename OT> void animateNodeFromNearIterToRemove(OT* node);

    template<typename OT> void animateNodeFromFocusToIter(OT* node);
    template<typename OT> void animateNodeFromFocusToNormal(OT* node);

    template<typename OT> void animateNodeFromReferToNormal(OT* node);
    template<typename OT> void animateNodeFromReferToIter(OT* node);
    template<typename OT> void animateNodeFromReferToRemove(OT* node);

    template<typename OT> void animateNodeFromRemoveToNearIter(OT* node);

    template<typename OT> void animateNodeFromDisabledToNormal(OT* node);
    template<typename OT> void animateNodeFromDisabledToFocus(OT* node);

    template<typename OT> void animateArrowFromIterToBlank(OT* node);

    template<typename OT> void animateArrowFromNormalToIter(OT* node);
    template<typename OT> void animateArrowFromNormalToFocus(OT* node);

    template<typename OT> void animateArrowFromIterToNormal(OT* node);
    template<typename OT> void animateArrowFromIterToFocus(OT* node);

    template<typename OT> void animateArrowFromFocusToNormal(OT* node);
    
    template<typename OT> void animateArrowSlideFromIterToNormal(OT* node);

    template<typename OT> void animateArrowSlideFromNormalToIter(OT* node);
};

#include "ListOfOperationsGroups_template.cpp"
#endif
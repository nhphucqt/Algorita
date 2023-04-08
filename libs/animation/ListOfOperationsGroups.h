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
    Animate::RunType runType;

    bool isReversed;
    bool isPaused;
    double currTime;

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

    void build();

    void updateCurrTime();
    void resetCurrTime();

    bool canRunOper() const;
    bool canRunScene() const;
    bool run();

    ExitStatus toFirstState();
    ExitStatus toLastState();

    void clearGroup();
    
    void draw();

    void destroy();
    
    void animateDelay();

    template<typename OT> void animateFadeIn(OT* obj);
    template<typename OT> void animateFadeOut(OT* obj);

    template<typename OT> void animateFocus(OT* obj);
    template<typename OT> void animateUnfocus(OT* obj);

    template<typename OT> void animateFocusBorder(OT* obj);
    template<typename OT> void animateUnfocusBorder(OT* obj);

    template<typename OT> void animateDisplace(OT* obj, int Sx, int Sy, int Dx, int Dy);
    template<typename OT> void animateTransform(OT* obj, int Sx, int Sy, int Tx, int Ty);

    template<typename OT> void animateSlideIn(OT* obj);
    template<typename OT> void animateSlideOut(OT* obj);

    template<typename OT> void animateRedirect(OT* A, OT* C);

    template<typename OT, typename MT> void animateAppearAllNodes(OT* obj);
    template<typename OT, typename MT> void animateVanishAllNodes(OT* obj);
    template<typename OT, typename MT> void animateUnfocusAllNodes(OT* obj);
};

#include "ListOfOperationsGroups.cpp"
#endif
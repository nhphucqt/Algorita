#ifndef LIST_OF_OPERATIONS_GROUPS_TEMPLATE_CPP
#define LIST_OF_OPERATIONS_GROUPS_TEMPLATE_CPP

#include "ListOfOperationsGroups.h"

template<typename OT>
void ListOfOperationsGroups::animateAssignValue(OT* obj, int oldVal, int newVal) {
    backGroup()->push(std::bind(&Animate::assignValue<OT>, obj, oldVal, newVal, &currTime, &isReversed));
}
 
template<typename OT>
void ListOfOperationsGroups::animateFadeIn(OT* obj) {
    backGroup()->push(std::bind(&Animate::fadeIn<OT>, obj, &currTime, &isReversed));
}

template<typename OT>
void ListOfOperationsGroups::animateFadeOut(OT* obj) {
    backGroup()->push(std::bind(&Animate::fadeOut<OT>, obj, &currTime, &isReversed));
}

template<typename OT> 
void ListOfOperationsGroups::animateTransText(OT* obj, const std::string &src, const std::string &snk) {
    backGroup()->push(std::bind(Animate::transText<OT>, obj, src, snk, &currTime, &isReversed));
}


template<typename OT> 
void ListOfOperationsGroups::animateDisplace(OT* obj, int Sx, int Sy, int Dx, int Dy) {
    backGroup()->push(std::bind(&Animate::displace<OT>, obj, Sx, Sy, Dx, Dy, &currTime, &isReversed));
}

template<typename OT> 
void ListOfOperationsGroups::animateTransform(OT* obj, int Sx, int Sy, int Tx, int Ty) {
    backGroup()->push(std::bind(&Animate::transform<OT>, obj, Sx, Sy, Tx, Ty, &currTime, &isReversed));
}

template<typename OT> 
void ListOfOperationsGroups::animateFadeOutDisplace(OT* obj, int Sx, int Sy, int Dx, int Dy) {
    backGroup()->push(std::bind(&Animate::fadeOutDisplace<OT>, obj, Sx, Sy, Dx, Dy, &currTime, &isReversed));
}

template<typename OT> 
void ListOfOperationsGroups::animateFadeOutTransform(OT* obj, int Sx, int Sy, int Tx, int Ty) {
    backGroup()->push(std::bind(&Animate::fadeOutTransform<OT>, obj, Sx, Sy, Tx, Ty, &currTime, &isReversed));
}

template<typename OT>
void ListOfOperationsGroups::animateSlideIn(OT* obj) {
    backGroup()->push(std::bind(&Animate::slideIn<OT>, obj, &currTime, &isReversed));
}

template<typename OT>
void ListOfOperationsGroups::animateSlideOut(OT* obj) {
    backGroup()->push(std::bind(&Animate::slideOut<OT>, obj, &currTime, &isReversed));
}

template<typename OT>
void ListOfOperationsGroups::animateSlideColorIn(OT* obj) {
    backGroup()->push(std::bind(&Animate::slideColorIn<OT>, obj, &currTime, &isReversed));
}

template<typename OT>
void ListOfOperationsGroups::animateSlideColorOut(OT* obj) {
    backGroup()->push(std::bind(&Animate::slideColorOut<OT>, obj, &currTime, &isReversed));
}

template<typename OT, typename MT> 
void ListOfOperationsGroups::animateRedirectHead(OT* A, MT* arrow, OT* C) {
    backGroup()->push(std::bind(&Animate::redirectHead<OT, MT>, A, arrow, C, &currTime, &isReversed));
}

template<typename OT, typename MT> 
void ListOfOperationsGroups::animateRedirectTail(OT* A, MT* arrow, OT* C) {
    backGroup()->push(std::bind(&Animate::redirectTail<OT, MT>, A, arrow, C, &currTime, &isReversed));
}

template<typename OT>
void ListOfOperationsGroups::animateNodeFromNormalToIter(OT* node) {
    animateTransColor(&node->backColor, &node->pBackColor, &Theme::currTheme.NODE_BACKGROUND, &Theme::currTheme.NODE_BACKGROUND_FOCUS_ITER);
    animateTransColor(&node->bordColor, &node->pBordColor, &Theme::currTheme.NODE_BORDER, &Theme::currTheme.NODE_BORDER_FOCUS_ITER);
    animateTransColor(&node->foreColor, &node->pForeColor, &Theme::currTheme.NODE_FOREGROUND, &Theme::currTheme.NODE_FOREGROUND_FOCUS);
}

template<typename OT>
void ListOfOperationsGroups::animateNodeFromNormalToFocus(OT* node) {
    animateTransColor(&node->backColor, &node->pBackColor, &Theme::currTheme.NODE_BACKGROUND, &Theme::currTheme.NODE_BACKGROUND_FOCUS);
    animateTransColor(&node->bordColor, &node->pBordColor, &Theme::currTheme.NODE_BORDER, &Theme::currTheme.NODE_BORDER_FOCUS);
    animateTransColor(&node->foreColor, &node->pForeColor, &Theme::currTheme.NODE_FOREGROUND, &Theme::currTheme.NODE_FOREGROUND_FOCUS);
}

template<typename OT>
void ListOfOperationsGroups::animateNodeFromNormalToRefer(OT* node) {
    animateTransColor(&node->backColor, &node->pBackColor, &Theme::currTheme.NODE_BACKGROUND, &Theme::currTheme.NODE_BACKGROUND_FOCUS_REFER);
    animateTransColor(&node->bordColor, &node->pBordColor, &Theme::currTheme.NODE_BORDER, &Theme::currTheme.NODE_BORDER_FOCUS_REFER);
    animateTransColor(&node->foreColor, &node->pForeColor, &Theme::currTheme.NODE_FOREGROUND, &Theme::currTheme.NODE_FOREGROUND_FOCUS);
}

template<typename OT>
void ListOfOperationsGroups::animateNodeFromNormalToRemove(OT* node) {
    animateTransColor(&node->backColor, &node->pBackColor, &Theme::currTheme.NODE_BACKGROUND, &Theme::currTheme.NODE_BACKGROUND_FOCUS_REMOVE);
    animateTransColor(&node->bordColor, &node->pBordColor, &Theme::currTheme.NODE_BORDER, &Theme::currTheme.NODE_BORDER_FOCUS_REMOVE);
    animateTransColor(&node->foreColor, &node->pForeColor, &Theme::currTheme.NODE_FOREGROUND, &Theme::currTheme.NODE_FOREGROUND_FOCUS);
}

template<typename OT>
void ListOfOperationsGroups::animateNodeFromNormalToDisabled(OT* node) {
    animateTransColor(&node->backColor, &node->pBackColor, &Theme::currTheme.NODE_BACKGROUND, &Theme::currTheme.NODE_BACKGROUND_DISABLED);
    animateTransColor(&node->bordColor, &node->pBordColor, &Theme::currTheme.NODE_BORDER, &Theme::currTheme.NODE_BORDER_DISABLED);
    animateTransColor(&node->foreColor, &node->pForeColor, &Theme::currTheme.NODE_FOREGROUND, &Theme::currTheme.NODE_FOREGROUND_DISABLED);
}

template<typename OT>
void ListOfOperationsGroups::animateNodeFromIterToNormal(OT* node) {
    animateTransColor(&node->backColor, &node->pBackColor, &Theme::currTheme.NODE_BACKGROUND_FOCUS_ITER, &Theme::currTheme.NODE_BACKGROUND);
    animateTransColor(&node->bordColor, &node->pBordColor, &Theme::currTheme.NODE_BORDER_FOCUS_ITER, &Theme::currTheme.NODE_BORDER);
    animateTransColor(&node->foreColor, &node->pForeColor, &Theme::currTheme.NODE_FOREGROUND_FOCUS, &Theme::currTheme.NODE_FOREGROUND);
}

template<typename OT>
void ListOfOperationsGroups::animateNodeFromIterToNearIter(OT* node) {
    animateTransColor(&node->backColor, &node->pBackColor, &Theme::currTheme.NODE_BACKGROUND_FOCUS_ITER, &Theme::currTheme.NODE_BACKGROUND_FOCUS_NEAR_ITER);
    animateTransColor(&node->foreColor, &node->pForeColor, &Theme::currTheme.NODE_FOREGROUND_FOCUS, &Theme::currTheme.NODE_FOREGROUND_FOCUS_ITER);
}

template<typename OT>
void ListOfOperationsGroups::animateNodeFromIterToFocus(OT* node) {
    animateTransColor(&node->backColor, &node->pBackColor, &Theme::currTheme.NODE_BACKGROUND_FOCUS_ITER, &Theme::currTheme.NODE_BACKGROUND_FOCUS);
    animateTransColor(&node->bordColor, &node->pBordColor, &Theme::currTheme.NODE_BORDER_FOCUS_ITER, &Theme::currTheme.NODE_BORDER_FOCUS);
}

template<typename OT> 
void ListOfOperationsGroups::animateNodeFromIterToRemove(OT* node) {
    animateTransColor(&node->backColor, &node->pBackColor, &Theme::currTheme.NODE_BACKGROUND_FOCUS_ITER, &Theme::currTheme.NODE_BACKGROUND_FOCUS_REMOVE);
    animateTransColor(&node->bordColor, &node->pBordColor, &Theme::currTheme.NODE_BORDER_FOCUS_ITER, &Theme::currTheme.NODE_BORDER_FOCUS_REMOVE);
}

template<typename OT> 
void ListOfOperationsGroups::animateNodeFromIterToDisabled(OT* node) {
    animateTransColor(&node->backColor, &node->pBackColor, &Theme::currTheme.NODE_BACKGROUND_FOCUS_ITER, &Theme::currTheme.NODE_BACKGROUND_DISABLED);
    animateTransColor(&node->bordColor, &node->pBordColor, &Theme::currTheme.NODE_BORDER_FOCUS_ITER, &Theme::currTheme.NODE_BORDER_DISABLED);
    animateTransColor(&node->foreColor, &node->pForeColor, &Theme::currTheme.NODE_FOREGROUND_FOCUS, &Theme::currTheme.NODE_FOREGROUND_DISABLED);
}

template<typename OT>
void ListOfOperationsGroups::animateNodeFromNearIterToNormal(OT* node) {
    animateTransColor(&node->backColor, &node->pBackColor, &Theme::currTheme.NODE_BACKGROUND_FOCUS_NEAR_ITER, &Theme::currTheme.NODE_BACKGROUND);
    animateTransColor(&node->bordColor, &node->pBordColor, &Theme::currTheme.NODE_BORDER_FOCUS_ITER, &Theme::currTheme.NODE_BORDER);
    animateTransColor(&node->foreColor, &node->pForeColor, &Theme::currTheme.NODE_FOREGROUND_FOCUS_ITER, &Theme::currTheme.NODE_FOREGROUND);
}

template<typename OT>
void ListOfOperationsGroups::animateNodeFromNearIterToIter(OT* node) {
    animateTransColor(&node->backColor, &node->pBackColor, &Theme::currTheme.NODE_BACKGROUND_FOCUS_NEAR_ITER, &Theme::currTheme.NODE_BACKGROUND_FOCUS_ITER);
    animateTransColor(&node->foreColor, &node->pForeColor, &Theme::currTheme.NODE_FOREGROUND_FOCUS_ITER, &Theme::currTheme.NODE_FOREGROUND_FOCUS);
}

template<typename OT>
void ListOfOperationsGroups::animateNodeFromNearIterToFocus(OT* node) {
    animateTransColor(&node->backColor, &node->pBackColor, &Theme::currTheme.NODE_BACKGROUND_FOCUS_NEAR_ITER, &Theme::currTheme.NODE_BACKGROUND_FOCUS);
    animateTransColor(&node->bordColor, &node->pBordColor, &Theme::currTheme.NODE_BORDER_FOCUS_ITER, &Theme::currTheme.NODE_BORDER_FOCUS);
    animateTransColor(&node->foreColor, &node->pForeColor, &Theme::currTheme.NODE_FOREGROUND_FOCUS_ITER, &Theme::currTheme.NODE_FOREGROUND_FOCUS);
}

template<typename OT>
void ListOfOperationsGroups::animateNodeFromNearIterToRemove(OT* node) {
    animateTransColor(&node->backColor, &node->pBackColor, &Theme::currTheme.NODE_BACKGROUND_FOCUS_NEAR_ITER, &Theme::currTheme.NODE_BACKGROUND_FOCUS_REMOVE);
    animateTransColor(&node->bordColor, &node->pBordColor, &Theme::currTheme.NODE_BORDER_FOCUS_ITER, &Theme::currTheme.NODE_BORDER_FOCUS_REMOVE);
    animateTransColor(&node->foreColor, &node->pForeColor, &Theme::currTheme.NODE_FOREGROUND_FOCUS_ITER, &Theme::currTheme.NODE_FOREGROUND_FOCUS);
}

template<typename OT>
void ListOfOperationsGroups::animateNodeFromFocusToIter(OT* node) {
    animateTransColor(&node->backColor, &node->pBackColor, &Theme::currTheme.NODE_BACKGROUND_FOCUS, &Theme::currTheme.NODE_BACKGROUND_FOCUS_ITER);
    animateTransColor(&node->bordColor, &node->pBordColor, &Theme::currTheme.NODE_BORDER_FOCUS, &Theme::currTheme.NODE_BORDER_FOCUS_ITER);
}

template<typename OT>
void ListOfOperationsGroups::animateNodeFromFocusToNormal(OT* node) {
    animateTransColor(&node->backColor, &node->pBackColor, &Theme::currTheme.NODE_BACKGROUND_FOCUS, &Theme::currTheme.NODE_BACKGROUND);
    animateTransColor(&node->bordColor, &node->pBordColor, &Theme::currTheme.NODE_BORDER_FOCUS, &Theme::currTheme.NODE_BORDER);
    animateTransColor(&node->foreColor, &node->pForeColor, &Theme::currTheme.NODE_FOREGROUND_FOCUS, &Theme::currTheme.NODE_FOREGROUND);
}

template<typename OT>
void ListOfOperationsGroups::animateNodeFromReferToNormal(OT* node) {
    animateTransColor(&node->backColor, &node->pBackColor, &Theme::currTheme.NODE_BACKGROUND_FOCUS_REFER, &Theme::currTheme.NODE_BACKGROUND);
    animateTransColor(&node->bordColor, &node->pBordColor, &Theme::currTheme.NODE_BORDER_FOCUS_REFER, &Theme::currTheme.NODE_BORDER);
    animateTransColor(&node->foreColor, &node->pForeColor, &Theme::currTheme.NODE_FOREGROUND_FOCUS, &Theme::currTheme.NODE_FOREGROUND);
}

template<typename OT>
void ListOfOperationsGroups::animateNodeFromReferToIter(OT* node) {
    animateTransColor(&node->backColor, &node->pBackColor, &Theme::currTheme.NODE_BACKGROUND_FOCUS_REFER, &Theme::currTheme.NODE_BACKGROUND_FOCUS_ITER);
    animateTransColor(&node->bordColor, &node->pBordColor, &Theme::currTheme.NODE_BORDER_FOCUS_REFER, &Theme::currTheme.NODE_BORDER_FOCUS_ITER);
}

template<typename OT>
void ListOfOperationsGroups::animateNodeFromReferToRemove(OT* node) {
    animateTransColor(&node->backColor, &node->pBackColor, &Theme::currTheme.NODE_BACKGROUND_FOCUS_REFER, &Theme::currTheme.NODE_BACKGROUND_FOCUS_REMOVE);
    animateTransColor(&node->bordColor, &node->pBordColor, &Theme::currTheme.NODE_BORDER_FOCUS_REFER, &Theme::currTheme.NODE_BORDER_FOCUS_REMOVE);
}

template<typename OT>
void ListOfOperationsGroups::animateNodeFromRemoveToNearIter(OT* node) {
    animateTransColor(&node->backColor, &node->pBackColor, &Theme::currTheme.NODE_BACKGROUND_FOCUS_REMOVE, &Theme::currTheme.NODE_BACKGROUND_FOCUS_NEAR_ITER);
    animateTransColor(&node->bordColor, &node->pBordColor, &Theme::currTheme.NODE_BORDER_FOCUS_REMOVE, &Theme::currTheme.NODE_BORDER_FOCUS_ITER);
    animateTransColor(&node->foreColor, &node->pForeColor, &Theme::currTheme.NODE_FOREGROUND_FOCUS, &Theme::currTheme.NODE_FOREGROUND_FOCUS_ITER);
}

template<typename OT>
void ListOfOperationsGroups::animateNodeFromDisabledToNormal(OT* node) {
    animateTransColor(&node->backColor, &node->pBackColor, &Theme::currTheme.NODE_BACKGROUND_DISABLED, &Theme::currTheme.NODE_BACKGROUND);
    animateTransColor(&node->bordColor, &node->pBordColor, &Theme::currTheme.NODE_BORDER_DISABLED, &Theme::currTheme.NODE_BORDER);
    animateTransColor(&node->foreColor, &node->pForeColor, &Theme::currTheme.NODE_FOREGROUND_DISABLED, &Theme::currTheme.NODE_FOREGROUND);
}

template<typename OT>
void ListOfOperationsGroups::animateNodeFromDisabledToFocus(OT* node) {
    animateTransColor(&node->backColor, &node->pBackColor, &Theme::currTheme.NODE_BACKGROUND_DISABLED, &Theme::currTheme.NODE_BACKGROUND_FOCUS);
    animateTransColor(&node->bordColor, &node->pBordColor, &Theme::currTheme.NODE_BORDER_DISABLED, &Theme::currTheme.NODE_BORDER_FOCUS);
    animateTransColor(&node->foreColor, &node->pForeColor, &Theme::currTheme.NODE_FOREGROUND_DISABLED, &Theme::currTheme.NODE_FOREGROUND_FOCUS);
}

template<typename OT>
void ListOfOperationsGroups::animateArrowFromNormalToIter(OT* arrow) {
    animateTransColor(&arrow->lineColor, &arrow->pLineColor, &Theme::currTheme.ARROW_LINE, &Theme::currTheme.ARROW_LINE_FOCUS_ITER);
}

template<typename OT>
void ListOfOperationsGroups::animateArrowFromNormalToFocus(OT* arrow) {
    animateTransColor(&arrow->lineColor, &arrow->pLineColor, &Theme::currTheme.ARROW_LINE, &Theme::currTheme.ARROW_LINE_FOCUS);
}

template<typename OT>
void ListOfOperationsGroups::animateArrowFromIterToNormal(OT* arrow) {
    animateTransColor(&arrow->lineColor, &arrow->pLineColor, &Theme::currTheme.ARROW_LINE_FOCUS_ITER, &Theme::currTheme.ARROW_LINE);
}

template<typename OT>
void ListOfOperationsGroups::animateArrowFromIterToFocus(OT* arrow) {
    animateTransColor(&arrow->lineColor, &arrow->pLineColor, &Theme::currTheme.ARROW_LINE_FOCUS_ITER, &Theme::currTheme.ARROW_LINE_FOCUS);
}

template<typename OT>
void ListOfOperationsGroups::animateArrowFromFocusToNormal(OT* arrow) {
    animateTransColor(&arrow->lineColor, &arrow->pLineColor, &Theme::currTheme.ARROW_LINE_FOCUS, &Theme::currTheme.ARROW_LINE);
}

template<typename OT>
void ListOfOperationsGroups::animateArrowSlideFromIterToNormal(OT* arrow) {
    animateTransColor(&arrow->slideColor, &arrow->pSlideColor, &Theme::currTheme.ARROW_LINE_FOCUS_ITER, &Theme::currTheme.ARROW_LINE);
}

template<typename OT>
void ListOfOperationsGroups::animateArrowSlideFromNormalToIter(OT* arrow) {
    animateTransColor(&arrow->slideColor, &arrow->pSlideColor, &Theme::currTheme.ARROW_LINE, &Theme::currTheme.ARROW_LINE_FOCUS_ITER);
}

#endif
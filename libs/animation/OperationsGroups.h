#ifndef OPERATIONS_GROUPS_H
#define OPERATIONS_GROUPS_H

#include <list>
#include <functional>

#include "animation.h"
#include "../graphic/gui/Codeblock.h"

class OperationsGroups {
public:
// private:
    std::vector<int> highlightLines;
    Animate::QueueOfScenes opers;

public:
    OperationsGroups();

    void push(const std::function<bool()> &f);

    void setHighlightLines(const std::vector<int> &highlight);
    bool passHighlightLines(Codeblock* codeblock) const;

    void reset();

    // QueueOfScenes methods
    void clearFunc();
    bool run();

    void destroy();
};

#endif
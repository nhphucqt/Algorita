#include "OperationsGroups.h"

OperationsGroups::OperationsGroups() {
    highlightLines = std::vector<int>();
    opers = Animate::QueueOfScenes();
    // std::cerr << "OG::() resetcur " << (opers.q.end() == opers.iter) << '\n';
}

void OperationsGroups::push(const std::function<bool()> &f) {
    opers.push(f);
}

void OperationsGroups::setHighlightLines(const std::vector<int> &highlight) {
    highlightLines = highlight;
}

bool OperationsGroups::passHighlightLines(Codeblock* codeblock) const {
    codeblock->setHighlight(highlightLines);
    return true;
}

void OperationsGroups::reset() {
    clearFunc();
}

void OperationsGroups::clearFunc() {
    opers.clearScenes();
}

bool OperationsGroups::run() {
    return opers.run();
}

void OperationsGroups::destroy() {
    highlightLines.clear();
    opers.clearScenes();
}
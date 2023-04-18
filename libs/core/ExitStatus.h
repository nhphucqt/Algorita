#ifndef EXIT_STATUS_H
#define EXIT_STATUS_H

#include <string>

#include "../global.h"
#include "ccppfunc.h"

class ExitStatus {
public:
    bool success;
    std::string message;

    ExitStatus();
    ExitStatus(bool _success, const std::string &_message);
};

namespace ExitMess {
    const ExitStatus SUCCESS(true, "");
    const ExitStatus FAIL(false, "");

    const ExitStatus FAIL_VALUE_OOB(false, "Value is out of bounds: Allow from " + cf::num2str(Core::NODE_MIN_VALUE) + " to " + cf::num2str(Core::NODE_MAX_VALUE));

    const ExitStatus FAIL_LL_EMPTY(false, "The list is empty");
    const ExitStatus FAIL_LL_SIZE_OOB(false, "Size is out of bounds: Allow from 0 to " + cf::num2str(Core::MAX_NUM_NODE_SLL));
    const ExitStatus FAIL_LL_REACH_MAX_SIZE(false, "The list has reached maximum size which is " + cf::num2str(Core::MAX_NUM_NODE_SLL));
}

#endif
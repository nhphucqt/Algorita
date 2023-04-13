#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <algorithm>

#include "ccppfunc.h"
#include "ExitStatus.h"

namespace Valid {
    const std::string DIGIT = "0123456789";
    ExitStatus isMatch(const std::string &str, std::string match);
    ExitStatus isInRange(std::string num, int minValue, int maxValue);
}

#endif

#ifndef USER_FUNC_H
#define USER_FUNC_H

#include <vector>
#include <string>

#include "ExitStatus.h"
#include "validator.h"

namespace User {
    std::pair<ExitStatus, std::vector<int>> input2vector(const std::string &input, const std::string &match);
}

#endif
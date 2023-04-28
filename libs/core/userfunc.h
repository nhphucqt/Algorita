#ifndef USER_FUNC_H
#define USER_FUNC_H

#include <vector>
#include <string>
#include <sstream>

#include "ExitStatus.h"
#include "validator.h"

namespace User {
    ExitStatus getNum(std::stringstream &ss, int &num, bool &flagEOF, int minValue, int maxValue, const std::string &match);
    ExitStatus input2vector(const std::string &input, std::vector<int> &result, const std::string &match);
    ExitStatus extract2vector(std::stringstream &ss, std::vector<int> &result, const std::string &match);
}

#endif
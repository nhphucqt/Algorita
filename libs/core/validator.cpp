#include "validator.h"

ExitStatus Valid::isNumber(const std::string &str) {
    for (int i = 0; i < (int)str.size(); ++i) {
        if (!isdigit(str[i])) {
            return ExitStatus(false, "Not a number");
        }
    }
    return ExitMess::SUCCESS;
}

ExitStatus Valid::isMatch(const std::string &str, std::string match) {
    std::sort(match.begin(), match.end());
    for (int i = 0; i < (int)str.size(); ++i) {
        if (!std::binary_search(match.begin(), match.end(), str[i])) {
            return ExitStatus(false, "String contains invalid characters");
        }
    }
    return ExitMess::SUCCESS;
}

ExitStatus Valid::isMatch(char chr, const std::string &match) {
    if (match.find(chr) == match.npos) {
        return ExitStatus(false, "Invalid character");
    }
    return ExitMess::SUCCESS;
}


ExitStatus Valid::isInRange(std::string num, int minValue, int maxValue) {
    assert(minValue <= maxValue);
    std::string maxStr = cf::num2str(maxValue);
    cf::fixNumStr(num);
    if (num.size() > maxStr.size()) {
        return ExitStatus(false, "Max value exceeded");
    }
    if (num.size() == maxStr.size()) {
        if (num > maxStr) {
            return ExitStatus(false, "Max value exceeded");
        }
    }
    int realNum = cf::str2num(num);
    if (minValue > realNum) {
        return ExitStatus(false, "Min value exceeded");
    }
    return ExitStatus(true, "Valid number");
}

#include "userfunc.h"

ExitStatus User::getNum(std::stringstream &ss, int &num, bool &flagEOF, int minValue, int maxValue, const std::string &match) {
    std::string str;
    ExitStatus status;
    num = 0;
    flagEOF = false;
    char c;
    while (!isdigit(c = ss.get()) && !ss.eof() && ss) {
        if (!(status = Valid::isMatch(c, match)).success) {
            return status;
        }
    }
    if (!isdigit(c)) {
        flagEOF = true;
        return ExitStatus(false, "Number not found");
    }
    str += c;
    while (isdigit(c = ss.get()) && !ss.eof() && ss) {
        str += c;
    }
    if (!ss.eof() && ss && !(status = Valid::isMatch(c, match)).success) {
        return status;
    }
    if (!(status = Valid::isInRange(str, minValue, maxValue)).success) {
        return status;
    }
    num = cf::str2num(str);
    return ExitMess::SUCCESS;
}


ExitStatus User::input2vector(const std::string &input, std::vector<int> &result, const std::string &match) {
    result.clear();
    ExitStatus status = Valid::isMatch(input, match);
    if (!status.success) {
        status.message = "Input contains invalid characters";
        return status;
    }
    for (int i = 0, cnt = 0; i < (int)input.size(); ++i) {
        cnt++;
        if (i+1 == (int)input.size() || (isdigit(input[i]) ^ isdigit(input[i+1]))) {
            if (isdigit(input[i])) {
                std::string num = input.substr(i-cnt+1, cnt);
                status = Valid::isInRange(num, Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE);
                if (!status.success) {
                    return status;
                }
                result.push_back(cf::str2num(num));
            }
            cnt = 0;
        }
    }
    return ExitMess::SUCCESS;
}

ExitStatus User::input2vector(const std::string &input, std::vector<std::string> &result, const std::string &match) {
    result.clear();
    ExitStatus status = Valid::isMatch(input, match);
    if (!status.success) {
        status.message = "Input contains invalid characters";
        return status;
    }
    for (int i = 0, cnt = 0; i < (int)input.size(); ++i) {
        cnt++;
        if (i+1 == (int)input.size() || (input[i] >= 'a' && input[i] <= 'z') ^ (input[i+1] >= 'a' && input[i+1] <= 'z')) {
            if (input[i] >= 'a' && input[i] <= 'z') {
                std::string str = input.substr(i-cnt+1, cnt);
                if ((int)str.size() < 1 || (int)str.size() > Core::MAX_LEN_TRIE_ELM) {
                    return ExitMess::FAIL_TRIE_LEN_OOB;
                }
                result.push_back(str);
            }
            cnt = 0;
        }
    }
    return ExitMess::SUCCESS;
}

ExitStatus User::extract2vector(std::stringstream &ss, std::vector<int> &result, const std::string &match) {
    result.clear();
    ExitStatus status;
    bool flagEOF = false;
    int num = 0;
    while ((status = getNum(ss, num, flagEOF, Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE, match)).success) {
        result.push_back(num);
    }
    if (!flagEOF) {
        return status;
    }
    return ExitMess::SUCCESS;
}
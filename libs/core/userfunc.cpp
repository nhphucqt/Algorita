#include "userfunc.h"

std::pair<ExitStatus, std::vector<int>> User::input2vector(const std::string &input, const std::string &match) {
    std::vector<int> res;
    ExitStatus status = Valid::isMatch(input, match);
    if (!status.success) {
        status.message = "Input input";
        return std::make_pair(status, res);
    }
    for (int i = 0, cnt = 0; i < (int)input.size(); ++i) {
        cnt++;
        if (i+1 == (int)input.size() || (isdigit(input[i]) ^ isdigit(input[i+1]))) {
            if (isdigit(input[i])) {
                std::string num = input.substr(i-cnt+1, cnt);
                status = Valid::isInRange(num, Core::NODE_MIN_VALUE, Core::NODE_MAX_VALUE);
                if (!status.success) {
                    return std::make_pair(status, res);
                }
                res.push_back(cf::str2num(num));
            }
            cnt = 0;
        }
    }
    status = ExitStatus(true, "");
    return std::make_pair(status, res);
}

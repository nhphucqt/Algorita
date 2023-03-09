#include "ccppf.h"

std::string cf::num2str(int x) {
    if (x == 0) {
        return "0";
    } else {
        std::string ans;
        while (x > 0) {
            ans += x % 10 +  '0';
            x /= 10;
        }
        std::reverse(ans.begin(),ans.end());
        return ans;
    }
}
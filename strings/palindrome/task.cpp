#include "task.h"

bool is_palindrome(const std::string& s) {
    if (s.empty()) {
        return true;
    }
    else {
        int l = 0;
        int r = s.size() - 1;
        while (l < r) {
            char cur_l = tolower(s[l]);
            char cur_r = tolower(s[r]);
            if ((cur_l - 'a' >= 0 && cur_l - 'a' <= 25) && (cur_r - 'a' >= 0 && cur_r - 'a' <= 25)) {
                if (cur_l == cur_r) {
                    l++;
                    r--;
                }
                else {
                    return false;
                }
            }
            else {
                if (cur_l - 'a' < 0 || cur_l - 'a' > 25) {
                    l++;
                }
                if (cur_r - 'a' < 0 || cur_r - 'a' > 25) {
                    r--;
                }
            }
        }
        return true;
    }
}

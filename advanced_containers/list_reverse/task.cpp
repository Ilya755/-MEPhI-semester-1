#include "task.h"

void ReverseList(std::list<int>& l) {
    auto it = l.rbegin();
    std::list<int> ans;
    while (it != l.rend()) {
        auto cur = *(it++);
        ans.push_back(cur);
    }
    l = ans;
}

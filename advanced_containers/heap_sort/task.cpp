#include "task.h"

using namespace std;

vector<int> HeapSort(const vector<int>& v) {
    int n = (int)v.size();
    priority_queue<int, std::vector<int>, std::greater<int>> sorted;
    for (auto& el : v) {
        sorted.push(el);
    }
    vector<int> ans(n);
    for (auto& el : ans) {
        el = sorted.top();
        sorted.pop();
    }
    return ans;
}

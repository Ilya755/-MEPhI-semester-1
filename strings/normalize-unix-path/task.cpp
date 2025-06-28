#include <string>
#include <iterator>
#include <vector>

using namespace std;

string normalize(string_view path) {
    vector<string> split;
    string cur_s = "";
    size_t i = 0;
    if (path[0] == '/') {
        split.push_back("/");
        i = 1;
    }
    for (; i < path.size(); ++i) {
        if (path[i] == '/') {
            if (cur_s != "") {
                split.push_back(cur_s);
            }
            cur_s = "";
        }
        else {
            cur_s += path[i];
        }
    }
    if (!cur_s.empty()) {
        split.push_back(cur_s);
    }

    string ans;
    i = 0;
    if (split[0] == "/") {
        ans += '/';
        i = 1;
    }
    for (; i < split.size(); ++i) {
        if (split[i] == "..") {
            if (!ans.empty()) {
                if (split[0] == ".." && i && split[i - 1] == "..") {
                    ans += "..";    
                }
                else if (ans.size() > 1 && ans[ans.size() - 2] == '.') {
                    continue;;
                }
                else if (ans.size() == 1 && ans.back() == '/') {
                    continue;
                }
                else if (ans.size() > 1 && ans[ans.size() - 2] != '.') {
                    size_t j = ans.size() - 2;
                    while (ans[j] != '/') {
                        --j;
                    }
                    ans.erase(j, ans.size());
                }
            }
            else {
                ans += "..";
            }
        }
        else if (split[i] == ".") {
            if (!ans.empty()) {
                continue;
            }
            else {
                ans += '.';
            }
        }
        else {
            ans += split[i];
        }
        if (i != split.size() - 1 && ans.back() != '/') {
            ans += '/';
        }
    }
    if (ans.back() == '/' && ans.size() != 1) {
        ans.pop_back();
    }
    return ans;
}

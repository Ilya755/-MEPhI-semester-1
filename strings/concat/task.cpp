#include "task.h"

char* concat(const char* lhs, const char* rhs) {
    int i = 0;
    while (*(lhs + i) != '\0') {
        i++;
    }
    int len1 = i;
    i = 0;
    while (*(rhs +i) != '\0') {
        i++;
    }
    int len2 = i;
    char* ans = new char[len1 + len2 + 1];
    for (i = 0; i < len1; ++i) {
        ans[i] = *(lhs +i);
    }
    for (i = 0; i < len2; ++i) {
        ans[len1 + i] = *(rhs +i);
    }
    ans[len1 + len2] = '\0';
    return ans;
}

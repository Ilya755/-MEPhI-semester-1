#include "tasks.h"

#include <cassert>
#include <iostream>

int NPointers::Increment(int *x) {
    return ++(*x);
}

int NPointers::Multiply(int x, int y, bool *flag) {
    long long x1 = x;
    long long y1 = y; 

    if (x * y != x1 * y1)
    {
        *flag = true;
    }
    else
    {
        *flag = false;
    }
    return x * y;
}

int NPointers::ScalarProduct(const int *a, const int *b, int n) {
    int ans = 0;
    for (int i = 0; i < n; ++i)
    {
        ans += (a[i]) * (b[i]);
    }
    return ans;
}

int NPointers::SizeOfMaximumSquareOfCrosses(const char *a, int n, int m) {
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i*m + j] == '+') {
                bool flag = true;
                int cnt = 0;
                while (flag) {
                    for (int k = i; k < i + cnt; ++k) {
                        for (int l = j; l < j + cnt; ++l) {
                            if (k >= n || l >= m || a[k*m + l] == '.') {
                                flag = false;
                            }
                        }
                    }
                    if (cnt < n - 1 && cnt < m - 1) {
                        cnt++;
                    }
                    else {
                        flag = false;
                    }
                }
                ans = std::max(ans, cnt);
            }
        }
    }
    return ans;
}

long long *NPointers::MultiplyToLongLong(int x, int y) {
    long long x1 = x;
    long long y1 = y;
    long long *ans = new long long (x1 * y1);
    return ans;
}

void NReferences::MultiplyInplace(int &x, int y) {
    x *= y;
}

int NReferences::CompareArraysByAverage(const int *a, int n, int b[5]) {
    long double summ1 = 0;
    for(int i = 0; i < n; ++i) {
        summ1 += a[i];
    }
    double av1 = summ1 / n;

    long double summ2 = 0;
    int n1 = 5;
    for(int i = 0; i < n1; ++i) {
        summ2 += b[i];
    }
    double av2 = summ2 / n1;

    if (av1 < av2) {
        return -1;
    }
    else if (av1 == av2) {
        return 0;
    }
    else {
        return 1;
    }
}
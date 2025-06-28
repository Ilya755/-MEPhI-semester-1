#pragma once

namespace NPointers {
    int Increment(int *x);
    int Multiply(int x, int y, bool *flag);
    int ScalarProduct(const int *a, const int *b, int n);
    int SizeOfMaximumSquareOfCrosses(const char *a, int n, int m);
    long long *MultiplyToLongLong(const int x, const int y);
}

namespace NReferences {
    void MultiplyInplace(int &x, int y);
    int CompareArraysByAverage(const int *a, int n, int b[5]);
}

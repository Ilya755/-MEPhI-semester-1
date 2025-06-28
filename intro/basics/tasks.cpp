#include "tasks.h"

#include <cmath>

int NOuter::NInner::DoSomething(int lhs, int rhs) {
    return lhs + rhs;
}

int NOuter::DoSomething(int lhs, int rhs) {
    return lhs - rhs;
}

int NOverload::ProcessTwoArgs(int lhs, int rhs) {
    return lhs + rhs;
}

char NOverload::ProcessTwoArgs(char lhs, char rhs) {
    if (lhs - rhs > 0) {
        return lhs; 
    }
    else{
        return rhs;
    }
}

int NOverload::ProcessTwoArgs(int lhs, char rhs) {
    return lhs - rhs;
}

unsigned int NOverflow::WithOverflow(int lhs, int rhs) {
    return lhs + rhs;
}

uint64_t NOverflow::WithOverflow(int64_t lhs, int64_t rhs) {
    return lhs - rhs;
}

int NLoop::SumInRange(const int lhs, const int rhs) {
    int64_t summ = 0;
    for (int i = lhs; i < rhs; ++i) {
        summ += i;
    }
    return summ;
}

int NLoop::CountFixedBitsInRange(const int from, const int to, const int bitsCnt) {
    int cnt = 0;
    for (int i = from + 1; i < to; ++i) {
        int summ = 0;
        int cur = i;

        while (cur > 0) {
            summ += cur&1;
            cur >>= 1;
        }
        if (summ == bitsCnt) {
            ++cnt;
        }
    }
    return cnt;
}

double NMath::ComputeMathFormula(const double arg) {
    return fabs((sin(arg) / 2 + cos(arg)) * (sin(arg) / 2 + cos(arg)) + tan(arg) * atan(arg));
}

bool NMath::IsPositive(int arg) {
    if (arg > 0) {
        return true;
    }
    else {
        return false;
    }
}

int NRecursion::CalculateFibonacci(const int arg) {
    if (arg == 0) {
        return 0;
    }
    else if (arg == 1) {
        return 1;
    }
    else {
        return NRecursion::CalculateFibonacci(arg - 1) + NRecursion::CalculateFibonacci(arg - 2);
    }
}

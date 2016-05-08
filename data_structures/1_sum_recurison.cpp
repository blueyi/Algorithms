/*
 * sum_recurison.cpp
 * Copyright (C) 2016 blueyi <blueyi@debian>
 *
 * Distributed under terms of the MIT license.
 */

#include <iostream>
int sum_recurison(int *a, int N)
{
    return N < 1 ? 0 : sum_recurison(a, N - 1) + a[N-1];
}

int main(void)
{
    int N = 100;
    int a[N];
    for (int i = 1; i < 101; ++i) {
        a[i-1] = i;
    }
    std::cout << sum_recurison(a, N) << std::endl;
    return 0;
}



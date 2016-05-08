/*
 * 1_max2.cpp
 * Copyright (C) 2016  <@BLUEYI-PC>
 *
 * Distributed under terms of the MIT license.
 */

#include "../common/random_data.h"
#include <iostream>
#include <utility>

template <typename T> void max2_iteration(const std::vector<T> &vec, T &max1, T &max2)
{
    max1 = max2 = vec.front();
    for (auto v : vec) {
        if (max2 < v) {
            max2 = v;
            if (max1 < max2)
                std::swap(max1, max2);
        }
    }
}

template <typename T> void two_max_recursion_merge(const std::vector<T> &vec, std::size_t lo, std::size_t hi, T &max1, T &max2)
{
    if (lo + 2 == hi) {
        if (vec[lo] > vec[lo + 1]) {
            max1 = vec[lo];
            max2 = vec[lo + 1];
        }
        else {
            max1 = vec[lo + 1];
            max2 = vec[lo];
        }
        return;
    }
    if (lo + 3 == hi) {
        max1 = max2 = vec[lo] > vec[lo + 1] ? vec[lo] : vec[lo + 1];
        if (max2 > vec[hi - 1]) 
            max2 = vec[lo];
        else
            max1 = vec[hi - 1];
        return;
    }
    int mid = (lo + hi) / 2;
    T xl1, xl2; two_max_recursion_merge(vec, lo, mid, xl1, xl2);
    T xr1, xr2; two_max_recursion_merge(vec, mid, hi, xr1, xr2);
    if (xl1 > xr1) {
        max1 = xl1;
        max2 = xl2 > xr1 ? xl2 : xr1;
    }
    else {
        max1 = xr1;
        max2 = xr2 > xl1 ? xr2 : xl1;
    }
}

int main()
{
    std::vector<int> vec = random_int(20);
    int max1, max2;
    print(std::cout, vec, '*');
    max2_iteration(vec, max1, max2);
    std::cout << "iteration: " << max1 << " " << max2 << std::endl;

    two_max_recursion_merge(vec, 0, vec.size(), max1, max2);
    std::cout << std::endl << "recursion merge: " << max1 << " " << max2 << std::endl;

    return 0;
}



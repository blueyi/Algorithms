/*
 * sort_bubble_with_flag.cpp
 * Copyright (C) 2016  <@BLUEYI-PC>
 *
 * Distributed under terms of the MIT license.
 */

#include <iostream>
#include "../common/random_data.h"

template <typename T> void bubble_sort(std::vector<T> &vec)
{
    bool sorted = false;
    std::size_t n = vec.size();
    while (!sorted) {
        sorted = true;
        for (std::size_t i = 1; i < n; ++i) {
            if (vec[i-1] > vec[i]) {
                std::swap(vec[i-1], vec[i]);
                sorted = false;
            }
        }
        --n;
    }
}

int main()
{
    std::vector<int> rint = random_int(20);
    print(std::cout, rint, '*');
    bubble_sort(rint);
    print(std::cout, rint, '*');
    return 0;
}




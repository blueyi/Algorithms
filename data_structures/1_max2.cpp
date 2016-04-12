/*
 * 1_max2.cpp
 * Copyright (C) 2016  <@BLUEYI-PC>
 *
 * Distributed under terms of the MIT license.
 */

#include "../common/random_data.h"
#include <iostream>
#include <utility>

template <typename T> void max2_iteration(std::vector<T> &vec)
{
    T max1, max2;
    max1 = max2 = vec.front();
    for (auto v : vec) {
        if (max2 < v) {
            max2 = v;
            if (max1 < max2)
                std::swap(max1, max2);
        }
    }
    std::cout << max1 << " " << max2 << std::endl;
}

int main()
{
    std::vector<int> vec = random_int(20);
    print(std::cout, vec, '*');
    max2_iteration(vec);

    return 0;
}



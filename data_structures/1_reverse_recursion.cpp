/*
 * 1_reverse_recursion.cpp
 * Copyright (C) 2016  <@BLUEYI-PC>
 *
 * Distributed under terms of the MIT license.
 */

#include "../common/random_data.h"

#include <iostream>

void reverse(std::vector<int> &vec, std::vector<int>::size_type lo, std::vector<int>::size_type hi)
{
    if (lo < hi) {
        std::swap(vec[lo], vec[hi]);
        reverse(vec, ++lo, --hi);
    }
}

int main()
{
    std::vector<int> v = random_int(21);
    print(std::cout, v);
    reverse(v, 0, v.size() - 1);
    print(std::cout, v);
    return 0;
}



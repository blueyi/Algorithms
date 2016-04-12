/*
 * 1_count_ones.cpp
 * Copyright (C) 2016  <@BLUEYI-PC>
 *
 * Distributed under terms of the MIT license.
 */

#include <iostream>
std::size_t count_ones(int n)
{
    std::size_t sum = 0;
    while (0 < n) {
        sum += (n >>= 1) & 1;
    }
    return sum;
}

int main()
{
    for (int i = 0; i < 10; ++i) {
        std::cout << count_ones(i) << " ";
    }
    std::cout << std::endl;
    return 0;
}




/*
 * 1_count_ones.cpp
 * Copyright (C) 2016  <@BLUEYI-PC>
 *
 * Distributed under terms of the MIT license.
 */

#include <iostream>
#include <bitset>
//按位查找
std::size_t count_ones_shift(unsigned n)
{
    std::size_t sum = 0;
    while (0 < n) {
        sum += n & 1;
        n >>= 1;
    }
    return sum;
}

//按1统计
//将n与n-1相与，会消除掉n最右边一个1，因为n-1比n只少了最后一位1，
//所以相与之后n除了少了右边一位1之外，高位不会变化
std::size_t count_ones_reset1(unsigned n)
{
    std::size_t sum = 0;
    while (0 < n) {
        n &= n-1;
        ++sum;
    }
    return sum;
}

int main()
{
    for (unsigned i = 8; i < 100; i += 9) {
        std::bitset<sizeof(unsigned) * 8> bset(i);
        std::cout << bset.count() << "  count_ones_shift: " << count_ones_shift(i) << " " 
            << "count_ones_reset1: " << count_ones_reset1(i) << std::endl;
    }
    std::cout << std::endl;
    return 0;
}




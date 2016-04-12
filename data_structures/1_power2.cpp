/*
 * 1_power2.cpp
 * Copyright (C) 2016  <@BLUEYI-PC>
 *
 * Distributed under terms of the MIT license.
 */

#include <iostream>

inline int squar(int a) 
{
    return a * a;
}

int power2(int n)
{
    if (0 == n)
        return 1;
    return  0 == (n & 1) ?  squar(power2(n >> 1)) : squar(power2(n >> 1)) << 1;
}

int main()
{
    for (int i = 0; i < 10; ++i) 
        std::cout << power2(i) << " ";
    std::cout << std::endl;
}



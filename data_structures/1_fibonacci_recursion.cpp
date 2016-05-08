/*
 * 1_fibonacci_recursion.cpp
 * Copyright (C) 2016  <@BLUEYI-PC>
 *
 * Distributed under terms of the MIT license.
 */

#include <iostream>

long long fib1(long long n)
{
    return 2 > n ? n : fib1(n - 1) + fib1(n - 2);
}

long long fib2(long long n, long long pre)
{
    if (0 == n) {
        pre = 1;
        return 0;
    }
    else {
        long long prepre;
        pre = fib2(n-1, prepre);
        return prepre + pre;
    }
}

long long fib3(long long n)
{
    long long f0 = 0, f1 = 1;
    while (0 < n--) {
        f1 += f0;
        f0 = f1 - f0;
    }
    return f0;
}

int main()
{

    std::cout << "**fib3**" << std::endl;
    for (int i = 0; i < 99; ++i) {
        std::cout << fib3(i) << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "**fib2**" << std::endl;
    for (int i = 0; i < 41; ++i) {
        std::cout << fib1(i) << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
 
    std::cout << "**fib1**" << std::endl;
    for (int i = 0; i < 41; ++i) {
        std::cout << fib1(i) << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

   return 0;
}


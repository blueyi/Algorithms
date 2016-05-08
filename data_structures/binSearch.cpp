/*
 * binSearch.cpp
 * Copyright (C) 2016  <@BLUEYI-PC>
 *
 * Distributed under terms of the MIT license.
 */

#include <iostream>
#include <vector>

template <typename T> std::size_t binSearch(const std::vector<T> &vec, const T &e);
int main(void)
{
    std::vector<int> vec{1, 2, 4, 4, 4, 5, 5, 5, 5, 7, 9, 10, 10, 11};
    std::cout << "Original array:" << std::endl;
    std::cout << "  Num: ";
    for (auto v : vec) 
        std::cout << v << " ";
    std::cout << std::endl << "Index: ";
    for (int i = 0; i < vec.size(); ++i) 
        std::cout << i << " ";
    int e, res;
    std::cout << std::endl << "Enter your number: "; 
    while (std::cin >> e) {
        res = binSearch<int>(vec, e);
        if (vec[res] == e) 
            std::cout << "Ok: " << res << std::endl;
        else 
            std::cout << "NO: " << res << std::endl;
        std::cout << std::endl << "Enter your number: "; 
    }
    return 0;
}

template <typename T> std::size_t binSearch(const std::vector<T> &vec, const T &e)
{
    std::size_t lo = 0, hi = vec.size(), mid = 0;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        e < vec[mid] ? hi = mid : lo = mid + 1;
    }
    return --lo;
}


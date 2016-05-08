/*
 * sort_stl.cpp
 * Copyright (C) 2016  <@BLUEYI-PC>
 *
 * Distributed under terms of the MIT license.
 */

#include "../common/random_data.h"
#include <iostream>
#include <algorithm>
#include <functional>


int main(void)
{
    std::vector<int> vec = random_int(20);
    std::cout << "Origional: " << std::endl;
    print(std::cout, vec, '*');

    std::sort(vec.begin(), vec.end(), std::less<int>());
    std::cout << "Sort less: " << std::endl;
    print(std::cout, vec, '*');

    std::reverse(vec.begin(), vec.end());
    std::cout << "Sort greater: " << std::endl;
    print(std::cout, vec, '*');


    return 0;
}



/*
 * random_data_test.cpp
 * Copyright (C) 2016  <@BLUEYI-PC>
 *
 * Distributed under terms of the MIT license.
 */

#include "random_data.h"
#include <iostream>

int main()
{
    std::vector<int> vec = random_int(15, 1, 30);
    print(std::cout, vec);
    return 0;
}




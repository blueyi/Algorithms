/*
 * uniqueArray.cpp
 * Copyright (C) 2016  <@BLUEYI-PC>
 *
 * Distributed under terms of the MIT license.
 */

#include <iostream>
#include <vector>

//使用两个指针，一个指向当前已经唯一化的最后一个位置，另一个向后遍历需要唯一化的元素
//保证front之前的所有元素都始终是唯一的
//当front与after指向的值相同时，after向后移动，当不同时after值赋给front，且front也向后移动
template <typename T> void uniqueArray(std::vector<T> &vec)
{
    auto front = vec.begin(), after = vec.begin();  //都从第一个元素开始，避免只有一个元素而越界
    while (after++ != vec.end()) {
        if (*front != *after)       //如果不相同，则将后面的元素赋值给当前front所指向的位置
            *(++front) = *after;
    }
    vec.erase(front, after - 1);
}

int main(void)
{
    std::vector<int> vec{1, 2, 4, 4, 4, 5, 5, 5, 5, 7, 9, 10, 10, 11};
    std::cout << "Original array:" << std::endl;
    for (auto v : vec) 
        std::cout << v << " ";
    uniqueArray<int>(vec);
    std::cout << std::endl << "Unique array:" << std::endl;
    for (auto v : vec) 
        std::cout << v << " ";

    std::cout << std::endl;
    return 0;
}



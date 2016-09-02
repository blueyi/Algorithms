/*
 * sort.h
 * Copyright (C) 2016  <@BLUEYI-PC>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SORT_H
#define SORT_H
#include <vector>
#include <algorithm>

//默认是从小到大排序
//
//冒泡排序
//通过多次遍历所有元素，每次遍历时比较相邻两个元素的大小，将较小的元素调整到上面，直到所有元素都有序

template <typename T>
void bubbleSort(std::vector<T> vec)
{
    int N = vec.size();
    bool isSorted = true;
    while (!isSorted) {
        for (std::vector<T>::size_t i = 0; i < N; ++i) {
            if (vec[i] > vec[i + 1]) {
                std::swap(vec[i], vec[i + 1]);
                isSorted = false;
            }
        }
        --N;
    }
}

#endif /* !SORT_H */

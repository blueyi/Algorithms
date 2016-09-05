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

//默认排序结果是从小到大
//
//冒泡排序
//原理：通过多次遍历所有元素，每次遍历时比较相邻两个元素的大小，将较大的元素调整到下面，直到所有相邻元素都有序
//时间复杂度：当不使用bool判断时，默认最坏情况下外层循环至少需要执行n-1次，内层循环每次也需要执行n-1次，
//内部循环中每次需要比较一次，交换一次，内层循环时间复杂度为O(2*(n-1))，所以总的时间复杂度为O(2*(n-1)^2) = O(n^2)
//稳定性：由于每次比较时当两个元素相同时并不会发生交换，所以是稳定排序

template <typename T>
void bubbleSort(std::vector<T>& vec)
{
    std::size_t N = vec.size();
    bool isSorted = false;  //当某次遍历时发现所以想邻位置都已经有序，则退出外层循环，避免当已经有序时依然遍历的情况
    while (!isSorted) {
        isSorted = true;
        for (std::size_t i = 0; i < N; ++i) {
            if (vec[i] > vec[i + 1]) {
                std::swap(vec[i], vec[i + 1]);
                isSorted = false;
            }
        }
        --N;
    }
}

//插入排序
//原理：认真对于第i个元素，该元素的所有前面的元素都已经有序，将第i个元素依次与前面的元素比较并交换，最终将其插入到合适的位置
//时间复杂度：最坏情况下的时间复杂度刚好是一个等差数列的前n项和O(n*(n- )/2) = O(n^2)
//空间复杂度：
//稳定性：由于每次总是前一个元素会较先确定位置，所以是稳定排序
template <typename T>
void insertSort(std::vector<T> &vec)
{
    for (auto v = vec.begin() + 1; v != vec.end(); ++v) {
        T temp = *v;
        auto tv = v;
        while (temp < *(--tv)) {
            *(tv + 1) = *tv;
            if (tv == vec.begin())
                break;
        }
        *tv = temp;
    }
}

//选择排序
//原理：从第一个元素开始，从未排好序的元素中选出当前的最小值，与已排好序的元素的下一个位置上的元素交换。
//最终当所有元素都已经选完时，即全部有序
//时间复杂度：
//空间复杂度：
//稳定性
template <typename T>
void selectSort(std::vector<T> &vec) 
{
    for (auto v = vec.begin(); v != vec.end(); ++v) {
        //注意当模板与迭代器一起使用时需要在前面使用typename
        typename std::vector<T>::iterator it = v;  //始终指向无序中的最小值
        for (auto v2 = v + 1; v2 != vec.end(); ++v2) {
            if (*it > *v2)
                it = v2;
        } 
        if (it != v)
            std::swap(it, v);
    }
}

//快速排序
//原理：
//时间复杂度：
//空间复杂度：
//稳定性：
//

#endif /* !SORT_H */

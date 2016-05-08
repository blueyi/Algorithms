/*
 * insertSoft.cpp
 * Copyright (C) 2016  <@BLUEYI-PC>
 *
 * Distributed under terms of the MIT license.
 */

#include "../common/random_data.h"
#include <iostream>
#include <utility>

void insertSort(std::vector<int> &vec)
{
    for (auto v = vec.begin() + 1; v != vec.end(); ++v) {
        for (auto s = v; s != vec.begin() && *s < *(s - 1); --s) {
                std::swap(*s, *(s - 1));
        }
    }
}

void merge(std::vector<int> &vec, int lo, int mid, int hi)
{
    std::vector<int> t;
    for (int i = lo; i < mid; ++i) {
        t.push_back(vec[i]);
    }
    int lf = t.size();
    for (int i = lo, j = 0, k = mid; (j < lf || k < hi);) {
        if (j < lf && (!(k < hi) || t[j] <= vec[k])) vec[i++] = t[j++];
        if (k < hi && (!(j < lf) || t[j] > vec[k])) vec[i++] = vec[k++];
    }
}

void mergeSort(std::vector<int> &vec, int lo, int hi)
{
    if (2 > hi - lo)
        return;
    int mid = (lo + hi) >> 1;
    mergeSort(vec, lo, mid);
    mergeSort(vec, mid, hi);
    merge(vec, lo, mid, hi);
}

int main(void)
{
    std::vector<int> vec = random_int(20);
    std::cout << "Origional: " << std::endl;
    print(std::cout, vec, '*');
//    insertSort(vec);
    mergeSort(vec, 0, vec.size());
    std::cout << "Sorted: " << std::endl;
    print(std::cout, vec, '*');
    return 0;
}



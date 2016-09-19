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

//默认排序结果是从小到大，未说明的情况下时间复杂度都是指平均时间复杂度
//
//1.冒泡排序
//原理：通过多次遍历所有元素，每次遍历时比较相邻两个元素的大小，将较大的元素调整到下面，直到所有相邻元素都有序
//时间复杂度：当不使用bool判断时，默认最坏情况下外层循环至少需要执行n-1次，内层循环每次也需要执行n-1次，
//内部循环中每次需要比较一次，交换一次，内层循环时间复杂度为O(2*(n-1))，所以总的时间复杂度为O(2*(n-1)^2) = O(n^2)
//空间复杂度：需要的额外空间不随n的变化而变化，所以空间复杂度为O(1)
//稳定性：由于每次比较时当两个元素相同时并不会发生交换，所以是稳定排序
//适用：n小时较好
//优化：

template <typename T>
void bubbleSort(std::vector<T>& vec)
{
    std::size_t N = vec.size();
    bool isSorted = false;  //当某次遍历时发现所有相邻位置都已经有序，则退出外层循环，避免当已经有序时依然遍历的情况
    while (!isSorted) {
        isSorted = true;
        for (std::size_t i = 0; i < N - 1; ++i) {  //将较大的元素交换到最下面
            if (vec[i] > vec[i + 1]) {
                std::swap(vec[i], vec[i + 1]);
                isSorted = false;
            }
        }
        --N;
    }
}

//2.插入排序
//原理：认为对于第i个元素，该元素的所有前面的元素都已经有序，将第i个元素依次与前面的元素比较并交换，最终将其插入到合适的位置
//时间复杂度：最坏情况下的时间复杂度刚好是一个等差数列的前n项和O(n*(n- )/2) = O(n^2)
//空间复杂度：需要的额外空间不随n的变化而变化，所以空间复杂度为O(1)
//稳定性：由于每次总是前一个元素会较先确定位置，所以是稳定排序
//适用：大部分已经排序时较好
//优化：
template <typename T>
void insertSort(std::vector<T> &vec)
{
    for (std::size_t i = 1; i < vec.size(); ++i) {  //从第二个元素开始
        int temp = vec[i];
        int j = i;
        for (; j > 0 && vec[j-1] > temp; --j)  //如果当前元素比前面的元素小，则交换，直到它找到合适的位置
            vec[j] = vec[j-1];
        vec[j] = temp;
    }
}

//3.选择排序
//原理：从第一个元素开始，从未排好序的元素中选出当前的最小值，与已排好序的元素的下一个位置上的元素交换。
//最终当所有元素都已经选完时，即全部有序
//时间复杂度：最坏情况下为O(n*(n-1)/2) = O(n^2)
//空间复杂度：需要的额外空间不随n的变化而变化，所以空间复杂度为O(1)
//稳定性：位于前面的元素肯定会被优先选择，所以是稳定排序
//适用：n小时较好
//优化：
template <typename T>
void selectSort(std::vector<T> &vec) 
{
    for (auto v = vec.begin(); v != vec.end(); ++v) {
        //注意当模板与迭代器一起使用时需要在前面使用typename
        typename std::vector<T>::iterator it = v;  //始终指向无序中的最小值
        for (auto v2 = v + 1; v2 != vec.end(); ++v2) {  //选出剩余元素中的最小值
            if (*it > *v2)
                it = v2;
        } 
        if (it != v)  //如果当前元素不是它本身，则交换
            std::swap(*it, *v);
    }
}



//5.归并排序
//原理：将整个序列由中点分成两部分，再分别通过递归对这两部分继续划分，直到划分成的两部分各自只剩下一个元素时，进行合并。合并时进行比较，合并后的序列需要是有序的，当所以被递归划分出的子序列全部合并完时，即整个序列已经有序。
//时间复杂度：由归并排序的原理可知主要的时间消耗都在合并，当有n个待合并元素时，共需要O(n)的时间。若设时间复杂度为T(n)，
//则有T(n) = 2*T(n/2) + O(n)，再根据T(1) = 1  可 得T(n) = O(nlogn)。或者理解为归并在划分时刚好是一颗完全二叉树，每次归并需要对所有n个元素扫描一遍，时间复杂度为O(n)，根据完全二叉树的尝试，共需要O(logn)趟，所以总的时间复杂度为O(nlogn)
//空间复杂度：每趟归并都需要当前参与归并元素个数的1/2辅助空间，所以总是空间占用为 n/2 + n/4 + n/8 + ... + 0 = n- n/(2^n)
//所以空间复杂度为O(n)
//稳定性：由于在归并时采用的是当前面序列的当前值小于等于后面序列当前值时，都先将前面的序列值归入目标序列，所以并不会改变相等变量的顺序，所以是稳定排序。
//适用：n大时较好
//优化：

//合并
template <typename T>
void merge(std::vector<T> &vec, std::size_t lo, std::size_t mid, std::size_t hi)  //将两个已经有序的子序列合并到原序列中
{
    std::vector<T> tvec;  //声明一个临时vector，用于存放前面一半的序列
    for (std::size_t i = lo; i <= mid; ++i)
        tvec.push_back(vec[i]);
    for (std::size_t i = lo, j = 0, k = mid + 1; (j < mid - lo + 1) || (k <= hi);) {  //通过比较后将两组序列合并为一组有序序列
        if (((j < mid-lo+1) && (k > hi)) || (tvec[j] <= vec[k])) vec[i++] = tvec[j++];  //多加||前面的那个判断是为了将当某一组剩余的序列直接追加后已经合并后的有序序列之后
        if (((j >= mid-lo+1) && (k <= hi)) || (vec[k] < tvec[j])) vec[i++] = vec[k++];
    }
}
//递归分组并合并
template <typename T>
void merge_partion(std::vector<T> &vec, std::size_t lo, std::size_t hi)
{
    if (lo >= hi) return;
    std::size_t mid = (hi + lo) >> 1;
    merge_partion(vec, lo, mid);
    merge_partion(vec, mid + 1, hi);
    merge(vec, lo, mid, hi);
}

//重载一下，方便调用
template <typename T>
void mergeSort(std::vector<T> &vec)
{
    std::size_t lo = 0, hi = vec.size() - 1;
    merge_partion(vec, lo, hi);
}



//5.快速排序
//原理：选择一个合适的轴点，然后以此轴点将待排序列分为左右两部分，使位于轴点左边的都比轴点小，位于轴点右边的都比轴点大
//然后再以同样的方式递归左右两部分子序列，最终当只剩下一个元素时递归返回，整个序列即已经有序
//时间复杂度：快速排序与归并排序非常类似，归并排序的时间主要花在序列合并上，序列划分只需要O(1)的时间。而快速排序的时间主要花在划分上，每次划分都需要遍历所有n个元素，同样划分的序列可以构成一颗深度为logn（log以2为底的n）的完全二叉树，总的时间复杂度即为O(nlogn)，合并时间为O(1)，即划分返回时就已经有序。所以时间复杂度为O(nlogn)，实际上快速排序的平均时间复杂度只有O(1.386logn)，所以快速排序通常是首选排序算法。当然对于一个已经有序的序列，此时所需要的时间复杂度刚是最坏的情况，需要O(n^2)
//空间复杂度：由于在每次划分时需要一个变量来保存轴点元素的值，对于n个待排元素的序列，共需要划分的次数刚好为完全二叉树的尝试，所以空间复杂度为O(logn)
//稳定性：由于在划分比较时并不会考虑相等元素的顺序，所以是不稳定排序算法
//适用：n大时较好
//优化

//快速划分
template <typename T>
std::size_t quick_partion(std::vector<T> &vec, std::size_t lo, std::size_t hi)
{
    //默认选择第一个作为轴点，但这样容易导致左右不平衡，可以考虑取出3个元素，选择位于中间的元素作为轴点
    T pivot = vec[lo];  //保存轴点元素，留出空间用于移动元素
    while (lo < hi) {
        while (lo < hi && pivot <= vec[hi])  //将右侧小于轴点的元素值移动到轴点左边
            --hi;
        vec[lo] = vec[hi];
        while (lo < hi && pivot >= vec[lo])  //将左侧大于轴点元素的值移动到轴点右边
            ++lo;
        vec[hi] = vec[lo];
    }
    vec[lo] = pivot;
    return lo;
}

//递归左右子序列
template <typename T>
void quickSort(std::vector<T> &vec, std::size_t lo, std::size_t hi)
{
    if (hi <= lo)  //当只剩下一个元素时即已经有序
        return;
    std::size_t pivot = quick_partion(vec, lo, hi);  //
    quickSort(vec, lo, pivot);
    quickSort(vec, pivot + 1, hi);
}

//为了遍于调用，进行重载
template <typename T>
void quickSort(std::vector<T> &vec)
{
    std::size_t lo = 0, hi = vec.size() - 1;
    quickSort(vec, lo, hi);
}


//6.希尔排序
//原理：
//时间复杂度：
//空间复杂度：
//稳定性：
//适用：
//优化
//


//7.堆排序
//原理：
//时间复杂度：
//空间复杂度：
//稳定性：
//优化
//


//8.计数排序
//原理：
//时间复杂度：
//空间复杂度：
//稳定性：
//
//优化



#endif /* !SORT_H */

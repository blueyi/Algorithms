#include "random_data.h"
#include "sort.h"


int main(void)
{
    std::vector<int> rdata = random_int(15);
    print(rdata, std::cout, '=', "Original arr");

    std::vector<int> trdata = rdata;
    bubbleSort(trdata);
    print(trdata, std::cout, '=', "bubble sort");

    trdata = rdata;
    insertSort(trdata);
    print(trdata, std::cout, '=', "insert sort");

    trdata = rdata;
    selectSort(trdata);
    print(trdata, std::cout, '=', "select sort");

    trdata = rdata;
    mergeSort(trdata);
    print(trdata, std::cout, '=', "merge sort");

    trdata = rdata;
    quickSort(trdata);
    print(trdata, std::cout, '=', "quick sort");

    return 0;
}

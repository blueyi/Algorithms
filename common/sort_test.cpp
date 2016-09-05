#include "random_data.h"
#include "sort.h"


int main(void)
{
    std::vector<int> rdata = random_int(15);
    print(rdata, std::cout, '=');
    bubbleSort(rdata);
    print(rdata, std::cout, '=');
    insertSort(rdata);
    print(rdata, std::cout, '=');
    selectSort(rdata);
    print(rdata, std::cout, '*');
    return 0;
}

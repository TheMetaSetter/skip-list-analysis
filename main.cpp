#include "SkipList.hpp"

// The maximum number of levels is currently set to be 10. You can change it by modifying the value of maxLevel in SkipList.hpp.
// NOTICE: The maxLevel should be in range [1, 64] since the max power is calculated by 2^maxLevel - 1 and 2^64 - 1 is the maximum value of unsigned long long.

// This source code perform the following operations on the skip list:
// − Test whether a skip list is empty
// − Get the number of elements in a skip list
// − Insert a new item into the skip list
// − Remove an item from the skip list
// − Build a skip list from given items
// − Remove all elements from the skip list

int main()
{
    int *arr;
    int n = 10;
    generateRandomArray(arr, n);

    SkipList skipList = buildSkipList(arr, n);

    std::cout << "Size of the skip list: " << skipListGetSize(skipList) << std::endl;
    printSkipList(skipList);

    skipListInsert(skipList, 123);
    skipListInsert(skipList, 456);

    std::cout << "Size of the skip list: " << skipListGetSize(skipList) << std::endl;

    skipListSearch(skipList, 123);
    skipListSearch(skipList, 456);

    printSkipList(skipList);

    skipListRemoveNode(skipList, 123);
    skipListRemoveNode(skipList, 456);

    std::cout << "Size of the skip list: " << skipListGetSize(skipList) << std::endl;
    printSkipList(skipList);

    makeEmptySkipList(skipList);
    std::cout << "Size of the skip list: " << skipListGetSize(skipList) << std::endl;

    printSkipList(skipList);

    return 0;
}

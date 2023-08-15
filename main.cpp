#include "SkipList.hpp"

int main()
{
    int *a;
    int n = 10;
    generateRandomArray(a, n);

    SkipList skipList = buildSkipList(a, n);

    skipListRemoveNode(skipList, 7633);

    printSkipList(skipList);

    makeEmptySkipList(skipList);

    printSkipList(skipList);

    return 0;
}

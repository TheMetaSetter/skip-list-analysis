#include "SkipList.hpp"

// The maximum number of levels is currently set to be 10. You can change it by modifying the value of maxLevel in SkipList.hpp.
// The maximum number of levels should be based on the number of elements you want to insert into the skip list.
// If the number of element you want to insert into the skip list is n, then the maximum number of levels should be log2(n).

// This source code perform the following operations on the skip list:
// − Test whether a skip list is empty
// − Get the number of elements in a skip list
// − Insert a new item into the skip list
// − Remove an item from the skip list
// − Build a skip list from given items
// − Remove all elements from the skip list

int main()
{
    // Generate a random array
    int *arr;
    int n = 10; // The size of the generated array, which is also the size of the lowest level of the skip list.
    generateRandomArray(arr, n);

    // Build a skip list from the generated array
    SkipList skipList = buildSkipList(arr, n);

    // Print the size of the skip list. It should be 10 now.
    std::cout << "Size of the skip list: " << skipListGetSize(skipList) << std::endl;

    // Print the skip list. The lowest level should contain 10 nodes.
    printSkipList(skipList);

    // Insert two new nodes
    skipListInsert(skipList, 123);
    skipListInsert(skipList, 456);

    // Print the size of the skip list. It should be 12 now.
    std::cout << "Size of the skip list: " << skipListGetSize(skipList) << std::endl;

    // Search the two nodes we've just inserted
    if (skipListSearch(skipList, 123))
    {
        std::cout << "Node 123 is in the skip list." << std::endl;
    }
    else
    {
        std::cout << "Node 123 is not in the skip list." << std::endl;
    }

    if (skipListSearch(skipList, 456))
    {
        std::cout << "Node 456 is in the skip list." << std::endl;
    }
    else
    {
        std::cout << "Node 456 is not in the skip list." << std::endl;
    }

    // Print the skip list. It should containt 12 nodes now, including two newly inserted nodes.
    printSkipList(skipList);

    // Remove the two newly inserted node
    skipListRemoveNode(skipList, 123);
    skipListRemoveNode(skipList, 456);

    // Search the two nodes we've just deleted. It should return nullptr.
    if (skipListSearch(skipList, 123))
    {
        std::cout << "Node 123 is in the skip list." << std::endl;
    }
    else
    {
        std::cout << "Node 123 is not in the skip list." << std::endl;
    }

    if (skipListSearch(skipList, 456))
    {
        std::cout << "Node 456 is in the skip list." << std::endl;
    }
    else
    {
        std::cout << "Node 456 is not in the skip list." << std::endl;
    }

    // Print the current size of the skip list. It should be 10 now.
    std::cout << "Size of the skip list: " << skipListGetSize(skipList) << std::endl;
    printSkipList(skipList);

    // Empty the skip list
    makeEmptySkipList(skipList);

    // Print the current size of the skip list. It should be 0 now.
    std::cout << "Size of the skip list: " << skipListGetSize(skipList) << std::endl;

    // Print the skip list. It should be unable to print since it's empty.
    printSkipList(skipList);

    return 0;
}

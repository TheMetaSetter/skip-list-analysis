//
//  skip_list.cpp
//  SKIP LIST
//
//  Created by Conqueror Mikrokosmos on 08/08/2023.
//

#include "SkipList.hpp"

bool isEmpty(SkipList skipList)
{
    return !skipList.root[0];
}

int skipListGetSize(SkipList skipList)
{
    if (isEmpty(skipList))
    {
        return 0;
    }

    int size = 0;

    int level;
    for (level = maxLevel - 1; level >= 0 && !skipList.root[level]; level--)
        ;

    while (level >= 0)
    {
        nodePtr currNode = skipList.root[level];
        while (currNode)
        {
            size++;
            currNode = currNode->next[level];
        }
        level--;
    }

    return size;
}

void printSkipList(SkipList skipList)
{
    if (isEmpty(skipList))
    {
        std::cout << "Error: Cannot print the skip list since it is empty.\n";
        return;
    }

    int level;
    for (level = maxLevel - 1; level >= 0 && !skipList.root[level]; level--)
        ;

    while (level >= 0)
    {
        nodePtr currNode = skipList.root[level];
        while (currNode)
        {
            std::cout << currNode->key << "->";
            currNode = currNode->next[level];
        }
        std::cout << "nullptr\n";
        level--;
    }
}

SkipList newSkipList()
{
    SkipList skipList;
    for (int i = 0; i < maxLevel; i++)
    {
        skipList.root[i] = nullptr;
    }

    return skipList;
}

// Funtion to choose level for a new node that will be inserted to the Skip List.
// Because the probability of a node to be inserted at a level is 1/2, excluded the level 0 that every node will be inserted to, so the probability of a node to be inserted at level 1 is 1/2, at level 2 is 1/4, at level 3 is 1/8, and so on.
// We utilize the fact that the distribution of odd and even number is almost equal for every set of random numbers.
// So we generate a random number and check if it is even or odd. This is similar to a coin flip with even is head and odd is tail.

int chooseLevel()
{
    int i = 0;

    while (i < maxLevel && rand() % 2 == 0)
    {
        i++;
    }

    return i;
}

nodePtr skipListSearch(SkipList skipList, const int key)
{
    // If the lowest level of the root node is empty, then the skip list is empty, then the search is unsuccessful.
    if (isEmpty(skipList))
    {
        return nullptr;
    }

    nodePtr prev, curr; // Using two-pointer method.

    int level;
    for (level = maxLevel - 1; level >= 0 && !skipList.root[level]; level--)
        ; // Find the highest non-null level.

    // If there's no non-null level of the root node, then the search operation cannot be performed.
    if (level < 0)
    {
        return nullptr;
    }

    prev = curr = skipList.root[level]; // Start the searching at the highest non-null level of the root node.

    // Loop 'til break
    while (true)
    {
        if (key == curr->key)
        { // If the current key is equal to the search key, then we return the current pointer, since it is what we're searching for.
            return curr;
        }
        else if (key < curr->key)
        {
            /*
             If the current key is larger than the search key, then there's 3 cases.
             Case 1: If we're standing at the lowest level (of a node or a skip list), then the search is unsuccessful, we return a nullptr. Note: prev->key is less than the search key and curr->key is larger than the search key.
             Case 2: If the current pointer is still a level of the root node, then we step down one level along the pointer array of the root node.
             Case 3: Otherwise, we're standing at a level of a node, which is not the root node. Since curr->key is larger than the search key, we have to go back one node on the same level and then step down one level the arrival node. We use the prev pointer to go back one node.
             */
            if (level == 0)
            {
                return nullptr;
            }
            else if (curr == skipList.root[level])
            {
                curr = skipList.root[--level];
            }
            else
                curr = prev->next[--level];
        }
        else
        {
            prev = curr; // If the current key is less than the search key, we automatically move the prev pointer forward.
            /*
             If the current key is less than the search key, then there's 2 cases.
             Case 1: If the next key on this level is not a nullptr, then we move the curr pointer forward.
             Case 2: If the next key on this level is a nullptr, then we're standing at the end of a level. We step down along this pointer array until we find a non-null next node.
                - After stepping down, if we found a non-null level, then we move the curr pointer forward at that level.
                - If there's no non-null level, we return a nullptr since the search is unsuccessful.
             */
            if (curr->next[level])
            {
                curr = curr->next[level];
            }
            else
            {
                for (level--; level >= 0 && !curr->next[level]; level--)
                    ; // Step down along this pointer array until we find a non-null next node.

                if (level >= 0)
                {
                    curr = curr->next[level];
                }
                else
                    return nullptr;
            }
        }
    }
}

void skipListInsert(SkipList &skipList, const int key)
{
    /*
     The insertion operation starts by searching the key in the skip list.
     The search starts at the highest level of the skip list.
     In this time, we use 2 array of pointers (or 2 "columns" of pointers) to traverse the skip list.
     This is because to insert a new node into the skip list, we need to search for the node before the node will be inserted.
     */
    nodePtr curr[maxLevel], prev[maxLevel], newNode;

    int level, i;

    curr[maxLevel - 1] = skipList.root[maxLevel - 1]; // Initialize the highest level of the current node with the highest level of the root node.
    prev[maxLevel - 1] = nullptr;                     // Initialize the highest level of the previous node with the nullptr.

    // The search starts at the highest level of the skip list.
    for (level = maxLevel - 1; level >= 0; level--)
    {
        // While the current level of the current node is not a nullptr and the key of that node is less than the new key, we move the curr pointer forward.
        while (curr[level] && curr[level]->key < key)
        {
            prev[level] = curr[level];
            curr[level] = curr[level]->next[level]; // Step into the next pointer and go to the same level as before.
        }

        if (curr[level] && curr[level]->key == key)
        { // Duplicates are not allowed in skip list so we return if we found the key.
            return;
        }

        /*
         E.g: Predecessor of a level 0 of node 5 is a level that points to the level 0 of the node 5.
         */
        if (level > 0)
        { // Go one level down if not the lowest level, using a link either from the root or from the predecessor.
            if (!prev[level])
            {                                               // If the predecessor is a nullptr, then we go down one level on the root node.
                curr[level - 1] = skipList.root[level - 1]; // Go down one level on the root node.
                prev[level - 1] = nullptr;                  // At the next level, the previous pointer is initialized with nullptr.
            }
            else
            {                                                   // If the predecessor is not a nullptr, then we use the link from the predecessor.
                curr[level - 1] = prev[level]->next[level - 1]; // Go to the next node of the predecessor and go down one level.
                prev[level - 1] = prev[level];
            }
        }
    }

    // Initialize the newNode.
    level = chooseLevel() + 1;                            // Generate randomly level for newNode.
    newNode = new SkipListNode();                         // Allocate memory for the newNode.
    newNode->next = new nodePtr[sizeof(nodePtr) * level]; // The next "column" of newNode has its height to be equal to its number of level.
    newNode->key = key;                                   // Set the new key.

    for (i = 0; i <= level; i++)
    {                               // Initialize next fields of newNode.
        newNode->next[i] = curr[i]; // On every levels, the next pointer of the newNode will point to the current node - which we found above - at the same level.
        if (!prev[i])
        { // If the previous node is a nullptr, then the root at that level will point to the newNode.
            skipList.root[i] = newNode;
        }
        else
        { // If the previous node is a non-nullptr, then we set the next pointer of it by the newNode.
            prev[i]->next[i] = newNode;
        }
    }
}

SkipList buildSkipList(int a[], int n)
{
    SkipList skipList = newSkipList();
    for (int i = 0; i < n; i++)
    {
        skipListInsert(skipList, a[i]);
    }

    return skipList;
}

void skipListRemoveNode(SkipList &skipList, const int key)
{
    nodePtr currNode[maxLevel], prevNode[maxLevel];

    currNode[maxLevel - 1] = skipList.root[maxLevel - 1];
    prevNode[maxLevel - 1] = nullptr;

    bool found = false;

    for (int currLevel = maxLevel - 1; currLevel >= 0; currLevel--)
    {
        while (currNode[currLevel] && currNode[currLevel]->key < key)
        {
            prevNode[currLevel] = currNode[currLevel];
            currNode[currLevel] = currNode[currLevel]->next[currLevel];
        }

        if (currNode[currLevel] && currNode[currLevel]->key == key)
        {
            found = true;
        }

        if (currLevel > 0)
        {
            if (!prevNode[currLevel])
            {
                currNode[currLevel - 1] = skipList.root[currLevel - 1];
                prevNode[currLevel - 1] = nullptr;
            }
            else
            {
                currNode[currLevel - 1] = prevNode[currLevel]->next[currLevel - 1];
                prevNode[currLevel - 1] = prevNode[currLevel];
            }
        }
    }

    if (!found)
    {
        std::cout << "Error: Remove node cannot be found.\n";
        return;
    }

    nodePtr deleteNode = nullptr; // The node (or column) will be deleted.

    for (int currLevel = maxLevel - 1; currLevel >= 0; currLevel--)
    {
        if (currNode[currLevel] && currNode[currLevel]->key == key)
        {
            deleteNode = currNode[currLevel];
            if (!prevNode[currLevel])
            {
                skipList.root[currLevel] = currNode[currLevel]->next[currLevel];
            }
            else
            {
                prevNode[currLevel]->next[currLevel] = currNode[currLevel]->next[currLevel];
            }
        }
    }

    delete deleteNode;
}

void generateRandomArray(int *&a, int n)
{
    a = new int[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 10000;
    }
}

void makeEmptySkipList(SkipList &skipList)
{
    if (isEmpty(skipList))
    {
        std::cout << "Error: Cannot make the skip list empty since it is already empty.\n";
        return;
    }

    /*
        Because all of the pointers of pointers (all of the nodes) are located at the lowest level. So we just need to delete the lowest level.
    */
    nodePtr currNode = skipList.root[0];
    while (currNode)
    {
        nodePtr deleteNode = currNode;
        currNode = currNode->next[0];
        delete deleteNode;
        // After deleting a node, remember to set it to nullptr to void garbage values.
        deleteNode = nullptr;
    }

    for (int currLevel = maxLevel - 1; currLevel >= 0; currLevel--)
    {
        if (skipList.root[currLevel])
        {
            skipList.root[currLevel] = nullptr;
        }
    }
}
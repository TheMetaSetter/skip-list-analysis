//
//  skip_list.hpp
//  SKIP LIST
//
//  Created by Conqueror Mikrokosmos on 08/08/2023.
//

#ifndef SkipList_hpp
#define SkipList_hpp

#include <iostream>
#include <vector>
#include <cmath>

const int maxLevel = 10;

typedef struct SkipListNode *nodePtr;
typedef unsigned long long ull;

// A node of a skip list is similar to a column with a key value and each row (level) contains a pointer. In other words, one node contains multiple levels and multiple levels of a node points to corresponding levels of the next node.
struct SkipListNode
{
    int key;
    SkipListNode **next;
};

struct SkipList
{
    nodePtr root[maxLevel];
    ull powers[maxLevel];
};

SkipList newSkipList();
void printSkipList(SkipList skipList);
bool isEmpty(SkipList skipList);
void choosePowers(SkipList &skipList);
int chooseLevel(SkipList skipList);
nodePtr skipListSearch(SkipList skipList, const int key);
void skipListInsert(SkipList &skipList, const int key);
SkipList buildSkipList(int a[], int n);
void skipListRemoveNode(SkipList &skipList, const int key);
void generateRandomArray(int *&a, int n);
void makeEmptySkipList(SkipList &SkipList);

#endif /* SkipList_hpp */
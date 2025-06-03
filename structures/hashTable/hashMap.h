#ifndef HASHMAP_H
#define HASHMAP_H
#include "../../types.h"
#define HASH_MAP_SIZE 11 //Use prime number for better distribution.

#define CHECK(ptr)                          \
    if (!ptr)                               \
    {                                       \
        printf("Error memory allocation."); \
        exit(1);                            \
    }

typedef struct Node
{
    void *data;
    struct Node *next;
} Node;

typedef struct HashMap
{
    Node **array;
} HashMap;

typedef ulong (*HashFunc)(void* key);
typedef void* (*KeySelector)(void* data);
typedef int (*KeyComparator)(void* key1, void* key2);

void set(HashMap *hashMap, void *data, KeySelector selector, KeyComparator comparator, HashFunc hashFunc);
void *get(HashMap *hashMap, void *searchKey, KeySelector selector, KeyComparator comparator, HashFunc hashFunc);

Node *initNode(void *data);
HashMap *initHashMap();

void printHashMap(HashMap *hashMap, KeySelector selector);
void freeHashMap(HashMap *hashMap);

int compareUints(void* key1, void* key2);
int compareStrings(void* key1, void* key2);
ulong hashUint(void *key);
ulong hashString(void *key);

#endif
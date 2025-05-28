#ifndef HASHMAP_H
#define HASHMAP_H

#define HASH_MAP_SIZE 11 //Use prime number for better distribution.

#define CHECK(ptr)                          \
    if (!ptr)                               \
    {                                       \
        printf("Error memory allocation."); \
        exit(1);                            \
    }

typedef struct Node
{
    void *key;
    void *val;
    struct Node *next;
} Node;

typedef struct HashMap
{
    Node **array;
} HashMap;

Node *initNode(void *key, void *val);
HashMap *initHashMap();
unsigned long hash(const char *key);
void setByStringKey(HashMap *hashMap, char *key, void *val);
void setByIntKey(HashMap *hashMap, int key, void *val);
void *getByStringKey(HashMap *hashMap, char *key);
void *getByIntKey(HashMap *hashMap, int key);
void printHashMap(HashMap *hashMap);
void freeHashMap(HashMap *hashMap);

#endif
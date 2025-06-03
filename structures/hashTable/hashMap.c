#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashMap.h"

Node *initNode(void *data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    CHECK(newNode);
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

HashMap *initHashMap()
{
    HashMap *newMap = (HashMap *)malloc(sizeof(HashMap));
    CHECK(newMap);
    newMap->array = (Node **)calloc(HASH_MAP_SIZE, sizeof(Node *));
    CHECK(newMap->array);

    return newMap;
}

// djb2, by Daniel J. Bernstein
unsigned long hashString(void *key)
{
    char *keyAsChar = (char *)key;
    unsigned long hash = 5381;
    int c;
    while ((c = *keyAsChar++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

void set(HashMap *hashMap, void *data, KeySelector selector, KeyComparator comparator, HashFunc hashFunc)
{
    void *key = selector(data);
    unsigned long index = hashFunc(key) % HASH_MAP_SIZE;

    if (hashMap->array[index])
    {
        Node *current = hashMap->array[index];

        while (current->next)
        {
            if (comparator(selector(current), key) == 0)
            {
                current->data = data;
                return;
            }
            current = current->next;
        }

        current->next = initNode(data);
    }
    else
    {
        hashMap->array[index] = initNode(data);
    }
}

void *get(HashMap *hashMap, void *searchKey, KeySelector selector, KeyComparator comparator, HashFunc hashFunc)
{
    unsigned long index = hashFunc(searchKey) % HASH_MAP_SIZE;

    if (hashMap->array[index])
    {
        Node *current = hashMap->array[index];

        while (current)
        {
            void *currentKey = selector(current->data);
            if (comparator(currentKey, searchKey) == 0)
                return current->data;
            current = current->next;
        }
    }

    return NULL;
}

void printHashMap(HashMap *hashMap, KeySelector keySelector)
{
    for (int i = 0; i < HASH_MAP_SIZE; i++)
    {
        if (hashMap->array[i])
        {
            Node *curr = hashMap->array[i];
            printf("[%d]: ", i);
            while (curr)
            {
                printf("%s %d, ", keySelector(curr), curr->data);
                curr = curr->next;
            }
            printf("\n");
        }
    }
}

void freeHashMap(HashMap *hashMap)
{
    for (int i = 0; i < HASH_MAP_SIZE; i++)
    {
        Node *curr = hashMap->array[i];
        while (curr)
        {
            Node *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }

    free(hashMap->array);
    free(hashMap);
}

int compareInts(void *key1, void *key2)
{
    return *((int *)key1) - *((int *)key2);
}

int compareStrings(void *key1, void *key2)
{
    return strcmp((char *)key1, (char *)key2);
}

unsigned long hashInt(void *key)
{
    return (*(long *)key) % HASH_MAP_SIZE;
}
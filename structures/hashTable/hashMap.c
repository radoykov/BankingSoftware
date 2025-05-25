#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashMap.h"

Node *initNode(void *key, void *val)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    CHECK(newNode);
    newNode->key = key;
    newNode->val = val;
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

// abv
// a + b + v
// int hash(char *key)
// {
//     int value = 0;
//     for (int i = 0; key[i] != '\0'; i++)
//     {
//         value += key[i];
//     }

//     return value;
// }


//djb2, by Daniel J. Bernstein
unsigned long hash(const char* key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

void setByStringKey(HashMap *hashMap, char *key, void *val)
{

    int index = hash(key) % HASH_MAP_SIZE;

    if (hashMap->array[index])
    {
        Node *current = hashMap->array[index];

        while (current->next)
        {
            if (strcmp((char *)current->key, key) == 0)
            {
                current->val = val;
                return;
            }
            current = current->next;
        }

        current->next = initNode(key, val);
    }
    else
    {
        hashMap->array[index] = initNode(key, val);
    }
}

void setByIntKey(HashMap *hashMap, int key, void *val)
{

    int index = key % HASH_MAP_SIZE;

    if (hashMap->array[index])
    {
        Node *current = hashMap->array[index];

        while (current->next)
        {
            if (*(int *)current->key == key)
            {
                current->val = val;
                return;
            }
            current = current->next;
        }

        current->next = initNode(&key, val);
    }
    else
    {
        hashMap->array[index] = initNode(&key, val);
    }
}

void *getByStringKey(HashMap *hashMap, char *key)
{
    int index = hash(key) % HASH_MAP_SIZE;

    if (hashMap->array[index])
    {
        Node *current = hashMap->array[index];

        while (current)
        {
            if (strcmp((char *)current->key, key) == 0)
            {
                return current->val;
            }
            current = current->next;
        }
    }

    return NULL;
}

void *getByIntKey(HashMap *hashMap, int key)
{
    int index = key % HASH_MAP_SIZE;

    if (hashMap->array[index])
    {
        Node *current = hashMap->array[index];

        while (current)
        {
            if (*(int *)current->key == key)
            {
                return current->val;
            }
            current = current->next;
        }
    }

    return NULL;
}

void printHashMap(HashMap *hashMap)
{
    for (int i = 0; i < HASH_MAP_SIZE; i++)
    {
        if (hashMap->array[i])
        {
            Node *curr = hashMap->array[i];
            printf("[%d]: ", i);
            while (curr)
            {
                printf("%s %d, ", curr->key, curr->val);
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
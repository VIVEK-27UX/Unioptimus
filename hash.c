#include <stdlib.h>
#include "structures.h"

unsigned int hashFn(int id)
{
    return id % HASH_SIZE;
}

void hashInsert(HashTable *ht, Student s)
{
    unsigned int idx = hashFn(s.id);

    HashNode *node = (HashNode*)malloc(sizeof(HashNode));
    node->data = s;
    node->next = ht->buckets[idx];
    ht->buckets[idx] = node;

    ht->count++;
}

Student *hashSearch(HashTable *ht, int id)
{
    unsigned int idx = hashFn(id);

    for (HashNode *cur = ht->buckets[idx]; cur; cur = cur->next)
        if (cur->data.id == id)
            return &cur->data;

    return NULL;
}
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

void saveStudentToFile(Student s)
{
    FILE *fp = fopen(STUDENT_FILE, "ab");

    if (fp == NULL)
    {
        printf("File error!\n");
        return;
    }

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
}

void loadStudentsFromFile(HashTable *ht)
{
    FILE *fp = fopen(STUDENT_FILE, "rb");

    if (fp == NULL) return;

    Student s;

    while (fread(&s, sizeof(Student), 1, fp))
    {
        unsigned int idx = s.id % HASH_SIZE;

        HashNode *node = (HashNode*)malloc(sizeof(HashNode));
        node->data = s;
        node->next = ht->buckets[idx];
        ht->buckets[idx] = node;
        ht->count++;
    }

    fclose(fp);
}
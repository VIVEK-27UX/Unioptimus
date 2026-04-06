#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <limits.h>

#define MAX_STUDENTS 100
#define MAX_NAME 64
#define HASH_SIZE 127
#define MAX_NODES 20
#define INF INT_MAX
#define MAX_ACTIVITIES 50
#define MAX_ITEMS 50
#define STUDENT_FILE "students.dat"

typedef struct {
    int id;
    char name[MAX_NAME];
    char branch[32];
    float cgpa;
} Student;

typedef struct HashNode {
    Student data;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode *buckets[HASH_SIZE];
    int count;
} HashTable;

typedef struct {
    int adj[MAX_NODES][MAX_NODES];
    int n;
} Graph;

typedef struct {
    char name[MAX_NAME];
    int start, finish;
    int selected;
} Activity;

typedef struct {
    char name[MAX_NAME];
    double weight, value;
} Item;

#endif
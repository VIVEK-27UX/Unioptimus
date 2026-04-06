#include <stdio.h>
#include "structures.h"

/* function declarations from other modules */
void saveStudentToFile(Student s);
void loadStudentsFromFile(HashTable *ht);
void hashInsert(HashTable *ht, Student s);
Student *hashSearch(HashTable *ht, int id);

int activitySelection(Activity *acts, int n);
double fractionalKnapsack(Item *items, int n, double capacity);

int findMotherVertex(Graph *g);

/* ANSI colors (same as original) */
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

int main()
{
    HashTable ht = {0};
    int choice;

    loadStudentsFromFile(&ht);

    while (1)
    {
        printf(BOLD CYAN "\n--- UniOptimus Menu ---\n" RESET);
        printf("1. Register Student\n");
        printf("2. Search Student\n");
        printf("3. Activity Selection\n");
        printf("4. Resource Knapsack\n");
        printf("5. Network Mother Vertex\n");
        printf("6. Exit\n");
        printf("Selection: ");

        scanf("%d", &choice);

        if (choice == 1)
        {
            Student s;

            printf("Enter ID Name Branch CGPA: ");
            scanf("%d %s %s %f", &s.id, s.name, s.branch, &s.cgpa);

            hashInsert(&ht, s);
            saveStudentToFile(s);

            printf(GREEN "Student Registered and Saved!\n" RESET);
        }

        else if (choice == 2)
        {
            int id;

            printf("Enter ID to search: ");
            scanf("%d", &id);

            Student *res = hashSearch(&ht, id);

            if (res)
                printf(YELLOW "Found: %s (%s) CGPA: %.2f\n" RESET,
                       res->name, res->branch, res->cgpa);
            else
                printf(RED "Student not found\n" RESET);
        }

        else if (choice == 3)
        {
            int n;

            printf("Number of activities: ");
            scanf("%d", &n);

            Activity acts[MAX_ACTIVITIES];

            for (int i = 0; i < n; i++)
            {
                printf("Name Start Finish: ");
                scanf("%s %d %d",
                      acts[i].name,
                      &acts[i].start,
                      &acts[i].finish);
            }

            int total = activitySelection(acts, n);

            printf(GREEN "Maximum activities: %d\n" RESET, total);

            for (int i = 0; i < n; i++)
                if (acts[i].selected)
                    printf("Selected: %s\n", acts[i].name);
        }

        else if (choice == 4)
        {
            int n;
            double cap;

            printf("Enter number of items and capacity: ");
            scanf("%d %lf", &n, &cap);

            Item items[MAX_ITEMS];

            for (int i = 0; i < n; i++)
            {
                printf("Name Value Weight: ");
                scanf("%s %lf %lf",
                      items[i].name,
                      &items[i].value,
                      &items[i].weight);
            }

            double maxValue = fractionalKnapsack(items, n, cap);

            printf(GREEN "Maximum value: %.2f\n" RESET, maxValue);
        }

        else if (choice == 5)
        {
            Graph g;

            printf("Enter number of nodes: ");
            scanf("%d", &g.n);

            printf("Enter adjacency matrix:\n");

            for (int i = 0; i < g.n; i++)
                for (int j = 0; j < g.n; j++)
                    scanf("%d", &g.adj[i][j]);

            int mv = findMotherVertex(&g);

            if (mv != -1)
                printf(GREEN "Mother Vertex: %d\n" RESET, mv);
            else
                printf(RED "No Mother Vertex\n" RESET);
        }

        else if (choice == 6)
        {
            printf("Exiting...\n");
            break;
        }
    }

    return 0;
}
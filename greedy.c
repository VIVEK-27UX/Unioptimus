#include <stdlib.h>
#include "structures.h"

int cmpActivity(const void *a, const void *b)
{
    return ((Activity *)a)->finish - ((Activity *)b)->finish;
}

int activitySelection(Activity *acts, int n)
{
    qsort(acts, n, sizeof(Activity), cmpActivity);

    int count = 0;
    int lastFinish = -1;

    for (int i = 0; i < n; i++)
    {
        if (acts[i].start >= lastFinish)
        {
            acts[i].selected = 1;
            lastFinish = acts[i].finish;
            count++;
        }
        else
            acts[i].selected = 0;
    }

    return count;
}

int cmpItem(const void *a, const void *b)
{
    double r1 = ((Item *)a)->value / ((Item *)a)->weight;
    double r2 = ((Item *)b)->value / ((Item *)b)->weight;

    if (r2 > r1) return 1;
    if (r2 < r1) return -1;

    return 0;
}

double fractionalKnapsack(Item *items, int n, double capacity)
{
    qsort(items, n, sizeof(Item), cmpItem);

    double totalValue = 0.0;

    for (int i = 0; i < n; i++)
    {
        if (capacity >= items[i].weight)
        {
            capacity -= items[i].weight;
            totalValue += items[i].value;
        }
        else
        {
            totalValue += items[i].value * (capacity / items[i].weight);
            break;
        }
    }

    return totalValue;
}
#include "structures.h"

void dfsMark(Graph *g, int u, int visited[])
{
    visited[u] = 1;

    for (int v = 0; v < g->n; v++)
        if (g->adj[u][v] && !visited[v])
            dfsMark(g, v, visited);
}

int findMotherVertex(Graph *g)
{
    int visited[MAX_NODES] = {0};
    int candidate = 0;

    for (int i = 0; i < g->n; i++)
    {
        if (!visited[i])
        {
            dfsMark(g, i, visited);
            candidate = i;
        }
    }

    int checkVisited[MAX_NODES] = {0};
    dfsMark(g, candidate, checkVisited);

    for (int i = 0; i < g->n; i++)
        if (!checkVisited[i])
            return -1;

    return candidate;
}